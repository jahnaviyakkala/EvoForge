import os
import shutil
import tempfile
import pytest
from agents.sdlc_crew import SDLCCrewManager, clean_markdown_content
from tools.requirement_tools import strip_tag_prefix, classify_requirements


def test_clean_markdown_content():
    raw_markdown = "```markdown\n# Title\n- [NEW] Req 1\n```"
    assert clean_markdown_content(raw_markdown) == "# Title\n- [NEW] Req 1"

    preamble_markdown = "Here is the result:\n```markdown\n# Header\nContent\n```\nHope this helps!"
    assert clean_markdown_content(preamble_markdown) == "# Header\nContent"

    plain_markdown = "# Simple Header\nJust text"
    assert clean_markdown_content(plain_markdown) == "# Simple Header\nJust text"


def test_strip_tag_prefix():
    assert strip_tag_prefix("- [NEW] The system shall add.") == "The system shall add."
    assert strip_tag_prefix("[MODIFIED] The system shall update.") == "The system shall update."
    assert strip_tag_prefix("[UNCHANGED] System shall stay.") == "System shall stay."
    assert strip_tag_prefix("[REMOVED] System shall delete.") == "System shall delete."


def test_extract_and_write_files():
    temp_dir = tempfile.mkdtemp()
    try:
        manager = SDLCCrewManager("temp_test_proj")
        manager.project_dir = temp_dir

        llm_response = """
Here is the code implementation:

--- FILE: app.py ---
```python
def run():
    return "running"
```

--- FILE: utils.py ---
```python
def helper():
    return 42
```
"""
        extracted = manager._extract_and_write_files(llm_response)
        assert "app.py" in extracted
        assert "utils.py" in extracted
        assert os.path.exists(os.path.join(temp_dir, "app.py"))
        assert os.path.exists(os.path.join(temp_dir, "utils.py"))
        with open(os.path.join(temp_dir, "app.py")) as f:
            content = f.read()
            assert "def run():" in content
            assert "```" not in content
    finally:
        shutil.rmtree(temp_dir)


def test_python_pipeline_fallback():
    temp_project = "test_py_calc_fallback"
    manager = SDLCCrewManager(temp_project)
    try:
        res = manager.run_pipeline("Build a python calculator app with add and divide.", mode="new")
        assert os.path.exists(res["srs"])
        assert os.path.exists(res["delta_report"])
        calc_py = os.path.join(manager.project_dir, "calculator.py")
        main_py = os.path.join(manager.project_dir, "main.py")
        test_py = os.path.join(manager.project_dir, "tests", "test_calculator.py")
        assert os.path.exists(calc_py)
        assert os.path.exists(main_py)
        assert os.path.exists(test_py)
    finally:
        # cleanup test files
        if os.path.exists(manager.project_dir):
            shutil.rmtree(manager.project_dir)
        if os.path.exists(manager.reports_dir):
            shutil.rmtree(manager.reports_dir)


def test_syntax_validation_and_self_correction():
    manager = SDLCCrewManager("temp_val_proj")
    
    # 1. Valid python code
    valid_py_map = {"app.py": "def add(a, b):\n    return a + b\n"}
    ok, msg = manager._validate_syntax(valid_py_map, "python")
    assert ok is True
    assert "passed" in msg

    # 2. Invalid python code (syntax error)
    invalid_py_map = {"app.py": "def add(a, b)\n    return a + b\n"}
    ok, msg = manager._validate_syntax(invalid_py_map, "python")
    assert ok is False
    assert "Python SyntaxError" in msg

    # 3. Valid C code
    valid_c_map = {
        "calc.h": "#ifndef CALC_H\n#define CALC_H\nint add(int a, int b);\n#endif\n",
        "calc.c": '#include "calc.h"\nint add(int a, int b) { return a + b; }\n',
        "main.c": '#include <stdio.h>\n#include "calc.h"\nint main() { printf("%d", add(2, 3)); return 0; }\n'
    }
    ok, msg = manager._validate_syntax(valid_c_map, "c")
    assert ok is True

    # 4. Invalid C code (missing semicolon)
    invalid_c_map = {
        "calc.h": "#ifndef CALC_H\n#define CALC_H\nint add(int a, int b);\n#endif\n",
        "calc.c": '#include "calc.h"\nint add(int a, int b) { return a + b }\n',
        "main.c": '#include <stdio.h>\n#include "calc.h"\nint main() { printf("%d", add(2, 3)); return 0; }\n'
    }
    ok, msg = manager._validate_syntax(invalid_c_map, "c")
    assert ok is False
    assert "Compiler Errors" in msg or "Compiler Error Output" in msg


def test_semantic_evaluation_tool(tmp_path):
    from tools.semantic_evaluation import evaluate_project_semantics, generate_semantic_evaluation_report
    
    srs = """
# SRS
## 3. Functional Requirements
- [NEW] The system shall add two numbers.
- [NEW] The system shall validate inputs and raise ValueError on invalid numbers.
"""
    proj_dir = tmp_path / "proj"
    proj_dir.mkdir()
    code_file = proj_dir / "calc.py"
    code_file.write_text("def add(a, b):\n    if not isinstance(a, (int, float)):\n        raise ValueError('Invalid')\n    return a + b\n")

    res = evaluate_project_semantics(str(proj_dir), srs, "python")
    assert res["is_semantically_valid"] is True
    assert res["score"] >= 0.7

    rep = generate_semantic_evaluation_report(res, str(tmp_path / "reports"))
    assert os.path.exists(rep)
    with open(rep) as f:
        txt = f.read()
        assert "Semantic Evaluation Report" in txt
        assert "PASSED" in txt
