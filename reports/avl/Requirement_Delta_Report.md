# Requirement Delta Report

## Summary
- New requirements: 5
- Modified requirements: 18
- Removed requirements: 7
- Unchanged requirements: 4

## Detailed Requirement Delta

### System Purpose

- [UNCHANGED] The system is designed to implement an AVL (Adelson‑Velsky and Landis) tree data structure in **C++** programming language. The AVL tree is a self‑balancing binary search tree where the difference between heights of left and right subtrees cannot be more than one for all nodes.

### Domain Goals

- [MODIFIED] Provide efficient insertion, deletion, and lookup operations with O(log n) time complexity. (matched old requirement: To provide efficient insertion, deletion, and lookup operations with O(log n) time complexity.)
- [MODIFIED] Ensure the tree remains balanced after each operation to maintain optimal performance. (matched old requirement: To ensure the tree remains balanced after each operation to maintain optimal performance.)

### High‑Level Scope

- [MODIFIED] The system will focus on the AVL tree implementation in C++, including basic operations such as insert, delete, search, height calculation, and balance checking. The scope does **not** include graphical user interfaces or external database integrations. (matched old requirement: The system will focus on the AVL tree implementation in C, including basic operations such as insert, delete, search, and balance. The scope does not include graphical user interfaces or external database integrations.)

### Target Users

- [UNCHANGED] Developers who need a reliable AVL tree implementation for their projects.
- [UNCHANGED] Students learning about self‑balancing binary trees.

### Operational Environment

- [NEW] The system will run on any standard C++ compiler environment, including Windows, Linux, and macOS. No specific hardware requirements are necessary beyond basic computer resources sufficient to compile and execute C++ programs.
- [REMOVED] The system will run on any standard C compiler environment, including Windows, Linux, and macOS. (matched old requirement: The system will run on any standard C compiler environment, including Windows, Linux, and macOS.)
- [REMOVED] No specific hardware requirements are necessary beyond basic computer resources sufficient to compile and execute C programs. (matched old requirement: No specific hardware requirements are necessary beyond basic computer resources sufficient to compile and execute C programs.)

### Dependencies

- [NEW] Standard C++ library (e.g., `<iostream>`, `<memory>`). No external libraries or dependencies are required.
- [REMOVED] Standard C library (stdlib.h, stdio.h). (matched old requirement: Standard C library (stdlib.h, stdio.h).)
- [REMOVED] No external libraries or dependencies are required. (matched old requirement: No external libraries or dependencies are required.)

### Core Operations

- [MODIFIED] **[NEW]** The system shall provide a function `insert(int value)` that inserts an integer into the AVL tree while maintaining balance. (matched old requirement: The system shall provide a function `insert(int value)` that inserts an integer into the AVL tree while maintaining balance.)
- [MODIFIED] **[NEW]** The system shall provide a function `remove(int value)` that removes an integer from the AVL tree while maintaining balance. (matched old requirement: The system shall provide a function `delete(int value)` that removes an integer from the AVL tree while maintaining balance.)
- [MODIFIED] **[NEW]** The system shall provide a function `search(int value)` that returns whether an integer exists in the AVL tree. (matched old requirement: The system shall provide a function `search(int value)` that returns whether an integer exists in the AVL tree.)

### Input Validation & Error Handling

- [MODIFIED] **[NEW]** The system shall validate input values to ensure they are integers and handle invalid inputs gracefully by returning appropriate error codes or messages. (matched old requirement: The system shall validate input values to ensure they are integers and handle invalid inputs gracefully by returning appropriate error messages or codes.)
- [NEW] **[NEW]** The system shall detect and reject attempts to insert duplicate values, either by ignoring the insertion or updating the existing node, as specified in the configuration.

### Data Processing

- [MODIFIED] **[NEW]** The system shall automatically balance the tree after each insertion or deletion operation to maintain O(log n) performance. (matched old requirement: The system shall automatically balance the tree after each insertion or deletion operation to maintain O(log n) performance.)
- [MODIFIED] **[NEW]** The system shall provide a function `height()` that returns the height of the AVL tree. (matched old requirement: The system shall provide a function `height()` that returns the height of the AVL tree.)

### Status Monitoring

- [MODIFIED] **[NEW]** The system shall provide a function `isBalanced()` that checks if the AVL tree is balanced. (matched old requirement: The system shall provide a function `isBalanced()` that checks if the AVL tree is balanced.)

### Performance & Latency

- [MODIFIED] **[NEW]** The system shall ensure all operations (insert, remove, search) have an average time complexity of O(log n). (matched old requirement: The system shall ensure all operations (insert, delete, search) have an average time complexity of O(log n).)

### Reliability & Boundary Handling

- [MODIFIED] **[NEW]** The system shall handle edge cases such as inserting duplicate values by ignoring them or updating the existing node. (matched old requirement: The system shall handle edge cases such as inserting duplicate values by ignoring them or updating the existing node.)
- [NEW] **[NEW]** The system shall handle memory allocation failures gracefully and provide appropriate error handling, returning a distinct error code to indicate failure.
- [REMOVED] The system shall handle memory allocation failures gracefully and provide appropriate error handling. (matched old requirement: The system shall handle memory allocation failures gracefully and provide appropriate error handling.)

### Maintainability & Standards

- [MODIFIED] **[MODIFIED]** The system shall follow C++ programming standards and best practices for code readability and maintainability. (matched old requirement: The system shall follow C programming standards and best practices for code readability and maintainability.)
- [MODIFIED] **[MODIFIED]** The system shall include comments in the code to explain complex logic and data structures. (matched old requirement: The system shall include comments in the code to explain complex logic and data structures.)

### Build & Test Verification

- [MODIFIED] **[NEW]** The system shall provide a Makefile or build script to compile the AVL tree implementation. (matched old requirement: The system shall provide a Makefile or build script to compile the AVL tree implementation.)
- [MODIFIED] **[NEW]** The system shall include unit tests for each function to verify correctness and performance. (matched old requirement: The system shall include unit tests for each function to verify correctness and performance.)

### CLI/API Contracts

- [NEW] The system shall expose a command‑line interface (CLI) with commands such as `insert`, `remove`, `search`, `height`, and `isBalanced`. The CLI accepts input values via the command line and outputs results to the console.
- [REMOVED] The system shall expose a command-line interface (CLI) with commands such as `insert`, `delete`, `search`, `height`, and `isBalanced`. (matched old requirement: The system shall expose a command-line interface (CLI) with commands such as `insert`, `delete`, `search`, `height`, and `isBalanced`.)
- [REMOVED] The system shall accept input values via the command line and output results to the console. (matched old requirement: The system shall accept input values via the command line and output results to the console.)

### Data Formats

- [UNCHANGED] The system shall use plain text for input and output, with each operation result displayed on a new line.

### Exit Codes

- [MODIFIED] **[NEW]** The system shall return exit code 0 for successful operations. (matched old requirement: The system shall return exit code 0 for successful operations.)
- [MODIFIED] **[NEW]** The system shall return non‑zero exit codes for errors such as invalid input or memory allocation failures. (matched old requirement: The system shall return non-zero exit codes for errors such as invalid input or memory allocation failures.)
