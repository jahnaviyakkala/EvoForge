# Reuse Decision Report

## Reusable Components Detected

- Function `getHeight` in `avl.h` with args: 
- Function `getBalanceFactor` in `avl.h` with args: 
- Function `rotateRight` in `avl.h` with args: 
- Function `rotateLeft` in `avl.h` with args: 
- Function `insertNode` in `avl.h` with args: 
- Function `freeTree` in `avl.h` with args: 
- Function `searchNode` in `avl.h` with args: 
- Function `getHeight` in `avl.c` with args: 
- Function `getBalanceFactor` in `avl.c` with args: 
- Function `rotateRight` in `avl.c` with args: 
- Function `rotateLeft` in `avl.c` with args: 
- Function `insertNode` in `avl.c` with args: 
- Function `freeTree` in `avl.c` with args: 
- Function `searchNode` in `avl.c` with args: 
- Function `insert` in `main.c` with args: 
- Function `search` in `main.c` with args: 
- Function `searchNode` in `main.c` with args: 
- Function `freeMemory` in `main.c` with args: 
- Function `main` in `main.c` with args: 
- Function `printf` in `main.c` with args: 
- Function `test_insert` in `tests/test_runner.c` with args: 
- Function `test_insert_duplicates` in `tests/test_runner.c` with args: 
- Function `test_search` in `tests/test_runner.c` with args: 
- Function `test_delete` in `tests/test_runner.c` with args: 
- Function `test_height` in `tests/test_runner.c` with args: 
- Function `test_isBalanced` in `tests/test_runner.c` with args: 
- Function `main` in `tests/test_runner.c` with args: 

## Reuse Decisions

- [NEW] `[UNCHANGED] The system is designed to implement an AVL (Adelson‑Velsky and Landis) tree data structure in **C++** programming language. The AVL tree is a self‑balancing binary search tree where the difference between heights of left and right subtrees cannot be more than one for all nodes.` requires new implementation. No strong reusable component found.
- [NEW] `[MODIFIED] Provide efficient insertion, deletion, and lookup operations with O(log n) time complexity.` requires new implementation. No strong reusable component found.
- [NEW] `[MODIFIED] Ensure the tree remains balanced after each operation to maintain optimal performance.` requires new implementation. No strong reusable component found.
- [NEW] `[MODIFIED] The system will focus on the AVL tree implementation in C++, including basic operations such as insert, delete, search, height calculation, and balance checking. The scope does **not** include graphical user interfaces or external database integrations.` requires new implementation. No strong reusable component found.
- [NEW] `[UNCHANGED] Developers who need a reliable AVL tree implementation for their projects.` requires new implementation. No strong reusable component found.
- [NEW] `[UNCHANGED] Students learning about self‑balancing binary trees.` requires new implementation. No strong reusable component found.
- [NEW] `[NEW] The system will run on any standard C++ compiler environment, including Windows, Linux, and macOS. No specific hardware requirements are necessary beyond basic computer resources sufficient to compile and execute C++ programs.` requires new implementation. No strong reusable component found.
- [NEW] `[REMOVED] The system will run on any standard C compiler environment, including Windows, Linux, and macOS.` requires new implementation. No strong reusable component found.
- [NEW] `[REMOVED] No specific hardware requirements are necessary beyond basic computer resources sufficient to compile and execute C programs.` requires new implementation. No strong reusable component found.
- [NEW] `[NEW] Standard C++ library (e.g., `<iostream>`, `<memory>`). No external libraries or dependencies are required.` requires new implementation. No strong reusable component found.
- [NEW] `[REMOVED] Standard C library (stdlib.h, stdio.h).` requires new implementation. No strong reusable component found.
- [NEW] `[REMOVED] No external libraries or dependencies are required.` requires new implementation. No strong reusable component found.
- [NEW] `[MODIFIED] **[NEW]** The system shall provide a function `insert(int value)` that inserts an integer into the AVL tree while maintaining balance.` requires new implementation. No strong reusable component found.
- [NEW] `[MODIFIED] **[NEW]** The system shall provide a function `remove(int value)` that removes an integer from the AVL tree while maintaining balance.` requires new implementation. No strong reusable component found.
- [NEW] `[MODIFIED] **[NEW]** The system shall provide a function `search(int value)` that returns whether an integer exists in the AVL tree.` requires new implementation. No strong reusable component found.
- [NEW] `[MODIFIED] **[NEW]** The system shall validate input values to ensure they are integers and handle invalid inputs gracefully by returning appropriate error codes or messages.` requires new implementation. No strong reusable component found.
- [NEW] `[NEW] **[NEW]** The system shall detect and reject attempts to insert duplicate values, either by ignoring the insertion or updating the existing node, as specified in the configuration.` requires new implementation. No strong reusable component found.
- [NEW] `[MODIFIED] **[NEW]** The system shall automatically balance the tree after each insertion or deletion operation to maintain O(log n) performance.` requires new implementation. No strong reusable component found.
- [NEW] `[MODIFIED] **[NEW]** The system shall provide a function `height()` that returns the height of the AVL tree.` requires new implementation. No strong reusable component found.
- [NEW] `[MODIFIED] **[NEW]** The system shall provide a function `isBalanced()` that checks if the AVL tree is balanced.` requires new implementation. No strong reusable component found.
- [NEW] `[MODIFIED] **[NEW]** The system shall ensure all operations (insert, remove, search) have an average time complexity of O(log n).` requires new implementation. No strong reusable component found.
- [NEW] `[MODIFIED] **[NEW]** The system shall handle edge cases such as inserting duplicate values by ignoring them or updating the existing node.` requires new implementation. No strong reusable component found.
- [NEW] `[NEW] **[NEW]** The system shall handle memory allocation failures gracefully and provide appropriate error handling, returning a distinct error code to indicate failure.` requires new implementation. No strong reusable component found.
- [NEW] `[REMOVED] The system shall handle memory allocation failures gracefully and provide appropriate error handling.` requires new implementation. No strong reusable component found.
- [NEW] `[MODIFIED] **[MODIFIED]** The system shall follow C++ programming standards and best practices for code readability and maintainability.` requires new implementation. No strong reusable component found.
- [NEW] `[MODIFIED] **[MODIFIED]** The system shall include comments in the code to explain complex logic and data structures.` requires new implementation. No strong reusable component found.
- [NEW] `[MODIFIED] **[NEW]** The system shall provide a Makefile or build script to compile the AVL tree implementation.` requires new implementation. No strong reusable component found.
- [NEW] `[MODIFIED] **[NEW]** The system shall include unit tests for each function to verify correctness and performance.` requires new implementation. No strong reusable component found.
- [NEW] `[NEW] The system shall expose a command‑line interface (CLI) with commands such as `insert`, `remove`, `search`, `height`, and `isBalanced`. The CLI accepts input values via the command line and outputs results to the console.` requires new implementation. No strong reusable component found.
- [NEW] `[REMOVED] The system shall expose a command-line interface (CLI) with commands such as `insert`, `delete`, `search`, `height`, and `isBalanced`.` requires new implementation. No strong reusable component found.
- [NEW] `[REMOVED] The system shall accept input values via the command line and output results to the console.` requires new implementation. No strong reusable component found.
- [NEW] `[UNCHANGED] The system shall use plain text for input and output, with each operation result displayed on a new line.` requires new implementation. No strong reusable component found.
- [NEW] `[MODIFIED] **[NEW]** The system shall return exit code 0 for successful operations.` requires new implementation. No strong reusable component found.
- [NEW] `[MODIFIED] **[NEW]** The system shall return non‑zero exit codes for errors such as invalid input or memory allocation failures.` requires new implementation. No strong reusable component found.
