# Design Document

## Architecture Overview
The project is a C application providing the `miniature_sql` module.

## Module Specifications
- `miniature_sql.h`: Public API declarations for the Miniature Sql component.
- `miniature_sql.c`: Implementation of Miniature Sql core logic.
- `main.c`: Interactive command-line interface accepting dynamic user inputs.
- `tests/test_runner.c`: Automated assertion test suite.

## Data Model
- Data structures and function signatures declared in `miniature_sql.h`.

## Sequence Flow
```mermaid
sequenceDiagram
    participant User
    participant Main CLI
    participant Miniature_sql Engine

    User->>Main CLI: launch program & provide input choices
    Main CLI->>Miniature_sql Engine: call domain operations
    Miniature_sql Engine-->>Main CLI: return results / error status
    Main CLI-->>User: display output in console
```
