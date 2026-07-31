# Design Document

## Architecture Overview
The project is a C application providing the `scientifc_calc` module.

## Module Specifications
- `scientifc_calc.h`: Public API declarations for the Scientifc Calc component.
- `scientifc_calc.c`: Implementation of Scientifc Calc core logic.
- `main.c`: Interactive command-line interface accepting dynamic user inputs.
- `tests/test_runner.c`: Automated assertion test suite.

## Data Model
- Data structures and function signatures declared in `scientifc_calc.h`.

## Sequence Flow
```mermaid
sequenceDiagram
    participant User
    participant Main CLI
    participant Scientifc_calc Engine

    User->>Main CLI: launch program & provide input choices
    Main CLI->>Scientifc_calc Engine: call domain operations
    Scientifc_calc Engine-->>Main CLI: return results / error status
    Main CLI-->>User: display output in console
```
