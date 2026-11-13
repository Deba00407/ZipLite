#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

#include "dependencies.h"

TEST_F(ZipliteUnitTests, CompressRepeatedBytes) {
    const std::vector<uint8_t> input = {'A', 'A', 'A', 'B', 'B', 'C', 'C', 'C'};
    const std::vector<uint8_t> expected = {'A', 3, 'B', 2, 'C', 3};

    const auto result = compression_engine.execute(input);

    EXPECT_TRUE(result.compression_used);
    EXPECT_EQ(result.payload, expected);
    EXPECT_EQ(result.original_size, input.size());
    EXPECT_EQ(result.compressed_size, expected.size());
}

TEST_F(ZipliteUnitTests, EmptyInputRemainsEmpty) {
    const std::vector<uint8_t> input;

    const auto result = compression_engine.execute(input);

    EXPECT_FALSE(result.compression_used);
    EXPECT_TRUE(result.payload.empty());
    EXPECT_EQ(result.original_size, 0);
    EXPECT_EQ(result.compressed_size, 0);
}

TEST_F(ZipliteUnitTests, SplitsRunsLongerThan255) {
    const std::vector<uint8_t> input(300, 'A');
    const std::vector<uint8_t> expected = {'A', 255, 'A', 45};

    const auto result = compression_engine.execute(input);

    EXPECT_TRUE(result.compression_used);
    EXPECT_EQ(result.payload, expected);
}

TEST_F(ZipliteUnitTests, KeepsOriginalWhenCompressionExpandsData) {
    const std::vector<uint8_t> input = {'A', 'B', 'C'};

    const auto result = compression_engine.execute(input);

    EXPECT_FALSE(result.compression_used);
    EXPECT_EQ(result.payload, input);
    EXPECT_EQ(result.compressed_size, input.size());
}
