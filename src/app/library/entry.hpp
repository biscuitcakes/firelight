//
// Created by alexs on 11/14/2023.
//

#ifndef FIRELIGHT_ENTRY_HPP
#define FIRELIGHT_ENTRY_HPP

#include <filesystem>
#include <string>
namespace FL::Library {

enum EntryType { NORMAL_GAME, ROMHACK };

struct Entry {
  std::string id;
  EntryType type;
  std::string gameName;
  std::string gameId;       // todo: change name?
  std::string sourceGameId; // todo
  std::string corePath;
  std::filesystem::path romPath; // todo: change name
};

} // namespace FL::Library

#endif // FIRELIGHT_ENTRY_HPP
