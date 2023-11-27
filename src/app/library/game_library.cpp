//
// Created by alexs on 11/18/2023.
//

#include "game_library.hpp"

namespace FL::Library {
Entry *GameLibrary::getEntryByGameId(const std::string &gameId) {
  for (auto &g : allGames) {
    if (g.gameId == gameId) {
      return &g;
    }
  }

  return nullptr;
}
void GameLibrary::addGame(Entry &entry) { allGames.emplace_back(entry); }
std::vector<Entry> GameLibrary::getAllGames() { return allGames; }
} // namespace FL::Library
