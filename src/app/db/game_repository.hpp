//
// Created by alexs on 11/14/2023.
//

#ifndef FIRELIGHT_GAME_REPOSITORY_HPP
#define FIRELIGHT_GAME_REPOSITORY_HPP

#include "game_record.hpp"
#include <memory>
#include <string>

namespace FL::DB {

using namespace std;

const string example =
    R"([{ "id": "123", "name": "Pokemon Red Version","md5_checksum":"testing"
 }])";

class GameRepository {
public:
  //  GameRepository();
  virtual shared_ptr<GameRecord> getGameByChecksum(string checksum) = 0;
};
// GameRepository::GameRepository() {
//   auto j = json::parse(example);
//   auto p2 = j.template get<std::vector<GameRecord>>();
//
//   json j2 = p2;
//
//   printf("cool man: %s\n", j2.dump().c_str());
// }

} // namespace FL::DB

#endif // FIRELIGHT_GAME_REPOSITORY_HPP
