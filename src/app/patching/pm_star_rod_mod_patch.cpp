//
// Created by alexs on 11/25/2023.
//

#include "pm_star_rod_mod_patch.hpp"
#include <cstring>
#include <fstream>

namespace FL::Patching {

PMStarRodModPatch::PMStarRodModPatch(const std::vector<uint8_t> &data) {
  auto cursor = data.data();
  uint32_t pmsr;
  memcpy(&pmsr, cursor, 4);
  cursor += 4;

  uint32_t numRecords =
      cursor[0] << 24 | cursor[1] << 16 | cursor[2] << 8 | cursor[3];
  cursor += 4;

  for (int i = 0; i < numRecords; ++i) {
    Record record{};
    record.offset =
        cursor[0] << 24 | cursor[1] << 16 | cursor[2] << 8 | cursor[3];
    cursor += 4;

    uint32_t dataLength =
        cursor[0] << 24 | cursor[1] << 16 | cursor[2] << 8 | cursor[3];
    cursor += 4;
    //    printf("offset: %d, len: %d\n", record.offset, dataLength);

    record.data.resize(dataLength);
    memcpy(record.data.data(), cursor, dataLength);
    cursor += dataLength;

    records.emplace_back(record);
  }
}

std::vector<uint8_t> PMStarRodModPatch::patchRom(std::vector<uint8_t> &data) {
  auto last = records[records.size() - 1];

  auto totalLen = last.offset + last.data.size();

  auto size = data.size();
  if (totalLen > data.size()) {
    size = totalLen;
  }

  std::vector<uint8_t> result(size);
  memcpy(result.data(), data.data(), data.size());

  auto begin = result.data();
  auto cursor = begin;
  for (auto r : records) {
    cursor = begin + r.offset;
    memcpy(cursor, r.data.data(), r.data.size());
  }

  return result;
}

} // namespace FL::Patching
