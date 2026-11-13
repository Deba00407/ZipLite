//
// Created by USER on 13-11-2026.
//

#ifndef ZIPLITE_COMPRESSION_ENGINE_H
#define ZIPLITE_COMPRESSION_ENGINE_H
#include <cstdint>
#include <vector>

#include "interfaces/ICompressor.h"

namespace ziplite {

    // file metadata
    struct CompressionResult {
        std::vector<uint8_t> payload;
        bool compression_used;
        uint64_t original_size;
        uint64_t compressed_size;
    };

    class CompressionEngine {
        const ICompressor& compressor;
    public:

        explicit CompressionEngine(const ICompressor& compressor);

        [[nodiscard]] CompressionResult execute(
            const std::vector<uint8_t> &byte_stream
        ) const;
    };

} // ziplite

#endif //ZIPLITE_COMPRESSION_ENGINE_H
