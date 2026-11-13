#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

#include "dependencies.h"

TEST_F(ZipliteUnitTests, ExpandsRunLengthPairs) {
    const std::vector<uint8_t> encoded = {'A', 3, 'B', 2, 'C', 1};
    const std::vector<uint8_t> expected = {'A', 'A', 'A', 'B', 'B', 'C'};

    EXPECT_EQ(decompression_engine.execute(encoded), expected);
}

TEST_F(ZipliteUnitTests, HandlesEmptyInput) {
    const std::vector<uint8_t> encoded;

    EXPECT_TRUE(decompression_engine.execute(encoded).empty());
}

TEST_F(ZipliteUnitTests, ExpandsMaximumRunCount) {
    const std::vector<uint8_t> encoded = {'Z', 255};
    const auto decoded = decompression_engine.execute(encoded);

    ASSERT_EQ(decoded.size(), 255);
    EXPECT_EQ(decoded, std::vector<uint8_t>(255, 'Z'));
}

TEST_F(ZipliteUnitTests, ReturnsPayloadUnchangedWhenCompressionWasSkipped) {
    const std::vector<uint8_t> original = {'A', 'B', 'C'};

    EXPECT_EQ(decompression_engine.execute(original, false), original);
}

TEST_F(ZipliteUnitTests, RoundTripsDataThroughRleEngines) {
    const std::vector<uint8_t> original = {'A', 'A', 'A', 'B', 'B', 'C', 'D', 'D', 'D'};
    const ziplite::RLECompressor compressor;
    const ziplite::CompressionEngine compression_engine{compressor};
    const auto compressed = compression_engine.execute(original);

    const auto decoded = decompression_engine.execute(
        compressed.payload,
        compressed.compression_used
    );

    EXPECT_EQ(decoded, original);
}
