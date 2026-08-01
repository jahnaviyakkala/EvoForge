#include "BoardService.hpp"
#include <iostream>

BoardService::BoardService() : size(3) {
    initializeBoard(size);
}

void BoardService::initializeBoard(int size) {
    board.resize(size, std::vector<char>(size, ' '));
}

bool BoardService::makeMove(int row, int col, char mark) {
    if (row < 0 || row >= size || col < 0 || col >= size) {
        return false;
    }
    if (isOccupied(row, col)) {
        return false;
    }
    board[row][col] = mark;
    return true;
}

bool BoardService::isOccupied(int row, int col) const {
    return board[row][col] != ' ';
}

std::string BoardService::getBoardState() const {
    std::string state;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            state += board[i][j];
            if (j < size - 1) {
                state += " | ";
            }
        }
        state += "\n";
        if (i < size - 1) {
            state += "---------\n";
        }
    }
    return state;
}
