#ifndef LIBCOMPRESSOR_HPP
#define LIBCOMPRESSOR_HPP

#include <cstdlib>

/**
 * @file libcompressor.hpp
 * @brief Header for the compression library.
 */

/**
 * @enum libcompressor_CompressionAlgorithm
 * @brief Compression algorithm types.
 */
enum libcompressor_CompressionAlgorithm {
    libcompressor_Zlib,  ///< Zlib compression
    libcompressor_Bzip   ///< Bzip2 compression
};

/**
 * @struct libcompressor_Buffer
 * @brief Buffer structure for input and output data.
 */
struct libcompressor_Buffer {
    char* data; ///< Pointer to the data
    int size;   ///< Size of the data in bytes
};

/**
 * @brief Compresses input buffer using specified algorithm.
 * @param algo Compression algorithm to use.
 * @param input Input buffer.
 * @return Output buffer. If error occurs, data is NULL and size is 0.
 */
libcompressor_Buffer libcompressor_compress(libcompressor_CompressionAlgorithm algo, libcompressor_Buffer input);

#endif // LIBCOMPRESSOR_HPP