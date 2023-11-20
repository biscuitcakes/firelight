//
// Created by alexs on 11/18/2023.
//

#ifndef FIRELIGHT_SAVE_MANAGER_HPP
#define FIRELIGHT_SAVE_MANAGER_HPP

#include "../db/game_repository.hpp"
#include <string>
#include <vector>
namespace FL {

class SaveManager {
public:
  std::vector<unsigned char> getLatestForGame(std::string gameId);

private:
  DB::GameRepository *gameRepository;
};

} // namespace FL

#endif // FIRELIGHT_SAVE_MANAGER_HPP
