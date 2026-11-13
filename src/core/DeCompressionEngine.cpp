#include "DeCompressionEngine.h"

namespace ziplite {
    DeCompressionEngine::DeCompressionEngine(const ::IDecompressor &decompressor)
        : decompressor(decompressor) {
    }

    std::vector<uint8_t> DeCompressionEngine::execute(
        const std::vector<uint8_t> &byte_stream,
        const bool compression_used
    ) const {
        if (!compression_used) {
            return byte_stream;
        }

        return decompressor.decompress(byte_stream);
    }
} // namespace ziplite
