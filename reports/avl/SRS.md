# Software Requirements Specification (SRS)
## 1. Document Overview & Project Vision
## System Purpose
- [NEW] The system is designed to implement an AVL (Adelson-Velsky and Landis) tree data structure in C programming language. The AVL tree is a self-balancing binary search tree where the difference between heights of left and right subtrees cannot be more than one for all nodes.
## Domain Goals
- [NEW] To provide efficient insertion, deletion, and lookup operations with O(log n) time complexity.
- [NEW] To ensure the tree remains balanced after each operation to maintain optimal performance.
## High-Level Scope
- [NEW] The system will focus on the AVL tree implementation in C, including basic operations such as insert, delete, search, and balance. The scope does not include graphical user interfaces or external database integrations.
## 2. User Personas & System Scope
## Target Users
- [NEW] Developers who need a reliable AVL tree implementation for their projects.
- [NEW] Students learning about self-balancing binary trees.
## Operational Environment
- [NEW] The system will run on any standard C compiler environment, including Windows, Linux, and macOS.
- [NEW] No specific hardware requirements are necessary beyond basic computer resources sufficient to compile and execute C programs.
## Dependencies
- [NEW] Standard C library (stdlib.h, stdio.h).
- [NEW] No external libraries or dependencies are required.
## 3. Functional Requirements
## Core Operations
- [NEW] The system shall provide a function `insert(int value)` that inserts an integer into the AVL tree while maintaining balance.
- [NEW] The system shall provide a function `delete(int value)` that removes an integer from the AVL tree while maintaining balance.
- [NEW] The system shall provide a function `search(int value)` that returns whether an integer exists in the AVL tree.
## Input Validation & Error Handling
- [NEW] The system shall validate input values to ensure they are integers and handle invalid inputs gracefully by returning appropriate error messages or codes.
## Data Processing
- [NEW] The system shall automatically balance the tree after each insertion or deletion operation to maintain O(log n) performance.
- [NEW] The system shall provide a function `height()` that returns the height of the AVL tree.
## Status Monitoring
- [NEW] The system shall provide a function `isBalanced()` that checks if the AVL tree is balanced.
## 4. Non-Functional Requirements
## Performance & Latency
- [NEW] The system shall ensure all operations (insert, delete, search) have an average time complexity of O(log n).
## Reliability & Boundary Handling
- [NEW] The system shall handle edge cases such as inserting duplicate values by ignoring them or updating the existing node.
- [NEW] The system shall handle memory allocation failures gracefully and provide appropriate error handling.
## Maintainability & Standards
- [NEW] The system shall follow C programming standards and best practices for code readability and maintainability.
- [NEW] The system shall include comments in the code to explain complex logic and data structures.
## Build & Test Verification
- [NEW] The system shall provide a Makefile or build script to compile the AVL tree implementation.
- [NEW] The system shall include unit tests for each function to verify correctness and performance.
## 5. Interface & Operational Constraints
## CLI/API Contracts
- [NEW] The system shall expose a command-line interface (CLI) with commands such as `insert`, `delete`, `search`, `height`, and `isBalanced`.
- [NEW] The system shall accept input values via the command line and output results to the console.
## Data Formats
- [NEW] The system shall use plain text for input and output, with each operation result displayed on a new line.
## Exit Codes
- [NEW] The system shall return exit code 0 for successful operations.
- [NEW] The system shall return non-zero exit codes for errors such as invalid input or memory allocation failures.
