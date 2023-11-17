//
// Created by alexs on 11/14/2023.
//

#ifndef FIRELIGHT_GAME_REPOSITORY_HPP
#define FIRELIGHT_GAME_REPOSITORY_HPP

#include "game_record.hpp"
#include <memory>
#include <string>

namespace FL::DB {

class GameRepository {
public:
  virtual std::shared_ptr<GameRecord>
  getGameByChecksum(std::string checksum) = 0;
};

} // namespace FL::DB

#endif // FIRELIGHT_GAME_REPOSITORY_HPP
