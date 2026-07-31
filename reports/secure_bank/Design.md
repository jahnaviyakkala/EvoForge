# Design Document

## Architecture Overview
The project is organized as a modular Python application centered on the `secure_bank` module.

## Module Specifications
- `secure_bank.py`: Core domain logic and operations.
- `main.py`: Application entry point and demonstration CLI.
- `tests/test_secure_bank.py`: Pytest suite for automated testing.

## Sequence Flow
```mermaid
sequenceDiagram
    participant User
    participant Main
    participant Secure_bankService

    User->>Main: execute program
    Main->>Secure_bankService: perform operation
    Secure_bankService-->>Main: return result
    Main-->>User: display output
```
