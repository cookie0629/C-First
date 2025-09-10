#include <spdlog/spdlog.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "libcompressor/libcompressor.hpp"

int main(int argc, char* argv[]) {
  // ������־��¼��
  auto logger = spdlog::stderr_logger_mt("stderr");
  spdlog::set_level(spdlog::level::err);

  // ����������
  if (argc < 3) {
    logger->error("Usage: {} <zlib|bzip> <input_string>", argv[0]);
    return EXIT_FAILURE;
  }

  // ����ѹ���㷨
  libcompressor_CompressionAlgorithm algo;
  if (strcmp(argv[1], "zlib") == 0) {
    algo = libcompressor_Zlib;
  } else if (strcmp(argv[1], "bzip") == 0) {
    algo = libcompressor_Bzip;
  } else {
    logger->error("First argument must be 'zlib' or 'bzip'");
    return EXIT_FAILURE;
  }

  // ׼�����뻺����
  libcompressor_Buffer input;
  input.data = argv[2];
  input.size = strlen(argv[2]);

  // ѹ��
  libcompressor_Buffer output = libcompressor_compress(algo, input);
  if (output.data == nullptr || output.size == 0) {
    logger->error("Compression failed");
    return EXIT_FAILURE;
  }

  // ���ѹ������ֽ���
  for (int i = 0; i < output.size; i++) {
    printf("%02x", static_cast<unsigned char>(output.data[i]));
  }
  printf("\n");

  std::free(output.data);
  return EXIT_SUCCESS;
}
