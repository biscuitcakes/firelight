//
// Created by alexs on 11/14/2023.
//

#ifndef FIRELIGHT_GAME_SCANNER_HPP
#define FIRELIGHT_GAME_SCANNER_HPP

#include "openssl/md5.h"
#include <filesystem>
#include <fstream>
#include <openssl/evp.h>
#include <string>

namespace FL::DB {

const int MAX_FILESIZE_BYTES = 15000000;

std::string calculateMD5(const char *input, int size) {
  // Create a buffer to hold the hash
  unsigned char md5Hash[EVP_MAX_MD_SIZE];
  unsigned int md5HashLength;

  std::string output;

  // Create a message digest context
  auto mdctx = EVP_MD_CTX_new();

  // Initialize the message digest context
  if (mdctx == nullptr || !EVP_DigestInit_ex2(mdctx, EVP_md5(), nullptr)) {
    EVP_MD_CTX_free(mdctx);
    throw std::runtime_error("Failed to initialize hash context");
  }

  // Add data to the message digest context
  if (!EVP_DigestUpdate(mdctx, input, size)) {
    EVP_MD_CTX_free(mdctx);
    throw std::runtime_error("Failed to update hash context");
  }

  // Finalize the hash computation
  if (!EVP_DigestFinal_ex(mdctx, md5Hash, &md5HashLength)) {
    EVP_MD_CTX_free(mdctx);
    throw std::runtime_error("Failed to finalize hash context");
  }

  // Clean up the message digest context
  EVP_MD_CTX_free(mdctx);

  output.resize(md5HashLength * 2);
  for (unsigned int i = 0; i < md5HashLength; ++i)
    std::sprintf(&output[i * 2], "%02x", md5Hash[i]);

  return output;

  //  Convert the hash to a hexadecimal string std::ostringstream oss;
  //  for (unsigned int i = 0; i < md5HashLength; ++i) {
  //    oss << std::hex << std::setw(2) << std::setfill('0')
  //        << static_cast<int>(md5Hash[i]);
  //  }
  //
  //  return oss.str();
}

// std::string calculateOTHERMD5(const std::string &input) {
//
//   unsigned char md5Hash[MD5_DIGEST_LENGTH];
//   MD5(input, input.size(), )
// }

class GameScanner {
public:
  GameScanner();
};

GameScanner::GameScanner() {
  std::string path = "../../ember-app";
  printf("====================================\n");
  for (const auto &entry :
       std::filesystem::recursive_directory_iterator(path)) {
    if (!entry.is_directory()) {
      auto size = entry.file_size();

      if (size < MAX_FILESIZE_BYTES) {
        std::vector<char> thing(size);
        std::ifstream file(entry.path(), std::ios::binary);

        file.read(thing.data(), size);
        file.close();

        printf("path: %ls, md5: %s\n", entry.path().c_str(),
               calculateMD5(thing.data(), size).c_str());
      }
    }
  }
  printf("====================================\n");
}

} // namespace FL::DB

#endif // FIRELIGHT_GAME_SCANNER_HPP
