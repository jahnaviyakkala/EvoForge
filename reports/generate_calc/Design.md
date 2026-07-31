# Design Document

## Architecture Overview
The project is a C application providing the `generate_calc` module.

## Module Specifications
- `generate_calc.h`: Public API declarations for the Generate Calc component.
- `generate_calc.c`: Implementation of Generate Calc core logic.
- `main.c`: Interactive command-line interface accepting dynamic user inputs.
- `tests/test_runner.c`: Automated assertion test suite.

## Data Model
- Data structures and function signatures declared in `generate_calc.h`.

## Sequence Flow
```mermaid
sequenceDiagram
    participant User
    participant Main CLI
    participant Generate_calc Engine

    User->>Main CLI: launch program & provide input choices
    Main CLI->>Generate_calc Engine: call domain operations
    Generate_calc Engine-->>Main CLI: return results / error status
    Main CLI-->>User: display output in console
```
