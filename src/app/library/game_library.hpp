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
  Entry *getEntryByGameId(const std::string &gameId);

private:
  std::vector<Entry> allGames;
};

} // namespace FL::Library

#endif // FIRELIGHT_GAME_LIBRARY_HPP
