//
// Created by alexs on 11/25/2023.
//

#ifndef FIRELIGHT_YAY_0_CODEC_HPP
#define FIRELIGHT_YAY_0_CODEC_HPP

#include <cstdint>
#include <vector>
namespace FL::Patching {

class Yay0Codec {
public:
  std::vector<uint8_t> decompress(uint8_t *compressed);

private:
  struct Header {
    uint32_t magic; // should just be ASCII 'Yay0'
    uint32_t uncompressedLength;
    uint32_t opsAddr;  // Address of beginning of opcodes
    uint32_t dataAddr; // Address of beginning of compressed data
  };
};

} // namespace FL::Patching

#endif // FIRELIGHT_YAY_0_CODEC_HPP
