//
// Created by USER on 13-11-2026.
//

#include "RLECompressor.h"

namespace ziplite {
    std::vector<uint8_t> RLECompressor::compress(const std::vector<uint8_t> &byte_stream) const {
        std::vector<uint8_t> compressed_stream;

        compressed_stream.reserve(1024);

        size_t p = 0, sz = byte_stream.size();

        while (p < sz) {
            int cnt = 1;
            uint8_t curr_byte = byte_stream[p];

            // At a time allow at max 255 occurrences of the same byte, if more add more instances
            while (p + cnt < sz && byte_stream[p + cnt] == curr_byte && cnt < 255) {
                cnt++;
            }

            compressed_stream.push_back(curr_byte);
            compressed_stream.push_back(cnt);

            p += cnt; // move to the next unique byte
        }

        return compressed_stream;
    }
} // ziplite
