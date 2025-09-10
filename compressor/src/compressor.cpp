#include <spdlog/spdlog.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "libcompressor/libcompressor.hpp"

int main(int argc, char* argv[]) {
  // 设置日志记录器
  auto logger = spdlog::stderr_logger_mt("stderr");
  spdlog::set_level(spdlog::level::err);

  // 检查参数数量
  if (argc < 3) {
    logger->error("Usage: {} <zlib|bzip> <input_string>", argv[0]);
    return EXIT_FAILURE;
  }

  // 解析压缩算法
  libcompressor_CompressionAlgorithm algo;
  if (strcmp(argv[1], "zlib") == 0) {
    algo = libcompressor_Zlib;
  } else if (strcmp(argv[1], "bzip") == 0) {
    algo = libcompressor_Bzip;
  } else {
    logger->error("First argument must be 'zlib' or 'bzip'");
    return EXIT_FAILURE;
  }

  // 准备输入缓冲区
  libcompressor_Buffer input;
  input.data = argv[2];
  input.size = strlen(argv[2]);

  // 压缩
  libcompressor_Buffer output = libcompressor_compress(algo, input);
  if (output.data == nullptr || output.size == 0) {
    logger->error("Compression failed");
    return EXIT_FAILURE;
  }

  // 输出压缩后的字节流
  for (int i = 0; i < output.size; i++) {
    printf("%02x", static_cast<unsigned char>(output.data[i]));
  }
  printf("\n");

  std::free(output.data);
  return EXIT_SUCCESS;
}
