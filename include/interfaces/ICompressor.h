//
// Created by USER on 13-11-2026.
//

#ifndef ZIPLITE_ICOMPRESSOR_H
#define ZIPLITE_ICOMPRESSOR_H

#include <cstdint>
#include <vector>

namespace ziplite {
    class ICompressor {
    public:
        virtual ~ICompressor() = default;

        [[nodiscard]] virtual std::vector<uint8_t> compress(
            const std::vector<uint8_t> &byte_stream
        ) const = 0; // concrete class will implement
    };
} // ziplite

#endif //ZIPLITE_ICOMPRESSOR_H
