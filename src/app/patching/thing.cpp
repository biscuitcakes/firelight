//
// Created by alexs on 11/25/2023.
//

#include "pm_star_rod_mod_patch.hpp"
#include "yay_0_codec.hpp"
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <vector>

struct Record {
  uint32_t offset;
  std::vector<uint8_t> data;
};

int main() {
  std::filesystem::path t = "/Users/alexs/git/firelight/src/app/patching"
                            "/PMMQ_Jr._1.5.1.2_fixed.mod";

  auto size = file_size(t);

  auto data = new char[size];

  std::ifstream file(t, std::ios::binary);

  file.read(data, size);

  FL::Patching::Yay0Codec codec;

  auto result = codec.decompress(reinterpret_cast<uint8_t *>(data));

  FL::Patching::PMStarRodModPatch patch(result);

  std::filesystem::path gamePath =
      "/Users/alexs/git/firelight/_data/_games/PaperMario.z64";
  std::ifstream game(gamePath);

  auto gameSize = file_size(gamePath);
  std::vector<uint8_t> gameData(gameSize);

  game.read(reinterpret_cast<char *>(gameData.data()), gameSize);

  auto patchedGame = patch.patchRom(gameData);

  std::ofstream output("moddedpm.z64", std::ios::binary);
  output.write(reinterpret_cast<const char *>(patchedGame.data()),
               patchedGame.size());
}
