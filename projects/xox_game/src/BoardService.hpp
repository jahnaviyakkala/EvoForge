#ifndef BOARDSERVICE_HPP
#define BOARDSERVICE_HPP

#include <vector>
#include <string>

class BoardService {
public:
    BoardService();
    void initializeBoard(int size);
    bool makeMove(int row, int col, char mark);
    bool isOccupied(int row, int col) const;
    std::string getBoardState() const;

private:
    std::vector<std::vector<char>> board;
    int size;
};

#endif // BOARDSERVICE_HPP
