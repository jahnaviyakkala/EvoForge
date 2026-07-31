# Design Document

## Architecture Overview
The project is organized as a modular Python application centered on the `bank` module.

## Module Specifications
- `bank.py`: Core domain logic and operations.
- `main.py`: Application entry point and demonstration CLI.
- `tests/test_bank.py`: Pytest suite for automated testing.

## Sequence Flow
```mermaid
sequenceDiagram
    participant User
    participant Main
    participant BankService

    User->>Main: execute program
    Main->>BankService: perform operation
    BankService-->>Main: return result
    Main-->>User: display output
```
