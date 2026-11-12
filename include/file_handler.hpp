#pragma once

#include <cstdint>
#include <string>
#include <vector>
namespace filehandler {

    std::vector<uint8_t> read_file(const std::string& input_filepath);

    void write_file(const std::string& out_filepath, std::vector<uint8_t>& bytes);
};