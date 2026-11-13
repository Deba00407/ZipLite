//
// Created by USER on 13-11-2026.
//

#ifndef ZIPLITE_IDECOMPRESSOR_H
#define ZIPLITE_IDECOMPRESSOR_H
#include <cstdint>
#include <vector>

class IDecompressor {
public:
    virtual ~IDecompressor() = default;

    [[nodiscard]] virtual std::vector<uint8_t> decompress(
        const std::vector<uint8_t> &byte_stream
    ) const = 0; // concrete class will implement
};

#endif //ZIPLITE_IDECOMPRESSOR_H
