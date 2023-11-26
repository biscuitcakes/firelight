//
// Created by alexs on 11/25/2023.
//

#ifndef FIRELIGHT_PM_STAR_ROD_MOD_PATCHER_HPP
#define FIRELIGHT_PM_STAR_ROD_MOD_PATCHER_HPP

#include <cstdint>
#include <vector>
namespace FL::Patching {

class PMStarRodModPatcher {
private:
  struct Record {
    uint32_t offset;
    std::vector<uint8_t> data;
  };
};

} // namespace FL::Patching

#endif // FIRELIGHT_PM_STAR_ROD_MOD_PATCHER_HPP
