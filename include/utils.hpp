#pragma once

#include <cstdint>
#include <vector>

namespace ziplite {
    const std::vector<uint8_t> compress(
        const std::vector<uint8_t>& input
    );

    const std::vector<uint8_t> decompress(
        const std::vector<uint8_t>& input
    );
};