//
// Created by alexs on 11/14/2023.
//

#ifndef FIRELIGHT_ENTRY_HPP
#define FIRELIGHT_ENTRY_HPP

#include <filesystem>
#include <string>
namespace FL::Library {

struct Entry {
  std::string id;
  std::string gameName;
  std::string gameId;
  std::string corePath;
  std::filesystem::path romPath;
};

} // namespace FL::Library

#endif // FIRELIGHT_ENTRY_HPP
