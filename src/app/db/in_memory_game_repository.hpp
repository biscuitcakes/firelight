//
// Created by alexs on 11/15/2023.
//

#ifndef FIRELIGHT_IN_MEMORY_GAME_REPOSITORY_HPP
#define FIRELIGHT_IN_MEMORY_GAME_REPOSITORY_HPP

#include "game_repository.hpp"
namespace FL::DB {

class InMemoryGameRepository : public GameRepository {
public:
  explicit InMemoryGameRepository(const std::string &filename);
  std::shared_ptr<GameRecord> getGameByChecksum(std::string checksum) override;

private:
  std::unordered_map<std::string, GameRecord> games;
};

} // namespace FL::DB

#endif // FIRELIGHT_IN_MEMORY_GAME_REPOSITORY_HPP
