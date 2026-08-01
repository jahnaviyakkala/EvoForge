#include "GameEngine.hpp"
#include <iostream>
#include <sstream>

GameEngine::GameEngine() {
    players.addPlayer("Player 1", 'X');
    players.addPlayer("Player 2", 'O');
}

void GameEngine::startGame() {
    board.initializeBoard(3);
    std::string input;
    int row, col;

    while (true) {
        std::cout << "Current Board:\n" << board.getBoardState();
        std::cout << getCurrentPlayer() << "'s turn. Enter move (row column): ";
        std::getline(std::cin, input);
        std::istringstream iss(input);

        if (!(iss >> row >> col)) {
            std::cout << "Invalid input. Please enter two integers separated by a space.\n";
            continue;
        }

        if (!makeMove(row, col)) {
            std::cout << "Invalid move. Try again.\n";
            continue;
        }

        if (checkWinCondition()) {
            std::cout << getCurrentPlayer() << " wins!\n";
            break;
        }

        if (isBoardFull()) {
            std::cout << "It's a draw!\n";
            break;
        }

        players.switchTurns();
    }
}

bool GameEngine::makeMove(int row, int col) {
    return board.makeMove(row, col, players.getCurrentPlayerMark());
}

bool GameEngine::checkWinCondition() {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if (board.getBoardState()[i * 4] == board.getBoardState()[i * 4 + 2] &&
            board.getBoardState()[i * 4] == board.getBoardState()[i * 4 + 4] &&
            board.getBoardState()[i * 4] != ' ') {
            return true;
        }
        if (board.getBoardState()[i] == board.getBoardState()[i + 3] &&
            board.getBoardState()[i] == board.getBoardState()[i + 6] &&
            board.getBoardState()[i] != ' ') {
            return true;
        }
    }

    // Check diagonals
    if (board.getBoardState()[0] == board.getBoardState()[4] &&
        board.getBoardState()[0] == board.getBoardState()[8] &&
        board.getBoardState()[0] != ' ') {
        return true;
    }
    if (board.getBoardState()[2] == board.getBoardState()[4] &&
        board.getBoardState()[2] == board.getBoardState()[6] &&
        board.getBoardState()[2] != ' ') {
        return true;
    }

    return false;
}

bool GameEngine::isBoardFull() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board.getBoardState()[i * 4 + j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

std::string GameEngine::getCurrentPlayer() {
    return players.getCurrentPlayerName();
}
