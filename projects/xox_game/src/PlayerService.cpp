#include "PlayerService.hpp"

PlayerService::PlayerService() {}

void PlayerService::addPlayer(const std::string& name, char mark) {
    players.emplace_back(name, mark);
}

void PlayerService::switchTurns() {
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

std::string PlayerService::getCurrentPlayerName() const {
    return players[currentPlayerIndex].first;
}

char PlayerService::getCurrentPlayerMark() const {
    return players[currentPlayerIndex].second;
}
