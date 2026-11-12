#include <cstdint>
#include <fstream>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "../include/file_handler.hpp"

namespace filehandler {
    std::vector<uint8_t> read_file(const std::string &input_filepath){
    
        std::ifstream file(input_filepath, std::ios::binary);

        if(!file.is_open()){
            throw std::runtime_error("Failed to open file: " + input_filepath);
        }

        std::vector<uint8_t> parsed_file(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>()
        );

        return parsed_file;
    };

    void write_file(const std::string &out_filepath, std::vector<uint8_t> &bytes){

        std::ofstream file(out_filepath, std::ios::binary | std::ios::out);

        if(!file.is_open()){
            throw std::runtime_error("Failed to create requested file: " + out_filepath);
        }

        file.write(
            (reinterpret_cast<const char*>(bytes.data())), 
            static_cast<std::streamsize>(bytes.size())
        );

        if(!file){
            throw std::runtime_error("Failed to write file.");
        }
    };
};