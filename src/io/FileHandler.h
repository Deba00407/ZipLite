//
// Created by USER on 13-11-2026.
//

#ifndef ZIPLITE_FILEHANDLER_H
#define ZIPLITE_FILEHANDLER_H

#include <string>

#include "core/CompressionEngine.h"

namespace filehandler {

    class FileHandler {
    public:
        static ziplite::CompressionResult read_file(const std::string& input_filePath);

        static std::vector<uint8_t> read_bytes(const std::string& input_filePath);

        static void write_file(
            const std::string& output_filePath,
            const ziplite::CompressionResult& result
        );
    };

} // filehandler

#endif //ZIPLITE_FILEHANDLER_H
