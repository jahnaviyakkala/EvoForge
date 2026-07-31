# Software Requirements Specification (SRS)
## 1. Document Overview & System Purpose
- [NEW] The system shall provide a high-performance, standards-compliant Miniature Sql application written in C.
- [NEW] Specification Prompt: "Build a miniature SQL database engine in C++ supporting CREATE TABLE, INSERT, SELECT, DELETE, WHERE clauses, CSV-based storage, a SQL parser, comprehensive unit tests, a CMake build system, and complete documentation. in python"
## 2. User Personas & System Scope
- [NEW] **Target Users**: System users, software developers, and automated build pipelines.
- [NEW] **Compilation Tools**: GCC / G++ / Clang toolchains supporting POSIX Makefile builds.
- [NEW] **Dependencies**: Standard runtime libraries (`libc`/`libm` or `<iostream>`, `<cmath>`, `<cassert>`).
## 3. Functional Requirements
## 3.1 Core Application Capabilities
- [NEW] The system shall execute functional logic satisfying: Build a miniature SQL database engine in C++ supporting CREATE TABLE, INSERT, SELECT, DELETE, WHERE clauses, CSV-based storage, a SQL parser, comprehensive unit tests, a CMake build system, and complete documentation. in python.
- [NEW] The system shall provide standard module initialization, operational execution, and resource cleanup routines.
- [NEW] The system shall include an interactive CLI entry point (`main`) prompting users for runtime inputs dynamically.
## 3.2 Boundary Error & Memory Management
- [NEW] The system shall validate all boundary parameters (division by zero, null pointers, out-of-bounds inputs).
- [NEW] The system shall ensure clean memory management without heap leaks or buffer overruns.
## 4. Non-Functional Requirements
## 4.1 Performance & Memory Efficiency
- [NEW] High execution performance with minimal heap allocation overhead.
## 4.2 Code Standards & Architecture
- [NEW] Code structured into header files (`.h`/`.hpp`) and source files (`.c`/`.cpp`) with standard `#ifndef` include guards.
- [NEW] Warning-free compilation under strict GCC/G++ compiler flags.
## 4.3 Build System & Testing
- [NEW] POSIX Makefile supporting `make`, `make test`, and `make clean` targets.
- [NEW] Automated assertion test runner in `tests/test_runner`.
## 5. Interface Specifications
- [NEW] Interactive CLI menu loop accepting dynamic user input via standard input.
