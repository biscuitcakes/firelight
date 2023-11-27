//
// Created by alexs on 11/18/2023.
//

#ifndef FIRELIGHT_GAME_LIBRARY_HPP
#define FIRELIGHT_GAME_LIBRARY_HPP

#include "entry.hpp"
#include <vector>

namespace FL::Library {

class GameLibrary {
public:
  void addGame(Entry &entry);
  Entry *getEntryByGameId(const std::string &gameId);
  std::vector<Entry> getAllGames();

private:
  std::vector<Entry> allGames;
};

} // namespace FL::Library

#endif // FIRELIGHT_GAME_LIBRARY_HPP
