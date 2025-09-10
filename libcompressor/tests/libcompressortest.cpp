#include <gtest/gtest.h>

#include <cstring>

#include "libcompressor/libcompressor.hpp"

TEST(CompressorTest, NonEmptyInput) {
  const char* test_data = "test_string";
  libcompressor_Buffer input;
  input.data = const_cast<char*>(test_data);
  input.size = std::strlen(test_data);

  libcompressor_Buffer output = libcompressor_compress(libcompressor_Zlib, input);
  EXPECT_NE(output.data, nullptr);
  EXPECT_GT(output.size, 0);
  std::free(output.data);

  output = libcompressor_compress(libcompressor_Bzip, input);
  EXPECT_NE(output.data, nullptr);
  EXPECT_GT(output.size, 0);
  std::free(output.data);
}

TEST(CompressorTest, EmptyInput) {
  libcompressor_Buffer input;
  input.data = nullptr;
  input.size = 0;

  libcompressor_Buffer output = libcompressor_compress(libcompressor_Zlib, input);
  EXPECT_EQ(output.data, nullptr);
  EXPECT_EQ(output.size, 0);

  output = libcompressor_compress(libcompressor_Bzip, input);
  EXPECT_EQ(output.data, nullptr);
  EXPECT_EQ(output.size, 0);
}

TEST(CompressorTest, ZlibSpecificOutput) {
  const char* test_data = "test_string";
  libcompressor_Buffer input;
  input.data = const_cast<char*>(test_data);
  input.size = std::strlen(test_data);

  libcompressor_Buffer output = libcompressor_compress(libcompressor_Zlib, input);
  ASSERT_NE(output.data, nullptr);
  ASSERT_EQ(output.size, 19);

  unsigned char expected[] = {0x78, 0x9c, 0x2b, 0x49, 0x2d, 0x2e, 0x89, 0x2f, 0x2e, 0x29,
                              0xca, 0xcc, 0x4b, 0x07, 0x00, 0x1c, 0x79, 0x04, 0xb7};
  for (int i = 0; i < output.size; i++) {
    EXPECT_EQ(static_cast<unsigned char>(output.data[i]), expected[i]);
  }
  std::free(output.data);
}

TEST(CompressorTest, BzipSpecificOutput) {
  const char* test_data = "test_string";
  libcompressor_Buffer input;
  input.data = const_cast<char*>(test_data);
  input.size = std::strlen(test_data);

  libcompressor_Buffer output = libcompressor_compress(libcompressor_Bzip, input);
  ASSERT_NE(output.data, nullptr);
  ASSERT_EQ(output.size, 49);

  unsigned char expected[] = {0x42, 0x5a, 0x68, 0x31, 0x31, 0x41, 0x59, 0x26, 0x53, 0x59, 0x4a, 0x7c,
                              0x69, 0x05, 0x00, 0x00, 0x04, 0x83, 0x80, 0x00, 0x00, 0x82, 0xa1, 0x1c,
                              0x00, 0x20, 0x00, 0x22, 0x03, 0x68, 0x84, 0x30, 0x22, 0x50, 0xdf, 0x04,
                              0x99, 0xe2, 0xee, 0x48, 0xa7, 0x0a, 0x12, 0x09, 0x4f, 0x8d, 0x20, 0xa0};
  for (int i = 0; i < output.size; i++) {
    EXPECT_EQ(static_cast<unsigned char>(output.data[i]), expected[i]);
  }
  std::free(output.data);
}
