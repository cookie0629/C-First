#include "libcompressor/libcompressor.hpp"
#include <zlib.h>
#include <bzlib.h>
#include <cstring>

libcompressor_Buffer libcompressor_compress(libcompressor_CompressionAlgorithm algo, libcompressor_Buffer input) {
    if (input.data == nullptr || input.size == 0) {
        return {nullptr, 0};
    }

    libcompressor_Buffer output;
    output.size = input.size + 1024;
    output.data = static_cast<char*>(std::malloc(output.size));
    if (output.data == nullptr) {
        return {nullptr, 0};
    }

    int result = 0;
    if (algo == libcompressor_Zlib) {
        uLongf compressedSize = output.size;
        result = compress2(reinterpret_cast<Bytef*>(output.data), &compressedSize,
                          reinterpret_cast<const Bytef*>(input.data), input.size,
                          Z_DEFAULT_COMPRESSION);
        if (result == Z_OK) {
            output.size = compressedSize;
        } else {
            std::free(output.data);
            return {nullptr, 0};
        }
    } else if (algo == libcompressor_Bzip) {
        unsigned int compressedSize = output.size;
        result = BZ2_bzBuffToBuffCompress(output.data, &compressedSize,
                                          input.data, input.size,
                                          1, 0, 0);
        if (result == BZ_OK) {
            output.size = compressedSize;
        } else {
            std::free(output.data);
            return {nullptr, 0};
        }
    } else {
        std::free(output.data);
        return {nullptr, 0};
    }

    return output;
}