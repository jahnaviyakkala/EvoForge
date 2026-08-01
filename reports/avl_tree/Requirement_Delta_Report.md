# Requirement Delta Report

## Summary
- New requirements: 35
- Modified requirements: 0
- Removed requirements: 0
- Unchanged requirements: 0

## Detailed Requirement Delta

### System Purpose

- [NEW] The AVL Tree Implementation system is designed to provide a robust and efficient data structure for managing dynamic sets of data where operations such as insertion, deletion, and lookup are required to be balanced in terms of time complexity.

### Domain Goals

- [NEW] To ensure that the AVL Tree maintains balance after every insert or delete operation.
- [NEW] To provide an interface for users to input data into the AVL Tree.
- [NEW] To allow users to perform basic operations on the AVL Tree such as insertion, deletion, and lookup.

### High-Level Scope

- [NEW] The system will implement an AVL Tree in C++ with functionalities to handle user inputs for inserting elements into the tree. The system will ensure that the AVL property is maintained after each operation.

### Target Users

- [NEW] Developers who need a balanced binary search tree implementation.
- [NEW] Students and educators learning about AVL Trees and their properties.
- [NEW] Anyone requiring efficient data management with guaranteed logarithmic time complexity for operations.

### Operational Environment

- [NEW] The system will run on any standard C++ development environment supporting C++11 or later standards.
- [NEW] It will be compiled using a standard C++ compiler such as g++, clang++, or MSVC.

### Dependencies

- [NEW] Standard C++ library (STL) for basic data structures and algorithms.

### Core Operations

- [NEW] The system shall allow users to insert elements into the AVL Tree.
- [NEW] The system shall maintain the AVL property after each insertion operation.
- [NEW] The system shall allow users to delete elements from the AVL Tree.
- [NEW] The system shall maintain the AVL property after each deletion operation.
- [NEW] The system shall allow users to search for elements in the AVL Tree.

### Input Validation & Error Handling

- [NEW] The system shall validate user inputs to ensure they are integers.
- [NEW] The system shall handle invalid inputs by displaying an error message and prompting the user to re-enter valid data.

### Data Processing

- [NEW] The system shall process user inputs to insert, delete, or search for elements in the AVL Tree.
- [NEW] The system shall update the tree structure to maintain balance after each operation.

### Status Monitoring

- [NEW] The system shall provide feedback to the user about successful operations (e.g., "Element inserted successfully").
- [NEW] The system shall provide feedback to the user about failed operations (e.g., "Element not found").

### Performance & Latency

- [NEW] The system shall ensure that all operations (insert, delete, search) have a time complexity of O(log n).

### Reliability & Boundary Handling

- [NEW] The system shall handle edge cases such as inserting duplicate elements or deleting non-existent elements gracefully.
- [NEW] The system shall be robust against invalid inputs and maintain integrity of the AVL Tree.

### Maintainability & Standards

- [NEW] The code shall follow standard C++ coding practices and conventions.
- [NEW] The code shall include comments explaining complex logic and algorithms.

### Build & Test Verification

- [NEW] The system shall include a build script to compile the source code.
- [NEW] The system shall include unit tests to verify the correctness of each operation (insert, delete, search).

### CLI/API Contracts

- [NEW] The system shall provide a command-line interface for user interaction.
- [NEW] The system shall accept commands such as "insert", "delete", "search", and "exit".

### Data Formats

- [NEW] User inputs shall be integers.
- [NEW] Outputs shall be text-based feedback to the user.

### Exit Codes

- [NEW] The system shall return an exit code of 0 upon successful execution.
- [NEW] The system shall return a non-zero exit code in case of errors or exceptions.
