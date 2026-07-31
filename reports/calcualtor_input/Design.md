# Design Document

## Architecture Overview
The project is a C++ application providing the `calcualtor_input` module.

## Module Specifications
- `calcualtor_input.hpp`: Public API declarations for the Calcualtor Input component.
- `calcualtor_input.cpp`: Implementation of Calcualtor Input core logic.
- `main.cpp`: Interactive command-line interface accepting dynamic user inputs.
- `tests/test_runner.cpp`: Automated assertion test suite.

## Data Model
- Data structures and function signatures declared in `calcualtor_input.hpp`.

## Sequence Flow
```mermaid
sequenceDiagram
    participant User
    participant Main CLI
    participant Calcualtor_input Engine

    User->>Main CLI: launch program & provide input choices
    Main CLI->>Calcualtor_input Engine: call domain operations
    Calcualtor_input Engine-->>Main CLI: return results / error status
    Main CLI-->>User: display output in console
```
