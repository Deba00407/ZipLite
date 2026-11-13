//
// Created by USER on 13-11-2026.
//

#ifndef ZIPLITE_RESOURCES_H
#define ZIPLITE_RESOURCES_H

#include <gtest/gtest.h>

#include "../src/algorithms_impl/RLECompressor.h"
#include "../src/algorithms_impl/RLEDecompressor.h"
#include "../src/core/CompressionEngine.h"
#include "../src/core/DeCompressionEngine.h"

class ZipliteUnitTests : public ::testing::Test {
protected:
    ziplite::RLECompressor compressor;

    ziplite::RLEDecompressor decompressor;

    ziplite::CompressionEngine compression_engine{compressor};

    ziplite::DeCompressionEngine decompression_engine{decompressor};
};

#endif
