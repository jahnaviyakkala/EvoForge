#ifndef PLAYERSERVICE_HPP
#define PLAYERSERVICE_HPP

#include <vector>
#include <string>

class PlayerService {
public:
    PlayerService();
    void addPlayer(const std::string& name, char mark);
    void switchTurns();
    std::string getCurrentPlayerName() const;
    char getCurrentPlayerMark() const;

private:
    std::vector<std::pair<std::string, char>> players;
    int currentPlayerIndex = 0;
};

#endif // PLAYERSERVICE_HPP
