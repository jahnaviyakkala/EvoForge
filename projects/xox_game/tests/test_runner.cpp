#include <iostream>
#include <cassert>
#include "GameEngine.hpp"
#include "BoardService.hpp"
#include "PlayerService.hpp"

void test_board_initialization() {
    BoardService board;
    board.initializeBoard(3);
    std::string expected = " |  | \n---------\n |  | \n---------\n |  | \n";
    assert(board.getBoardState() == expected);
}

void test_make_move() {
    BoardService board;
    board.initializeBoard(3);
    assert(board.makeMove(0, 0, 'X'));
    std::string expected = "X |  | \n---------\n |  | \n---------\n |  | \n";
    assert(board.getBoardState() == expected);

    // Test out of bounds move
    assert(!board.makeMove(3, 3, 'O'));

    // Test occupied cell
    assert(!board.makeMove(0, 0, 'O'));
}

void test_check_win_condition() {
    BoardService board;
    board.initializeBoard(3);
    board.makeMove(0, 0, 'X');
    board.makeMove(0, 1, 'X');
    board.makeMove(0, 2, 'X');
    assert(board.checkWinCondition());

    // Reset board
    board.initializeBoard(3);
    board.makeMove(0, 0, 'O');
    board.makeMove(1, 0, 'O');
    board.makeMove(2, 0, 'O');
    assert(board.checkWinCondition());

    // Reset board
    board.initializeBoard(3);
    board.makeMove(0, 0, 'X');
    board.makeMove(1, 1, 'X');
    board.makeMove(2, 2, 'X');
    assert(board.checkWinCondition());

    // Reset board
    board.initializeBoard(3);
    board.makeMove(0, 2, 'O');
    board.makeMove(1, 1, 'O');
    board.makeMove(2, 0, 'O');
    assert(board.checkWinCondition());
}

void test_is_board_full() {
    BoardService board;
    board.initializeBoard(3);
    board.makeMove(0, 0, 'X');
    board.makeMove(0, 1, 'O');
    board.makeMove(0, 2, 'X');
    board.makeMove(1, 0, 'O');
    board.makeMove(1, 1, 'X');
    board.makeMove(1, 2, 'O');
    board.makeMove(2, 0, 'X');
    board.makeMove(2, 1, 'O');
    board.makeMove(2, 2, 'X');
    assert(board.isBoardFull());
}

void test_player_service() {
    PlayerService players;
    players.addPlayer("Player 1", 'X');
    players.addPlayer("Player 2", 'O');

    assert(players.getCurrentPlayerName() == "Player 1");
    assert(players.getCurrentPlayerMark() == 'X');

    players.switchTurns();
    assert(players.getCurrentPlayerName() == "Player 2");
    assert(players.getCurrentPlayerMark() == 'O');
}

int main() {
    test_board_initialization();
    test_make_move();
    test_check_win_condition();
    test_is_board_full();
    test_player_service();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
