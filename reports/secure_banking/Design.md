# Design Document

## Architecture Overview
The project is a C application providing the `secure_banking` module.

## Module Specifications
- `secure_banking.h`: Public API declarations for the Secure Banking component.
- `secure_banking.c`: Implementation of Secure Banking core logic.
- `main.c`: Interactive command-line interface accepting dynamic user inputs.
- `tests/test_runner.c`: Automated assertion test suite.

## Data Model
- Data structures and function signatures declared in `secure_banking.h`.

## Sequence Flow
```mermaid
sequenceDiagram
    participant User
    participant Main CLI
    participant Secure_banking Engine

    User->>Main CLI: launch program & provide input choices
    Main CLI->>Secure_banking Engine: call domain operations
    Secure_banking Engine-->>Main CLI: return results / error status
    Main CLI-->>User: display output in console
```
