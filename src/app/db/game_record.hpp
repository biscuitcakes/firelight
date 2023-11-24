//
// Created by alexs on 11/14/2023.
//

#ifndef FIRELIGHT_GAME_RECORD_HPP
#define FIRELIGHT_GAME_RECORD_HPP

#include "nlohmann/json.hpp"
#include <string>

using std::string;
using namespace nlohmann;

namespace FL::DB {

struct GameRecord {
  string id;
  string name;
  string platform;
  string md5_checksum;
};

static void to_json(json &j, const GameRecord &record) {
  j = json{{"id", record.id},
           {"name", record.name},
           {"platform", record.platform},
           {"md5_checksum", record.md5_checksum}};
}

static void from_json(const json &j, GameRecord &record) {
  j.at("id").get_to(record.id);
  j.at("name").get_to(record.name);
  j.at("platform").get_to(record.platform);
  j.at("md5_checksum").get_to(record.md5_checksum);
}

} // namespace FL::DB

#endif // FIRELIGHT_GAME_RECORD_HPP
