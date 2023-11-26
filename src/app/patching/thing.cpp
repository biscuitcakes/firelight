//
// Created by alexs on 11/25/2023.
//

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
  unsigned int num = 1;
  char *byte = (char *)&num;

  if (*byte == 1) {
    printf("Little-endian\n");
  } else {
    printf("Big-endian\n");
  }

  std::filesystem::path t = "/Users/alexs/git/firelight/src/app/patching"
                            "/PMMQ_Jr._1.5.1.2_fixed.mod";

  auto size = file_size(t);

  auto data = new char[size];

  std::ifstream file(t, std::ios::binary);

  file.read(data, size);

  FL::Patching::Yay0Codec codec;

  auto result = codec.decompress(reinterpret_cast<uint8_t *>(data));

  auto cursor = result.data();
  uint32_t pmsr;
  memcpy(&pmsr, cursor, 4);
  cursor += 4;

  uint32_t numRecords =
      cursor[0] << 24 | cursor[1] << 16 | cursor[2] << 8 | cursor[3];
  cursor += 4;

  std::ofstream output("cooler.guy", std::ios::binary);
  output.write(reinterpret_cast<const char *>(result.data()), result.size());

  printf("pmsr: %c\n", pmsr);
  printf("numRecords: %u\n", numRecords);

  for (int i = 0; i < numRecords; ++i) {
    uint32_t offset =
        cursor[0] << 24 | cursor[1] << 16 | cursor[2] << 8 | cursor[3];
    cursor += 4;
    uint32_t dataLength =
        cursor[0] << 24 | cursor[1] << 16 | cursor[2] << 8 | cursor[3];

    cursor += 4;
    cursor += dataLength;
    //    printf("[%d] offset: %u, dataLen: %u\n", i, offset, dataLength);
  }
}
