//
// Created by alexs on 11/15/2023.
//

#include "in_memory_game_repository.hpp"
#include <fstream>

namespace FL::DB {

InMemoryGameRepository::InMemoryGameRepository(const string &filename) {
  std::filesystem::path path(filename);
  std::ifstream file(path);

  auto size = file_size(path);
  char content[size];

  file.read(content, size);
  file.close();

  string contentString = content;
  auto j = json::parse(contentString);

  auto p2 = j.template get<std::vector<GameRecord>>();
  for (const auto &p : p2) {
    games.emplace(p.md5_checksum, p);
    //    printf("name: %s\n", p.name.c_str());
  }
}

std::shared_ptr<GameRecord>
InMemoryGameRepository::getGameByChecksum(string checksum) {
  auto result = games.find(checksum);
  if (result != nullptr) {
    return std::make_shared<GameRecord>(result->second);
  }

  return nullptr;
}

} // namespace FL::DB