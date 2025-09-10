#include <spdlog/spdlog.h>

#include <cstring>
#include <iostream>

#include "libcompressor/libcompressor.hpp"

int main(int argc, char* argv[]) {
  if (argc < 3) {
    spdlog::error("Usage: compressor <zlib|bzip> <input_string>");
    return EXIT_FAILURE;
  }

  libcompressor_CompressionAlgorithm algo;
  if (std::strcmp(argv[1], "zlib") == 0) {
    algo = libcompressor_Zlib;
  } else if (std::strcmp(argv[1], "bzip") == 0) {
    algo = libcompressor_Bzip;
  } else {
    spdlog::error("First argument must be 'zlib' or 'bzip'");
    return EXIT_FAILURE;
  }

  const char* input_str = argv[2];
  libcompressor_Buffer input;
  input.data = const_cast<char*>(input_str);
  input.size = std::strlen(input_str);

  libcompressor_Buffer output = libcompressor_compress(algo, input);
  if (output.data == nullptr || output.size == 0) {
    spdlog::error("Compression failed");
    return EXIT_FAILURE;
  }

  for (int i = 0; i < output.size; i++) {
    printf("%02x", static_cast<unsigned char>(output.data[i]));
  }
  printf("\n");

  std::free(output.data);
  return EXIT_SUCCESS;
}
