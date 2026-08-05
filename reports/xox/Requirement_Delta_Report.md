# Requirement Delta Report

## Summary
- New requirements: 57
- Modified requirements: 0
- Removed requirements: 0
- Unchanged requirements: 0

## Detailed Requirement Delta

### 1.1 Purpose

- [NEW] The purpose of this Software Requirements Specification (SRS) is to define the functional and non‑functional requirements for a command‑line tic‑tac‑toe (XOX) game implemented in C++. The specification serves as a contract between stakeholders, developers, testers, and maintainers.

### 1.2 System Vision

- [NEW] The system shall provide an interactive, two‑player tic‑tac‑toe experience that can be played entirely within a terminal or console window. It will support basic gameplay features such as move validation, win/draw detection, and game restart/quit options while maintaining high usability and reliability.

### 1.3 Product Perspective

- [NEW] This product is a stand‑alone executable with no external dependencies beyond the standard C++ runtime libraries. It may be integrated into larger educational or gaming suites but will function independently when compiled and executed on any platform that supports ISO C++17 or later.

### 1.4 User Characteristics

- [NEW] **Primary Users**: Individuals who wish to play a simple two‑player tic‑tac‑toe game via the command line.
- [NEW] **Skill Level**: No programming knowledge required; basic familiarity with terminal commands is sufficient.
- [NEW] **Accessibility**: The interface uses plain text and standard keyboard input, making it accessible to users with visual impairments when combined with screen readers.

### 1.5 Definitions & Acronyms

- [NEW] | Term | Definition |
- [NEW] |------|------------|
- [NEW] | XOX | Tic‑tac‑toe game (also known as “noughts and crosses”) |
- [NEW] | CLI | Command Line Interface |
- [NEW] | NFR | Non‑Functional Requirement |
- [NEW] | FR | Functional Requirement |
- [NEW] | OC | Operational Constraint |

### 2. References & Applicable Standards

- [NEW] ISO/IEC/IEEE 29148:2018 – Software Requirements Specifications
- [NEW] C++ Standard (ISO/IEC 14882:2020)
- [NEW] ANSI X3.64 – Command Line Interface Conventions

### 3.1 External Interface Requirements

- [NEW] **[NEW]** The system shall provide a command‑line interface that accepts user input for moves in the format “row,column” where row and column are integers from 1 to 3.
- [NEW] **[NEW]** The system shall display the current state of the tic‑tac‑toe board after each move, using ‘X’, ‘O’, or blank spaces.

### 3.2 System Capabilities & Functional Requirements

- [NEW] **[NEW] FR1:** The system shall allow two human players to play a game of tic‑tac‑toe on a 3×3 grid.
- [NEW] **[NEW] FR2:** The system shall enforce alternating turns between Player X and Player O, starting with Player X.
- [NEW] **[NEW] FR3:** The system shall validate that each move is within the bounds of the board (rows 1–3, columns 1–3).
- [NEW] **[NEW] FR4:** The system shall reject a move if the chosen cell is already occupied, prompting the player to enter a different move.
- [NEW] **[NEW] FR5:** The system shall detect when a player has achieved three marks in a horizontal, vertical, or diagonal line and declare that player as the winner.
- [NEW] **[NEW] FR6:** The system shall detect a draw condition when all cells are occupied without any winning line and declare the game a draw.
- [NEW] **[NEW] FR7:** The system shall allow players to restart the game after completion by entering a specific command (e.g., “restart”).
- [NEW] **[NEW] FR8:** The system shall provide an option for a player to quit the current game session at any time by entering a specific command (e.g., “quit”).

### 3.3 System Quality Attributes & Non‑Functional Requirements

- [NEW] **[NEW] NFR1:** Performance – The system shall respond to user input and update the board display within 200 milliseconds under normal operating conditions.
- [NEW] **[NEW] NFR2:** Reliability – The system shall maintain correct game state across all valid inputs without loss or corruption of data.
- [NEW] **[NEW] NFR3:** Usability – The command‑line interface shall be intuitive, displaying clear prompts and error messages in plain text.
- [NEW] **[NEW] NFR4:** Maintainability – The source code shall be organized into modular components with clear separation of concerns to facilitate future enhancements.
- [NEW] **[NEW] NFR5:** Security – As a local application, the system shall not expose any network interfaces or external dependencies that could lead to security vulnerabilities.

### 3.4 Operational & Design Constraints

- [NEW] **[NEW] OC1:** Memory – The application shall use no more than 10 MB of RAM during execution.
- [NEW] **[NEW] OC2:** Execution Limits – The application shall terminate gracefully with exit code 0 upon normal completion or exit code 1 if an unrecoverable error occurs.

### 4. Verification Criteria & Acceptance Tests

- [NEW] | Req ID | Test Description | Expected Result |
- [NEW] |--------|------------------|-----------------|
- [NEW] | FR1 | Start a new game and verify two players can make moves alternately. | Game proceeds with alternating turns; no player is skipped. |
- [NEW] | FR2 | Attempt to play out of turn (e.g., Player X tries to move twice). | System rejects the second move and prompts for correct turn. |
- [NEW] | FR3 | Input a move “4,1” or “0,2”. | System reports invalid coordinates and requests a new input. |
- [NEW] | FR4 | Move to an already occupied cell. | System informs that the cell is taken and asks for another position. |
- [NEW] | FR5 | Create a winning line (e.g., X occupies 1,1; 1,2; 1,3). | System declares Player X as winner immediately after third move. |
- [NEW] | FR6 | Fill all nine cells without any winning line. | System declares the game a draw after last move. |
- [NEW] | FR7 | After a win or draw, input “restart”. | Board resets to empty state and prompts for new first move. |
- [NEW] | FR8 | Input “quit” during gameplay. | Application exits with exit code 0 and displays goodbye message. |
- [NEW] | NFR1 | Measure response time from input to board update on average hardware. | Response time ≤ 200 ms. |
- [NEW] | NFR2 | Replay a long sequence of valid moves; verify final state matches expected. | Final board state is correct, no data loss. |
- [NEW] | NFR3 | Observe prompts and error messages for clarity and consistency. | Messages are concise, unambiguous, and correctly formatted. |
- [NEW] | OC1 | Monitor memory usage during continuous play. | Peak RAM consumption ≤ 10 MB. |
- [NEW] | OC2 | Trigger an unrecoverable error (e.g., simulate file I/O failure). | Application exits with code 1 after displaying error message. |

### 5.1 Glossary

- [NEW] **Move**: A player's action of placing their mark on a specific cell.
- [NEW] **Turn**: The period during which a single player may make a move.
- [NEW] **Winning Line**: Three identical marks aligned horizontally, vertically, or diagonally.

### 5.2 Assumption Log

- [NEW] | # | Assumption | Rationale |
- [NEW] |---|------------|-----------|
- [NEW] | 1 | Users will run the executable in a terminal that supports UTF‑8 and basic ANSI escape codes. | Required for clear board rendering. |
- [NEW] | 2 | Input will be entered via standard keyboard; no mouse interaction is expected. | Simplifies interface design. |
- [NEW] | 3 | The application runs on platforms with at least 512 MB of available RAM. | Meets the memory constraint comfortably. |
- [NEW] ---
