#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include "BoardService.hpp"
#include "PlayerService.hpp"

class GameEngine {
public:
    GameEngine();
    void startGame();

private:
    BoardService board;
    PlayerService players;
    bool makeMove(int row, int col);
    bool checkWinCondition();
    bool isBoardFull();
    std::string getCurrentPlayer();
};

#endif // GAMEENGINE_HPP
