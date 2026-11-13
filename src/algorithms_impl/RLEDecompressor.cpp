//
// Created by USER on 13-11-2026.
//

#include "RLEDecompressor.h"

namespace ziplite {
    std::vector<uint8_t> RLEDecompressor::decompress(const std::vector<uint8_t> &byte_stream) const {
        std::vector<uint8_t> decompressed_stream;
        decompressed_stream.reserve(1024);


        const size_t sz = byte_stream.size();

        for(size_t p = 0; p+2 <= sz; p += 2){
            uint8_t byte = byte_stream[p], cnt = byte_stream[p+1];
            while(cnt--){
                decompressed_stream.push_back(byte);
            }
        }

        return decompressed_stream;
    }
} // ziplite