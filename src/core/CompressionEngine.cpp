//
// Created by USER on 13-11-2026.
//

#include "CompressionEngine.h"

namespace ziplite {

    // constructor DI
    CompressionEngine::CompressionEngine(const ICompressor &compressor) : compressor(compressor) {}

    CompressionResult CompressionEngine::execute(const std::vector<uint8_t> &byte_stream) const {
        CompressionResult result;

        result.original_size = byte_stream.size();
        result.compression_used = true;

        auto compressed_stream = compressor.compress(byte_stream);

        // Adaptive compression
        if (compressed_stream.size() < byte_stream.size()) {
            result.payload = compressed_stream;
        }else{
            result.payload = byte_stream; // keep original payload
            result.compression_used = false;
        }

        result.compressed_size = result.payload.size();

        return result;
    }
} // ziplite
