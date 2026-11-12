
#include <gtest/gtest.h>

#include "../include/utils.hpp"

#include <stdexcept>
#include <vector>
#include <cstdint>

TEST(CompressorTest, CompressRepeatedBytes) {

    std::vector<uint8_t> input = {
        'A', 'A', 'A',
        'B', 'B',
        'C', 'C', 'C'
    };

    std::vector<uint8_t> expected = {
        'A', 3,
        'B', 2,
        'C', 3
    };

    auto result = ziplite::compress(input);

    EXPECT_EQ(result, expected);
}

TEST(CompressorTest, CompressEmptyInput) {

    std::vector<uint8_t> input;

    EXPECT_EQ(input.size(), 0);
}

TEST(CompressorTest, HandleLongRuns) {

    std::vector<uint8_t> input(300, 'A');

    auto result = ziplite::compress(input);

    std::vector<uint8_t> expected = {
        'A', 255,
        'A', 45
    };

    EXPECT_EQ(result, expected);
}

TEST(CompressorTest, CompressionDecompressionRoundTrip) {

    std::vector<uint8_t> input = {
        'A', 'A', 'A',
        'B', 'B',
        'C', 'C', 'C',
        'D'
    };

    auto compressed = ziplite::compress(input);
    auto decompressed = ziplite::decompress(compressed);

    EXPECT_EQ(input, decompressed);
}
