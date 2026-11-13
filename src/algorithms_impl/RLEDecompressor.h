//
// Created by USER on 13-11-2026.
//

#ifndef ZIPLITE_RLEDECOMPRESSOR_H
#define ZIPLITE_RLEDECOMPRESSOR_H
#include <cstdint>
#include <vector>

#include "interfaces/IDecompressor.h"

namespace ziplite {
    class RLEDecompressor : public IDecompressor{
        public:
            [[nodiscard]] std::vector<uint8_t> decompress(
            const std::vector<uint8_t>& byte_stream
        ) const override;
    };
} // ziplite

#endif //ZIPLITE_RLEDECOMPRESSOR_H
