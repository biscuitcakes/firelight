//
// Created by alexs on 11/24/2023.
//

#ifndef FIRELIGHT_PAPER_MARIO_PATCH_THING_HPP
#define FIRELIGHT_PAPER_MARIO_PATCH_THING_HPP

#include <cstdint>
#include <cstdio>
namespace FL::Patching {

class PaperMarioPatchThing {
  typedef struct {
    uint32_t magic;
    uint32_t uncompressedLength;
    uint32_t opPtr;
    uint32_t dataPtr;
  } Yay0Header;

  // from:
  // https://github.com/pmret/papermario/blob/main/tools/splat/util/n64/Yay0decompress.c
  void decompress(Yay0Header *hdr, uint8_t *srcPtr, uint8_t *dstPtr,
                  bool isBigEndian) {
    uint8_t byte = 0, mask = 0;
    uint8_t *ctrl, *ops, *data;
    uint16_t copy, op;
    uint32_t written = 0;

    ctrl = srcPtr + sizeof(Yay0Header);
    ops = srcPtr + hdr->opPtr;
    data = srcPtr + hdr->dataPtr;

    while (written < hdr->uncompressedLength) {
      if ((mask >>= 1) == 0) {
        byte = *ctrl++;
        mask = 0x80;
      }

      if (byte & mask) {
        *dstPtr++ = *data++;
        written++;
      } else {
        op = isBigEndian ? (ops[0] << 8) | ops[1] : (ops[1] << 8) | ops[0];
        ops += 2;

        written += copy = (op >> 12) ? (2 + (op >> 12)) : (18 + *data++);

        while (copy--) {
          *dstPtr = dstPtr[-(op & 0xfff) - 1];
          dstPtr++;
        }
      }
    }
  }
};
} // namespace FL::Patching

#endif // FIRELIGHT_PAPER_MARIO_PATCH_THING_HPP