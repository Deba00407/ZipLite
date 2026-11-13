#ifndef ZIPLITE_DECOMPRESSIONENGINE_H
#define ZIPLITE_DECOMPRESSIONENGINE_H

#include <cstdint>
#include <vector>

#include "interfaces/IDecompressor.h"

namespace ziplite {

class DeCompressionEngine {
    const ::IDecompressor& decompressor;

public:
    explicit DeCompressionEngine(const ::IDecompressor& decompressor);

    // Pass compression_used from the corresponding CompressionResult. When
    // compression was skipped, the payload is already the original data.
    [[nodiscard]] std::vector<uint8_t> execute(
        const std::vector<uint8_t>& byte_stream,
        bool compression_used = true
    ) const;
};

} // namespace ziplite

#endif // ZIPLITE_DECOMPRESSIONENGINE_H
