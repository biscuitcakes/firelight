//
// Created by alexs on 10/17/2023.
//

#include "game.hpp"
#include <fstream>
#include <vector>

using std::vector;

using std::string;

namespace libretro {
static std::vector<char> ReadAllBytes(const string &filename) {
  std::ifstream ifs(filename, std::ios::binary | std::ios::ate);
  std::ifstream::pos_type pos = ifs.tellg();

  if (pos == 0) {
    return std::vector<char>{};
  }

  vector<char> result(pos);

  ifs.seekg(0, std::ios::beg);
  ifs.read(&result[0], pos);

  return result;
}

Game::Game(const string &filePath) {
  this->path = filePath;
  this->data = ReadAllBytes(filePath);
  if (this->data.empty()) {
    // TODO
  }
}

string Game::getPath() { return this->path; }

void *Game::getData() { return &this->data[0]; }

size_t Game::getSize() { return this->data.size(); }
} // namespace libretro