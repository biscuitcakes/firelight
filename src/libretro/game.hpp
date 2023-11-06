//
// Created by alexs on 10/17/2023.
//

#ifndef BLUEMBER_GAME_HPP
#define BLUEMBER_GAME_HPP

#include <cstddef>
#include <string>
#include <vector>

using std::string;

namespace libretro {

class Game {
public:
  explicit Game(const string &filePath);

  string getPath();

  void *getData();

  size_t getSize();

private:
  std::vector<char> data;
  string path;
};

} // namespace libretro

#endif // BLUEMBER_GAME_HPP
