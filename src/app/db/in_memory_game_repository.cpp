//
// Created by alexs on 11/15/2023.
//

#include "in_memory_game_repository.hpp"
#include <fstream>

namespace FL::DB {

InMemoryGameRepository::InMemoryGameRepository(const string &filename) {
  std::filesystem::path path(filename);
  ifstream file(path);

  auto size = file_size(path);
  char content[size];

  file.read(content, size);
  file.close();

  string contentString = content;
  auto j = json::parse(contentString);

  auto p2 = j.template get<std::vector<GameRecord>>();
  for (const auto &p : p2) {
    printf("name: %s\n", p.name.c_str());
  }
}

shared_ptr<GameRecord>
InMemoryGameRepository::getGameByChecksum(string checksum) {
  return shared_ptr<GameRecord>();
}

} // namespace FL::DB