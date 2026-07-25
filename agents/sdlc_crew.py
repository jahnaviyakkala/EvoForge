import os
import re
try:
    from crewai import Crew, Process, Task
    HAS_CREW = True
except Exception:
    Crew = None
    Process = None
    Task = None
    HAS_CREW = False
from typing import Any as BaseAgent  # Lazy import of BaseAgent at runtime to avoid module-level crewai dependency

from database.db_manager import DBManager
from tools.file_tools import calculate_hash, read_file, write_file, save_json
from tools.project_tools import (
    read_project_file,
    write_project_file,
    list_project_files,
    analyze_python_ast
)
from tools.build_tools import generate_makefile
from tools.language_tools import detect_language, load_project_language, save_project_language, get_source_extensions
from tools.requirement_tools import classify_requirements
from tools.static_analysis import build_dependency_graph, dependency_graph_to_json
from tools.reuse_tools import generate_reuse_decision_report
from tools.impact_tools import generate_test_impact_report
import tools.cli_ui as ui

class SDLCCrewManager:
    def __init__(self, project_name: str):
        self.project_name = project_name
        self.project_dir = os.path.join(
            os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
            "projects",
            project_name
        )
        self.reports_dir = os.path.join(
            os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
            "reports",
            project_name
        )
        os.makedirs(self.project_dir, exist_ok=True)
        os.makedirs(self.reports_dir, exist_ok=True)

        self.db = DBManager()
        self.project_id = self.db.register_project(project_name, self.project_dir)

    def run_pipeline(self, prompt: str, mode: str = "new"):
        """
        Runs the multi-agent SDLC pipeline incrementally.
        mode can be 'new' or 'evolve'.
        """
        self.current_prompt = prompt
        srs_path = os.path.join(self.reports_dir, "SRS.md")
        delta_path = os.path.join(self.reports_dir, "Requirement_Delta_Report.md")
        dependency_path = os.path.join(self.reports_dir, "Dependency_Graph.json")
        reuse_path = os.path.join(self.reports_dir, "Reuse_Decision_Report.md")
        test_impact_path = os.path.join(self.reports_dir, "Test_Impact_Report.md")

        existing_srs = self._load_existing_srs()
        prompt_language = detect_language(prompt)
        saved_language = load_project_language(self.project_dir)
        self.project_language = saved_language or prompt_language
        if saved_language and saved_language != prompt_language:
            if not self._project_has_source_files():
                ui.print_stage_warning(
                    "Language Override",
                    f"Prompt indicates '{prompt_language}' but existing project language is '{saved_language}'. Overriding language based on prompt."
                )
                self.project_language = prompt_language
            else:
                ui.print_stage_warning(
                    "Language Preserved",
                    f"Existing project language '{saved_language}' will be preserved for this run."
                )
        save_project_language(self.project_dir, self.project_language)

        # STAGE 1: Requirements Analysis
        ui.print_stage_card(1, 5, "Requirements Analysis & SRS Delta", "Parsing functional prompt, analyzing existing specification, and triaging requirement delta.")
        raw_srs = self._run_requirement_stage(prompt, existing_srs, srs_path)

        merged_srs, delta_report, classified_requirements = classify_requirements(existing_srs, raw_srs)
        write_file(srs_path, merged_srs)
        write_file(delta_path, delta_report)
        if hasattr(self.db, 'store_srs_version'):
            try:
                self.db.store_srs_version(self.project_id, merged_srs, note=mode)
            except Exception as e:
                ui.print_stage_warning("DB Persistence", f"Failed to store SRS version in DB: {e}")
        ui.print_stage_success("Requirement Stage", "SRS specification synthesized & requirement delta classified.")

        # STAGE 2: Architecture & Dependency Modeling
        ui.print_stage_card(2, 5, "Architecture & Dependency Modeling", "Generating static dependency graph, evaluating asset reuse, and modeling software design.")
        dependency_graph = build_dependency_graph(self.project_dir)
        save_json(dependency_path, dependency_graph)
        if hasattr(self.db, 'store_dependency_graph'):
            try:
                self.db.store_dependency_graph(self.project_id, "static", dependency_graph_to_json(dependency_graph), file_path=dependency_path)
            except Exception as e:
                ui.print_stage_warning("DB Persistence", f"Failed to store dependency graph in DB: {e}")

        reuse_report = generate_reuse_decision_report(self.project_dir, merged_srs)
        write_file(reuse_path, reuse_report)

        impacted_modules = self._guess_impacted_modules(classified_requirements)
        test_impact_report = generate_test_impact_report(impacted_modules, self.project_dir)
        write_file(test_impact_path, test_impact_report)

        self._run_design_stage(design_output=os.path.join(self.reports_dir, "Design.md"), delta_path=delta_path)
        ui.print_stage_success("Architecture Stage", "Dependency graph, reuse decisions & design documents updated.")

        # STAGE 3: Automated Code Generation
        ui.print_stage_card(3, 5, "Automated Code Engineering", "Generating source files, module headers, and build configuration specs.")
        try:
            from agents.base_agent import BaseAgent as _BaseAgent
            code_agent_name = "c_code_agent" if self.project_language in {"c", "cpp"} else "code_agent"
            code_agent_wrapper = _BaseAgent(code_agent_name)
        except Exception as e:
            ui.print_stage_warning("Agent Initialization", f"Could not import BaseAgent for code stage: {e}. Proceeding with fallback.")
            code_agent_wrapper = None
        self._run_code_stage(code_agent_wrapper=code_agent_wrapper, code_output=None, dependency_path=dependency_path, reuse_path=reuse_path, delta_path=delta_path)
        ui.print_stage_success("Code Engineering Stage", "Source files and build artifacts synthesized.")

        # STAGE 4: Testing & Test Suite Synthesis
        ui.print_stage_card(4, 5, "Test Suite & Impact Mapping", "Synthesizing test cases and mapping requirement impact to test execution suites.")
        self._run_testing_stage(testing_output_dir=os.path.join(self.project_dir, "tests"), test_impact_path=test_impact_path)
        ui.print_stage_success("Testing Stage", "Test suite files generated and mapped to impact specs.")

        # STAGE 5: Documentation & Spec Persistence
        ui.print_stage_card(5, 5, "Documentation & Spec Persistence", "Generating project documentation and updating SQLite DB version control.")
        self._run_documentation_stage(doc_output_dir=self.project_dir)

        self._update_db_registry_and_run(mode)
        ui.print_stage_success("Documentation Stage", "Project documentation synthesized and version control updated.")
        return {
            "srs": srs_path,
            "delta_report": delta_path,
            "dependency_graph": dependency_path,
            "reuse_report": reuse_path,
            "test_impact_report": test_impact_path
        }

    def _load_existing_srs(self) -> str:
        srs_path = os.path.join(self.reports_dir, "SRS.md")
        if os.path.exists(srs_path):
            return read_file(srs_path)
        return ""

    def _run_single_stage(self, agent_wrapper: BaseAgent, task_name: str, task_vars: dict, output_file=None, tools=None):
        """Run a single agent task. If Crew is unavailable, write a safe placeholder output and continue.
        """
        # Prepare agent and task description
        agent = None
        description = task_vars.get("prompt", f"{task_name} (no description)")
        expected = None

        if agent_wrapper is not None:
            try:
                agent = agent_wrapper.get_agent(tools=tools)
                description = agent_wrapper.get_task_description(task_name).format(**task_vars)
                expected = agent_wrapper.get_task_expected_output(task_name)
            except Exception as e:
                print(f"Agent wrapper preparation failed: {e}")
                agent = None

        if not HAS_CREW:
            print(f"Crew not available; attempting local agent execution for task '{task_name}'.")

            # For offline C/C++ code, testing, and documentation stages, deterministic fallback is more reliable.
            if hasattr(self, 'project_language') and self.project_language in {"c", "cpp"} and task_name in {"code_task", "testing_task", "documentation_task"}:
                print(f"Using deterministic C/C++ fallback for task '{task_name}' because Crew is unavailable.")
                fallback_output = self._run_c_fallback(task_name, task_vars, output_file)
                if fallback_output is not None:
                    return fallback_output

            # If we have a local agent implementation, run it and write its output
            if agent is not None and hasattr(agent, 'run'):
                try:
                    result_text = agent.run(description)
                    if not result_text or self._is_local_agent_failure(result_text):
                        raise ValueError("Local agent returned an error response")
                    if output_file:
                        try:
                            write_file(output_file, result_text)
                        except Exception as e:
                            print(f"Failed writing agent output to {output_file}: {e}")
                    return result_text
                except Exception as e:
                    print(f"Local agent execution failed: {e}")

            # If this is a C/C++ project, attempt deterministic fallback generation
            if hasattr(self, 'project_language') and self.project_language in {"c", "cpp"}:
                fallback_output = self._run_c_fallback(task_name, task_vars, output_file)
                if fallback_output is not None:
                    return fallback_output

            # Fallback placeholder when no local agent is available
            print(f"Local agent not available or failed — writing placeholder for '{task_name}'")
            if output_file:
                placeholder = f"# Placeholder output for {task_name}\n\nDescription:\n{description}\n\nNote: Crew/agent execution was skipped because the crew library is unavailable or incompatible, and local agent execution failed."
                try:
                    write_file(output_file, placeholder)
                except Exception as e:
                    print(f"Failed writing placeholder output to {output_file}: {e}")
            return None

        # If agent could not be prepared, write placeholder and return
        if agent is None:
            print(f"Agent is None for task '{task_name}' — writing placeholder output.")
            if output_file:
                placeholder = f"# Placeholder output for {task_name}\n\nDescription:\n{description}\n\nNote: Agent could not be initialized."
                try:
                    write_file(output_file, placeholder)
                except Exception as e:
                    print(f"Failed writing placeholder output to {output_file}: {e}")
            return None

        # Normal flow: run with Crew
        try:
            task = Task(
                description=description,
                expected_output=expected or f"Output for {task_name}",
                agent=agent,
                output_file=output_file
            )
            crew = Crew(agents=[agent], tasks=[task], process=Process.sequential, verbose=True)
            print(f"Running {task_name}...")
            return crew.kickoff()
        except TypeError as te:
            # Backward/forward compatibility issues — fallback to placeholder behavior
            print(f"Crew execution failed with TypeError: {te}. Falling back to placeholder output for '{task_name}'.")
            if output_file:
                placeholder = f"# Fallback output for {task_name}\n\nDescription:\n{description}\n\nNote: Crew execution failed with TypeError: {te}."
                try:
                    write_file(output_file, placeholder)
                except Exception as e:
                    print(f"Failed writing fallback output to {output_file}: {e}")
            return None
        except Exception as e:
            print(f"Unexpected error while running Crew for '{task_name}': {e}")
            raise

    def _run_requirement_stage(self, prompt: str, existing_srs: str, output_file: str) -> str:
        # Lazy import BaseAgent to avoid import-time crewai dependency
        try:
            from agents.base_agent import BaseAgent as _BaseAgent
            req_agent_wrapper = _BaseAgent("requirement_agent")
        except Exception as e:
            print(f"Could not import BaseAgent for requirement stage: {e}. Proceeding with fallback.")
            req_agent_wrapper = None

        req_task_vars = {
            "prompt": prompt,
            "reports_dir": self.reports_dir,
            "existing_srs": existing_srs or ""
        }
        self._run_single_stage(
            req_agent_wrapper,
            "requirement_task",
            req_task_vars,
            output_file=output_file,
            tools=[read_project_file, write_project_file]
        )
        return read_file(output_file)

    def _run_c_fallback(self, task_name: str, task_vars: dict, output_file: str):
        if task_name == "requirement_task":
            content = self._generate_c_requirements(task_vars.get("prompt", ""))
            if output_file:
                write_file(output_file, content)
            return content
        if task_name == "design_task":
            content = self._generate_c_design(task_vars.get("prompt", ""))
            if output_file:
                write_file(output_file, content)
            return content
        if task_name == "code_task":
            self._generate_c_code(task_vars.get("prompt", ""))
            return "Generated C/C++ source files."
        if task_name == "testing_task":
            self._generate_c_tests(task_vars["project_dir"])
            return "Generated C/C++ tests."
        if task_name == "documentation_task":
            self._generate_c_documentation(task_vars["project_dir"])
            return "Generated C/C++ documentation."
        return None

    def _is_local_agent_failure(self, result_text: str) -> bool:
        if not result_text:
            return True
        normalized = result_text.strip().upper()
        failure_indicators = [
            "ERROR_RUNNING_OLLAMA",
            "LOCAL_AGENT_ERROR",
            "ERROR:",
            "FAILED",
            "UNABLE TO",
            "NOT AVAILABLE",
            "NO MODEL"
        ]
        return any(indicator in normalized for indicator in failure_indicators)

    def _project_has_source_files(self) -> bool:
        source_exts = get_source_extensions('c') | get_source_extensions('cpp') | get_source_extensions('python')
        for root, _, files in os.walk(self.project_dir):
            if any(ignored in root for ignored in [".venv", "__pycache__", ".git", ".pytest_cache"]):
                continue
            for file in files:
                if file == '.evoforge_lang':
                    continue
                if os.path.splitext(file)[1] in source_exts:
                    return True
        return False

    def _infer_c_domain(self, prompt: str) -> str:
        prompt_lower = (prompt or getattr(self, 'current_prompt', '')).lower()
        if "queue" in prompt_lower:
            return "queue"
        elif "calculator" in prompt_lower:
            return "calculator"
        elif "converter" in prompt_lower:
            return "converter"
        elif "tree" in prompt_lower or "bst" in prompt_lower:
            return "tree"
        elif "list" in prompt_lower or "vector" in prompt_lower:
            return "list"
        elif "stack" in prompt_lower:
            return "stack"

        # Check existing headers in project_dir
        if hasattr(self, 'project_dir') and os.path.exists(self.project_dir):
            for f in os.listdir(self.project_dir):
                if f.endswith(('.h', '.hpp')) and f not in ('main.h', 'main.hpp'):
                    return os.path.splitext(f)[0]

        clean_name = re.sub(r'[^a-zA-Z0-9_]', '_', self.project_name).strip('_').lower()
        return clean_name or "module"

    def _generate_c_requirements(self, prompt: str) -> str:
        language_label = "C++" if self.project_language == "cpp" else "C"
        domain = self._infer_c_domain(prompt)
        domain_title = domain.capitalize()
        return (
            f"# Software Requirements Specification\n\n"
            f"## Overview\nThe system shall implement a {domain_title} component in {language_label}.\n\n"
            "## Functional Requirements\n"
            f"- [NEW] The system shall provide primary operations for {domain_title}.\n"
            f"- [NEW] The system shall support inspection and status queries for {domain_title}.\n"
            "- [NEW] The system shall safely handle invalid operations, boundary conditions, and memory allocation.\n"
            "- [NEW] The system shall compile using a generated Makefile and run automated unit tests.\n\n"
            "## Non-Functional Requirements\n"
            f"- [NEW] The implementation shall use idiomatic, standards-compliant {language_label}.\n"
            "- [NEW] The code shall be organized into header/source files and a test runner.\n"
            "- [NEW] The system shall include documentation describing build and usage instructions.\n"
        )

    def _generate_c_design(self, prompt: str) -> str:
        language_label = "C++" if self.project_language == "cpp" else "C"
        domain = self._infer_c_domain(prompt)
        header_ext = "hpp" if self.project_language == "cpp" else "h"
        source_ext = "cpp" if self.project_language == "cpp" else "c"
        struct_name = domain.capitalize()
        return (
            "# Design Document\n\n"
            f"## Architecture Overview\nThe project is a {language_label} library providing a {struct_name} module.\n\n"
            f"## Module Specifications\n"
            f"- `{domain}.{header_ext}`: Public API declarations for the {domain} component.\n"
            f"- `{domain}.{source_ext}`: Core implementation of {domain} operations.\n"
            f"- `main.{source_ext}`: Example usage and demonstration program.\n"
            f"- `tests/test_runner.{source_ext}`: Automated test harness validating {domain} functionality.\n\n"
            f"## Data Model\n- `{struct_name}` struct storing module state and resources.\n\n"
            "## Sequence Flow\n"
            "```mermaid\nsequenceDiagram\n    participant User\n    participant Main\n"
            f"    participant {struct_name}Module\n\n"
            "    User->>Main: start program\n"
            f"    Main->>{struct_name}Module: init\n"
            f"    Main->>{struct_name}Module: operate\n"
            f"    Main->>{struct_name}Module: destroy\n"
            "```\n"
        )

    def _generate_c_code(self, prompt: str) -> None:
        domain = self._infer_c_domain(prompt)
        is_cpp = (self.project_language == "cpp")
        header_ext = "hpp" if is_cpp else "h"
        source_ext = "cpp" if is_cpp else "c"
        header = f"{domain}.{header_ext}"
        source = f"{domain}.{source_ext}"
        main_src = f"main.{source_ext}"
        header_guard = f"{domain.upper()}_{header_ext.upper()}"
        struct_name = domain.capitalize()

        if domain == "queue":
            if is_cpp:
                header_content = (
                    f"#ifndef {header_guard}\n#define {header_guard}\n\n#include <cstddef>\n\n"
                    "struct Queue {\n    int *data;\n    std::size_t front;\n    std::size_t rear;\n    std::size_t size;\n    std::size_t capacity;\n};\n\n"
                    "void queue_init(Queue &q, std::size_t capacity);\n"
                    "bool queue_enqueue(Queue &q, int value);\n"
                    "bool queue_dequeue(Queue &q, int &value);\n"
                    "bool queue_peek(const Queue &q, int &value);\n"
                    "bool queue_is_empty(const Queue &q);\n"
                    "void queue_destroy(Queue &q);\n\n#endif\n"
                )
                source_content = (
                    f"#include \"{header}\"\n#include <cstdlib>\n#include <new>\n\n"
                    "void queue_init(Queue &q, std::size_t capacity) {\n"
                    "    q.data = static_cast<int*>(std::malloc(capacity * sizeof(int)));\n"
                    "    q.front = q.rear = q.size = 0;\n"
                    "    q.capacity = q.data ? capacity : 0;\n}\n\n"
                    "bool queue_enqueue(Queue &q, int value) {\n"
                    "    if (!q.data || q.size >= q.capacity) return false;\n"
                    "    q.data[q.rear] = value;\n"
                    "    q.rear = (q.rear + 1) % q.capacity;\n"
                    "    q.size++;\n    return true;\n}\n\n"
                    "bool queue_dequeue(Queue &q, int &value) {\n"
                    "    if (!q.data || q.size == 0) return false;\n"
                    "    value = q.data[q.front];\n"
                    "    q.front = (q.front + 1) % q.capacity;\n"
                    "    q.size--;\n    return true;\n}\n\n"
                    "bool queue_peek(const Queue &q, int &value) {\n"
                    "    if (!q.data || q.size == 0) return false;\n"
                    "    value = q.data[q.front];\n    return true;\n}\n\n"
                    "bool queue_is_empty(const Queue &q) {\n"
                    "    return q.size == 0;\n}\n\n"
                    "void queue_destroy(Queue &q) {\n"
                    "    std::free(q.data);\n    q.data = nullptr;\n    q.front = q.rear = q.size = q.capacity = 0;\n}\n"
                )
                main_content = (
                    f"#include <iostream>\n#include \"{header}\"\n\n"
                    "int main() {\n"
                    "    Queue q;\n    queue_init(q, 5);\n    queue_enqueue(q, 10);\n    queue_enqueue(q, 20);\n"
                    "    int val;\n    if (queue_peek(q, val)) std::cout << \"Front: \" << val << std::endl;\n"
                    "    while (queue_dequeue(q, val)) std::cout << \"Dequeued: \" << val << std::endl;\n"
                    "    queue_destroy(q);\n    return 0;\n}\n"
                )
            else:
                header_content = (
                    f"#ifndef {header_guard}\n#define {header_guard}\n\n#include <stddef.h>\n#include <stdbool.h>\n\n"
                    "typedef struct {\n    int *data;\n    size_t front;\n    size_t rear;\n    size_t size;\n    size_t capacity;\n} Queue;\n\n"
                    "void queue_init(Queue *q, size_t capacity);\n"
                    "bool queue_enqueue(Queue *q, int value);\n"
                    "bool queue_dequeue(Queue *q, int *value);\n"
                    "bool queue_peek(const Queue *q, int *value);\n"
                    "bool queue_is_empty(const Queue *q);\n"
                    "void queue_destroy(Queue *q);\n\n#endif\n"
                )
                source_content = (
                    f"#include \"{header}\"\n#include <stdlib.h>\n\n"
                    "void queue_init(Queue *q, size_t capacity) {\n"
                    "    if (!q) return;\n"
                    "    q->data = (int *)malloc(capacity * sizeof(int));\n"
                    "    q->front = q->rear = q->size = 0;\n"
                    "    q->capacity = q->data ? capacity : 0;\n}\n\n"
                    "bool queue_enqueue(Queue *q, int value) {\n"
                    "    if (!q || !q->data || q->size >= q->capacity) return false;\n"
                    "    q->data[q->rear] = value;\n"
                    "    q->rear = (q->rear + 1) % q->capacity;\n"
                    "    q->size++;\n    return true;\n}\n\n"
                    "bool queue_dequeue(Queue *q, int *value) {\n"
                    "    if (!q || !q->data || q->size == 0) return false;\n"
                    "    if (value) *value = q->data[q->front];\n"
                    "    q->front = (q->front + 1) % q->capacity;\n"
                    "    q->size--;\n    return true;\n}\n\n"
                    "bool queue_peek(const Queue *q, int *value) {\n"
                    "    if (!q || !q->data || q->size == 0) return false;\n"
                    "    if (value) *value = q->data[q->front];\n    return true;\n}\n\n"
                    "bool queue_is_empty(const Queue *q) {\n"
                    "    return !q || q->size == 0;\n}\n\n"
                    "void queue_destroy(Queue *q) {\n"
                    "    if (!q) return;\n"
                    "    free(q->data);\n    q->data = NULL;\n    q->front = q->rear = q->size = q->capacity = 0;\n}\n"
                )
                main_content = (
                    f"#include <stdio.h>\n#include \"{header}\"\n\n"
                    "int main(void) {\n"
                    "    Queue q;\n    queue_init(&q, 5);\n    queue_enqueue(&q, 10);\n    queue_enqueue(&q, 20);\n"
                    "    int val;\n    if (queue_peek(&q, &val)) printf(\"Front: %d\\n\", val);\n"
                    "    while (queue_dequeue(&q, &val)) printf(\"Dequeued: %d\\n\", val);\n"
                    "    queue_destroy(&q);\n    return 0;\n}\n"
                )
        elif domain == "calculator":
            if is_cpp:
                header_content = (
                    f"#ifndef {header_guard}\n#define {header_guard}\n\n"
                    "double calculator_add(double a, double b);\n"
                    "double calculator_subtract(double a, double b);\n"
                    "double calculator_multiply(double a, double b);\n"
                    "bool calculator_divide(double a, double b, double &result);\n\n#endif\n"
                )
                source_content = (
                    f"#include \"{header}\"\n\n"
                    "double calculator_add(double a, double b) { return a + b; }\n"
                    "double calculator_subtract(double a, double b) { return a - b; }\n"
                    "double calculator_multiply(double a, double b) { return a * b; }\n"
                    "bool calculator_divide(double a, double b, double &result) {\n"
                    "    if (b == 0.0) return false;\n    result = a / b;\n    return true;\n}\n"
                )
                main_content = (
                    f"#include <iostream>\n#include \"{header}\"\n\n"
                    "int main() {\n"
                    "    std::cout << \"2 + 3 = \" << calculator_add(2, 3) << std::endl;\n"
                    "    double res;\n"
                    "    if (calculator_divide(10, 2, res)) std::cout << \"10 / 2 = \" << res << std::endl;\n"
                    "    return 0;\n}\n"
                )
            else:
                header_content = (
                    f"#ifndef {header_guard}\n#define {header_guard}\n\n#include <stdbool.h>\n\n"
                    "double calculator_add(double a, double b);\n"
                    "double calculator_subtract(double a, double b);\n"
                    "double calculator_multiply(double a, double b);\n"
                    "bool calculator_divide(double a, double b, double *result);\n\n#endif\n"
                )
                source_content = (
                    f"#include \"{header}\"\n\n"
                    "double calculator_add(double a, double b) { return a + b; }\n"
                    "double calculator_subtract(double a, double b) { return a - b; }\n"
                    "double calculator_multiply(double a, double b) { return a * b; }\n"
                    "bool calculator_divide(double a, double b, double *result) {\n"
                    "    if (b == 0.0) return false;\n    if (result) *result = a / b;\n    return true;\n}\n"
                )
                main_content = (
                    f"#include <stdio.h>\n#include \"{header}\"\n\n"
                    "int main(void) {\n"
                    "    printf(\"2 + 3 = %f\\n\", calculator_add(2, 3));\n"
                    "    double res;\n"
                    "    if (calculator_divide(10, 2, &res)) printf(\"10 / 2 = %f\\n\", res);\n"
                    "    return 0;\n}\n"
                )
        else: # stack or generic
            if is_cpp:
                header_content = (
                    f"#ifndef {header_guard}\n#define {header_guard}\n\n#include <cstddef>\n\n"
                    f"struct {struct_name} {{\n    int *data;\n    std::size_t size;\n    std::size_t capacity;\n}};\n\n"
                    f"void {domain}_init({struct_name} &s, std::size_t capacity);\n"
                    f"void {domain}_push({struct_name} &s, int value);\n"
                    f"bool {domain}_pop({struct_name} &s, int &value);\n"
                    f"bool {domain}_peek(const {struct_name} &s, int &value);\n"
                    f"bool {domain}_is_empty(const {struct_name} &s);\n"
                    f"void {domain}_destroy({struct_name} &s);\n\n#endif\n"
                )
                source_content = (
                    f"#include \"{header}\"\n#include <cstdlib>\n#include <new>\n\n"
                    f"void {domain}_init({struct_name} &s, std::size_t capacity) {{\n"
                    f"    s.data = static_cast<int*>(std::malloc(capacity * sizeof(int)));\n"
                    f"    s.size = 0;\n    s.capacity = s.data ? capacity : 0;\n}}\n\n"
                    f"void {domain}_push({struct_name} &s, int value) {{\n"
                    f"    if (s.size >= s.capacity) {{\n"
                    f"        std::size_t new_cap = s.capacity == 0 ? 4 : s.capacity * 2;\n"
                    f"        int *new_data = static_cast<int*>(std::realloc(s.data, new_cap * sizeof(int)));\n"
                    f"        if (!new_data) return;\n        s.data = new_data;\n        s.capacity = new_cap;\n"
                    f"    }}\n    s.data[s.size++] = value;\n}}\n\n"
                    f"bool {domain}_pop({struct_name} &s, int &value) {{\n"
                    f"    if (s.size == 0) return false;\n    value = s.data[--s.size];\n    return true;\n}}\n\n"
                    f"bool {domain}_peek(const {struct_name} &s, int &value) {{\n"
                    f"    if (s.size == 0) return false;\n    value = s.data[s.size - 1];\n    return true;\n}}\n\n"
                    f"bool {domain}_is_empty(const {struct_name} &s) {{\n    return s.size == 0;\n}}\n\n"
                    f"void {domain}_destroy({struct_name} &s) {{\n"
                    f"    std::free(s.data);\n    s.data = nullptr;\n    s.size = s.capacity = 0;\n}}\n"
                )
                main_content = (
                    f"#include <iostream>\n#include \"{header}\"\n\n"
                    "int main() {\n"
                    f"    {struct_name} s;\n    {domain}_init(s, 4);\n    {domain}_push(s, 10);\n"
                    f"    int val;\n    if ({domain}_peek(s, val)) std::cout << \"Top: \" << val << std::endl;\n"
                    f"    while ({domain}_pop(s, val)) std::cout << \"Popped: \" << val << std::endl;\n"
                    f"    {domain}_destroy(s);\n    return 0;\n}}\n"
                )
            else:
                header_content = (
                    f"#ifndef {header_guard}\n#define {header_guard}\n\n#include <stddef.h>\n#include <stdbool.h>\n\n"
                    f"typedef struct {{\n    int *data;\n    size_t size;\n    size_t capacity;\n}} {struct_name};\n\n"
                    f"void {domain}_init({struct_name} *s, size_t capacity);\n"
                    f"void {domain}_push({struct_name} *s, int value);\n"
                    f"bool {domain}_pop({struct_name} *s, int *value);\n"
                    f"bool {domain}_peek(const {struct_name} *s, int *value);\n"
                    f"bool {domain}_is_empty(const {struct_name} *s);\n"
                    f"void {domain}_destroy({struct_name} *s);\n\n#endif\n"
                )
                source_content = (
                    f"#include \"{header}\"\n#include <stdlib.h>\n\n"
                    f"void {domain}_init({struct_name} *s, size_t capacity) {{\n"
                    f"    if (!s) return;\n"
                    f"    s->data = (int *)malloc(capacity * sizeof(int));\n"
                    f"    s->size = 0;\n    s->capacity = s->data ? capacity : 0;\n}}\n\n"
                    f"void {domain}_push({struct_name} *s, int value) {{\n"
                    f"    if (!s) return;\n"
                    f"    if (s->size >= s->capacity) {{\n"
                    f"        size_t new_cap = s->capacity == 0 ? 4 : s->capacity * 2;\n"
                    f"        int *new_data = (int *)realloc(s->data, new_cap * sizeof(int));\n"
                    f"        if (!new_data) return;\n        s->data = new_data;\n        s->capacity = new_cap;\n"
                    f"    }}\n    s->data[s->size++] = value;\n}}\n\n"
                    f"bool {domain}_pop({struct_name} *s, int *value) {{\n"
                    f"    if (!s || s->size == 0) return false;\n"
                    f"    if (value) *value = s->data[--s->size];\n    return true;\n}}\n\n"
                    f"bool {domain}_peek(const {struct_name} *s, int *value) {{\n"
                    f"    if (!s || s->size == 0) return false;\n"
                    f"    if (value) *value = s->data[s->size - 1];\n    return true;\n}}\n\n"
                    f"bool {domain}_is_empty(const {struct_name} *s) {{\n"
                    f"    return !s || s->size == 0;\n}}\n\n"
                    f"void {domain}_destroy({struct_name} *s) {{\n"
                    f"    if (!s) return;\n"
                    f"    free(s->data);\n    s->data = NULL;\n    s->size = s->capacity = 0;\n}}\n"
                )
                main_content = (
                    f"#include <stdio.h>\n#include \"{header}\"\n\n"
                    "int main(void) {\n"
                    f"    {struct_name} s;\n    {domain}_init(&s, 4);\n    {domain}_push(&s, 10);\n"
                    f"    int val;\n    if ({domain}_peek(&s, &val)) printf(\"Top: %d\\n\", val);\n"
                    f"    while ({domain}_pop(&s, &val)) printf(\"Popped: %d\\n\", val);\n"
                    f"    {domain}_destroy(&s);\n    return 0;\n}}\n"
                )

        write_file(os.path.join(self.project_dir, header), header_content)
        write_file(os.path.join(self.project_dir, source), source_content)
        write_file(os.path.join(self.project_dir, main_src), main_content)
        generate_makefile(self.project_dir, self.project_name, self.project_language)

    def _generate_c_tests(self, project_dir: str) -> None:
        domain = self._infer_c_domain(getattr(self, 'current_prompt', ''))
        is_cpp = (self.project_language == "cpp")
        test_ext = "cpp" if is_cpp else "c"
        header = f"{domain}.hpp" if is_cpp else f"{domain}.h"
        test_file = os.path.join(project_dir, "tests", f"test_runner.{test_ext}")
        struct_name = domain.capitalize()

        if domain == "queue":
            if is_cpp:
                test_content = (
                    f"#include <cassert>\n#include <iostream>\n#include \"{header}\"\n\n"
                    "int main() {\n"
                    "    Queue q;\n    queue_init(q, 5);\n    assert(queue_is_empty(q));\n"
                    "    assert(queue_enqueue(q, 10));\n    assert(queue_enqueue(q, 20));\n"
                    "    assert(!queue_is_empty(q));\n    int val;\n"
                    "    assert(queue_peek(q, val) && val == 10);\n"
                    "    assert(queue_dequeue(q, val) && val == 10);\n"
                    "    assert(queue_dequeue(q, val) && val == 20);\n"
                    "    assert(queue_is_empty(q));\n    queue_destroy(q);\n"
                    "    std::cout << \"C++ Queue tests passed.\" << std::endl;\n    return 0;\n}\n"
                )
            else:
                test_content = (
                    f"#include <assert.h>\n#include <stdio.h>\n#include \"{header}\"\n\n"
                    "int main(void) {\n"
                    "    Queue q;\n    queue_init(&q, 5);\n    assert(queue_is_empty(&q));\n"
                    "    assert(queue_enqueue(&q, 10));\n    assert(queue_enqueue(&q, 20));\n"
                    "    assert(!queue_is_empty(&q));\n    int val;\n"
                    "    assert(queue_peek(&q, &val) && val == 10);\n"
                    "    assert(queue_dequeue(&q, &val) && val == 10);\n"
                    "    assert(queue_dequeue(&q, &val) && val == 20);\n"
                    "    assert(queue_is_empty(&q));\n    queue_destroy(&q);\n"
                    "    printf(\"C Queue tests passed.\\n\");\n    return 0;\n}\n"
                )
        elif domain == "calculator":
            if is_cpp:
                test_content = (
                    f"#include <cassert>\n#include <iostream>\n#include \"{header}\"\n\n"
                    "int main() {\n"
                    "    assert(calculator_add(2.0, 3.0) == 5.0);\n"
                    "    assert(calculator_subtract(5.0, 2.0) == 3.0);\n"
                    "    assert(calculator_multiply(4.0, 2.5) == 10.0);\n"
                    "    double res;\n"
                    "    assert(calculator_divide(10.0, 2.0, res) && res == 5.0);\n"
                    "    assert(!calculator_divide(5.0, 0.0, res));\n"
                    "    std::cout << \"C++ Calculator tests passed.\" << std::endl;\n    return 0;\n}\n"
                )
            else:
                test_content = (
                    f"#include <assert.h>\n#include <stdio.h>\n#include \"{header}\"\n\n"
                    "int main(void) {\n"
                    "    assert(calculator_add(2.0, 3.0) == 5.0);\n"
                    "    assert(calculator_subtract(5.0, 2.0) == 3.0);\n"
                    "    assert(calculator_multiply(4.0, 2.5) == 10.0);\n"
                    "    double res;\n"
                    "    assert(calculator_divide(10.0, 2.0, &res) && res == 5.0);\n"
                    "    assert(!calculator_divide(5.0, 0.0, &res));\n"
                    "    printf(\"C Calculator tests passed.\\n\");\n    return 0;\n}\n"
                )
        else:
            if is_cpp:
                test_content = (
                    f"#include <cassert>\n#include <iostream>\n#include \"{header}\"\n\n"
                    "int main() {\n"
                    f"    {struct_name} s;\n    {domain}_init(s, 4);\n    assert({domain}_is_empty(s));\n"
                    f"    {domain}_push(s, 1);\n    {domain}_push(s, 2);\n    int val;\n"
                    f"    assert({domain}_peek(s, val) && val == 2);\n"
                    f"    assert({domain}_pop(s, val) && val == 2);\n"
                    f"    assert({domain}_pop(s, val) && val == 1);\n"
                    f"    assert({domain}_is_empty(s));\n    {domain}_destroy(s);\n"
                    f"    std::cout << \"C++ {domain} tests passed.\" << std::endl;\n    return 0;\n}}\n"
                )
            else:
                test_content = (
                    f"#include <assert.h>\n#include <stdio.h>\n#include \"{header}\"\n\n"
                    "int main(void) {\n"
                    f"    {struct_name} s;\n    {domain}_init(&s, 4);\n    assert({domain}_is_empty(&s));\n"
                    f"    {domain}_push(&s, 1);\n    {domain}_push(&s, 2);\n    int val;\n"
                    f"    assert({domain}_peek(&s, &val) && val == 2);\n"
                    f"    assert({domain}_pop(&s, &val) && val == 2);\n"
                    f"    assert({domain}_pop(&s, &val) && val == 1);\n"
                    f"    assert({domain}_is_empty(&s));\n    {domain}_destroy(&s);\n"
                    f"    printf(\"C {domain} tests passed.\\n\");\n    return 0;\n}}\n"
                )

        write_file(test_file, test_content)

    def _generate_c_documentation(self, project_dir: str) -> None:
        readme = os.path.join(project_dir, "README.md")
        user_manual = os.path.join(project_dir, "User_Manual.md")
        runtime = "C++" if self.project_language == "cpp" else "C"
        domain = self._infer_c_domain(getattr(self, 'current_prompt', ''))
        readme_content = (
            f"# {self.project_name}\n\n"
            f"A {runtime} implementation of {domain} with build and test support.\n\n"
            "## Build\n\n"
            "```sh\nmake\n```\n\n"
            "## Run\n\n"
            f"```sh\n./{self.project_name}\n```\n\n"
            "## Test\n\n"
            "```sh\nmake test\n```\n"
        )
        user_manual_content = (
            "# User Manual\n\n"
            f"This project provides a {runtime} {domain} library and an example application.\n\n"
            "## Build Instructions\n1. Run `make` to compile the executable.\n2. Run `make test` to build and execute the test runner.\n\n"
            f"## Usage\n1. Build the code with `make`.\n2. Execute `./{self.project_name}`.\n3. The program demonstrates operations on the {domain} component.\n"
        )
        write_file(readme, readme_content)
        write_file(user_manual, user_manual_content)

    def _run_design_stage(self, design_output: str, delta_path: str):
        try:
            from agents.base_agent import BaseAgent as _BaseAgent
            design_agent_wrapper = _BaseAgent("design_agent")
            design_agent_wrapper.get_agent(tools=[read_project_file, write_project_file])
        except Exception as e:
            print(f"Could not import BaseAgent for design stage: {e}. Proceeding with fallback.")
            design_agent_wrapper = None

        design_task_vars = {
            "reports_dir": self.reports_dir,
            "delta_path": delta_path
        }
        self._run_single_stage(
            design_agent_wrapper,
            "design_task",
            design_task_vars,
            output_file=design_output,
            tools=[read_project_file, write_project_file]
        )

    def _run_code_stage(self, code_agent_wrapper: BaseAgent, code_output, dependency_path: str, reuse_path: str, delta_path: str):
        existing_source_code = self._collect_existing_source_code()
        code_task_vars = {
            "reports_dir": self.reports_dir,
            "project_dir": self.project_dir,
            "existing_source_code": existing_source_code,
            "dependency_graph_path": dependency_path,
            "reuse_report_path": reuse_path,
            "delta_report_path": delta_path
        }
        # Use the unified _run_single_stage which has a Crew fallback
        return self._run_single_stage(
            code_agent_wrapper,
            "code_task",
            code_task_vars,
            output_file=code_output,
            tools=[read_project_file, write_project_file, list_project_files, analyze_python_ast]
        )

    def _run_testing_stage(self, testing_output_dir: str, test_impact_path: str):
        try:
            from agents.base_agent import BaseAgent as _BaseAgent
            testing_agent_name = "c_testing_agent" if self.project_language in {"c", "cpp"} else "testing_agent"
            testing_agent_wrapper = _BaseAgent(testing_agent_name)
        except Exception as e:
            print(f"Could not import BaseAgent for testing stage: {e}. Proceeding with fallback.")
            testing_agent_wrapper = None

        testing_task_vars = {
            "project_dir": self.project_dir,
            "reports_dir": self.reports_dir,
            "test_impact_path": test_impact_path
        }
        self._run_single_stage(
            testing_agent_wrapper,
            "testing_task",
            testing_task_vars,
            output_file=None,
            tools=[read_project_file, write_project_file, list_project_files]
        )

    def _run_documentation_stage(self, doc_output_dir: str):
        try:
            from agents.base_agent import BaseAgent as _BaseAgent
            doc_agent_wrapper = _BaseAgent("documentation_agent")
            doc_agent = doc_agent_wrapper.get_agent(tools=[read_project_file, write_project_file])
        except Exception as e:
            print(f"Could not import BaseAgent for documentation stage: {e}. Proceeding with fallback.")
            doc_agent_wrapper = None
            doc_agent = None

        doc_task_vars = {
            "project_dir": self.project_dir,
            "reports_dir": self.reports_dir
        }
        self._run_single_stage(
            doc_agent_wrapper,
            "documentation_task",
            doc_task_vars,
            output_file=None,
            tools=[read_project_file, write_project_file]
        )

    def _collect_existing_source_code(self) -> str:
        existing_source_code = ""
        valid_exts = {".c", ".cpp", ".cc", ".cxx", ".h", ".hpp", ".hxx", ".py", ".md", ".json", ".txt", ".ini"}
        for root, dirs, files in os.walk(self.project_dir):
            if any(ignored in root for ignored in [".venv", "__pycache__", ".git", ".pytest_cache", "tests"]):
                continue
            for file in files:
                ext = os.path.splitext(file)[1].lower()
                if file != "Makefile" and ext not in valid_exts:
                    continue
                filepath = os.path.join(root, file)
                rel_path = os.path.relpath(filepath, self.project_dir)
                content = read_file(filepath)
                existing_source_code += f"\n--- FILE: {rel_path} ---\n{content}\n"
        return existing_source_code if existing_source_code else "No existing source code."

    def _guess_impacted_modules(self, classified_requirements):
        ext = ".cpp" if getattr(self, "project_language", "") == "cpp" else (".c" if getattr(self, "project_language", "") == "c" else ".py")
        changed = []
        for item in classified_requirements:
            if item["tag"] in {"NEW", "MODIFIED", "REMOVED"}:
                keyword = re.sub(r"[^a-zA-Z0-9_]+", "_", item["text"]).strip("_")
                candidate = None
                if keyword:
                    candidate = f"{keyword.split('_')[0]}{ext}"
                changed.append(candidate or item["section"])
        return [module for module in sorted(set(changed)) if module]

    def _update_db_registry_and_run(self, mode: str):
        """Scan project and reports directories to update file hashes and log the run."""
        srs_path = os.path.join(self.reports_dir, "SRS.md")
        design_path = os.path.join(self.reports_dir, "Design.md")

        srs_hash = calculate_hash(srs_path)
        design_hash = calculate_hash(design_path)

        # Register reports files
        if srs_hash:
            self.db.register_file(self.project_id, srs_path, "spec", srs_hash)
        if design_hash:
            self.db.register_file(self.project_id, design_path, "spec", design_hash)

        # Scan and register project files
        for root, dirs, files in os.walk(self.project_dir):
            # Skip python caching/virtual env
            if any(ignored in root for ignored in [".venv", "__pycache__", ".git", ".pytest_cache"]):
                continue
            
            is_test_dir = "tests" in os.path.split(root)
            for file in files:
                file_path = os.path.join(root, file)
                content_hash = calculate_hash(file_path)
                
                # Categorize file type
                if is_test_dir or file.startswith("test_"):
                    file_type = "test"
                elif file.endswith(".md"):
                    file_type = "doc"
                elif file.endswith(".py"):
                    file_type = "source"
                else:
                    file_type = "source" # Fallback

                self.db.register_file(self.project_id, file_path, file_type, content_hash)

        # Log the run
        status = "success" if os.path.exists(srs_path) else "failed"
        self.db.log_run(self.project_id, srs_hash, design_hash, status)
        print(f"Logged SDLC run state in SQLite for project ID {self.project_id}.")


