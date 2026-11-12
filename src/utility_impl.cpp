#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

#include "../include/utils.hpp"

// Implemeting a simple RLE compression
// count consecutive appearences of characters and replace them with embedded form

void file_check(const std::vector<uint8_t> &input_stream) {

    std::cout << "\nPassed input stream size: " << input_stream.size() << " bytes" << std::endl;
    
    if(input_stream.empty()){
        std::cerr << "\nFile received was empty.";
    }
}

namespace ziplite {
    const std::vector<uint8_t> compress(const std::vector<uint8_t>& input){

        // file_check(input);
        
        std::vector<uint8_t> compressed_stream;
        compressed_stream.reserve(1024);

        size_t p = 0, sz = input.size();

        while(p < sz){
            int cnt = 1;
            uint8_t curr_byte = input[p];

            // At a time allow at max 255 occurences of the same byte, if more add more instances
            while(p+cnt < sz && input[p+cnt] == curr_byte && cnt < 255){
                cnt++;
            }

            compressed_stream.push_back(curr_byte);
            compressed_stream.push_back(cnt);

            p += cnt; // move to the next unique byte
        }

        return compressed_stream;
    };

    const std::vector<uint8_t> decompress(const std::vector<uint8_t>& input){

        // file_check(input);
        
        std::vector<uint8_t> decompressed_stream;
        decompressed_stream.reserve(1024);

        size_t p = 0, sz = input.size();

        for(; p+2 <= sz; p += 2){
            uint8_t byte = input[p], cnt = input[p+1];
            while(cnt--){
                decompressed_stream.push_back(byte);
            }
        }

        return decompressed_stream;
    };
}