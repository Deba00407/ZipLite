//
// Created by USER on 13-11-2026.
//

#ifndef ZIPLITE_RLECOMPRESSOR_H
#define ZIPLITE_RLECOMPRESSOR_H

#include "interfaces/ICompressor.h"

namespace ziplite {
    class RLECompressor : public ICompressor{
        public:
            [[nodiscard]] std::vector<uint8_t> compress(
            const std::vector<uint8_t>& byte_stream
        ) const override;
    };
} // ziplite

#endif //ZIPLITE_RLECOMPRESSOR_H
