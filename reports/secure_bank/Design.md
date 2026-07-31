# Design Document

## Architecture Overview
The project is a C application providing the `secure_bank` module.

## Module Specifications
- `secure_bank.h`: Public API declarations for the Secure Bank component.
- `secure_bank.c`: Implementation of Secure Bank core logic.
- `main.c`: Interactive command-line interface accepting dynamic user inputs.
- `tests/test_runner.c`: Automated assertion test suite.

## Data Model
- Data structures and function signatures declared in `secure_bank.h`.

## Sequence Flow
```mermaid
sequenceDiagram
    participant User
    participant Main CLI
    participant Secure_bank Engine

    User->>Main CLI: launch program & provide input choices
    Main CLI->>Secure_bank Engine: call domain operations
    Secure_bank Engine-->>Main CLI: return results / error status
    Main CLI-->>User: display output in console
```
