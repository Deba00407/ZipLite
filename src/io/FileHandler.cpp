#include "FileHandler.h"

#include <array>
#include <fstream>
#include <iterator>
#include <limits>
#include <stdexcept>

namespace filehandler {

constexpr std::array<uint8_t, 4> kMagic = {'Z', 'I', 'P', 'L'};
constexpr uint8_t kFormatVersion = 1;
constexpr std::size_t kHeaderSize = 4 + 1 + 1 + 8 + 8;

void write_u64(std::ostream& stream, const uint64_t value) {
    for (unsigned int shift = 0; shift < 64; shift += 8) {
        stream.put(static_cast<char>((value >> shift) & 0xff));
    }
}

uint64_t read_u64(std::istream& stream) {
    uint64_t value = 0;
    for (unsigned int shift = 0; shift < 64; shift += 8) {
        const int byte = stream.get();
        if (byte == std::char_traits<char>::eof()) {
            throw std::runtime_error("Truncated compression file header.");
        }
        value |= static_cast<uint64_t>(static_cast<uint8_t>(byte)) << shift;
    }
    return value;
}

} // namespace

ziplite::CompressionResult filehandler::FileHandler::read_file(const std::string& input_filePath) {
    std::ifstream file(input_filePath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + input_filePath);
    }

    std::array<uint8_t, 4> magic{};
    file.read(reinterpret_cast<char*>(magic.data()), static_cast<std::streamsize>(magic.size()));
    if (!file || magic != kMagic) {
        throw std::runtime_error("Invalid compression file header: " + input_filePath);
    }

    const int version = file.get();
    const int flags = file.get();
    if (version != kFormatVersion || (flags != 0 && flags != 1)) {
        throw std::runtime_error("Unsupported compression file format: " + input_filePath);
    }

    ziplite::CompressionResult result{};
    result.compression_used = flags == 1;
    result.original_size = read_u64(file);
    result.compressed_size = read_u64(file);

    if (result.compressed_size > std::numeric_limits<std::size_t>::max() ||
        result.compressed_size > static_cast<uint64_t>(std::numeric_limits<std::streamsize>::max())) {
        throw std::runtime_error("Payload is too large to read: " + input_filePath);
    }

    result.payload.resize(static_cast<std::size_t>(result.compressed_size));
    if (!result.payload.empty()) {
        file.read(reinterpret_cast<char*>(result.payload.data()),
                  static_cast<std::streamsize>(result.payload.size()));
    }
    if (!file || file.peek() != std::char_traits<char>::eof()) {
        throw std::runtime_error("Payload size does not match file metadata: " + input_filePath);
    }

    if (result.payload.size() != result.compressed_size ||
        (!result.compression_used && result.original_size != result.compressed_size)) {
        throw std::runtime_error("Inconsistent compression metadata: " + input_filePath);
    }
    return result;
}

std::vector<uint8_t> filehandler::FileHandler::read_bytes(const std::string &input_filePath) {
    std::ifstream file(input_filePath, std::ios::binary);

    if(!file.is_open()){
        throw std::runtime_error("Failed to open file: " + input_filePath);
    }

    std::vector<uint8_t> parsed_file(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );

    return parsed_file;
}

void filehandler::FileHandler::write_file(
    const std::string& output_filePath,
    const ziplite::CompressionResult& result
) {
    if (result.payload.size() != result.compressed_size ||
        (!result.compression_used && result.original_size != result.compressed_size)) {
        throw std::invalid_argument("CompressionResult has inconsistent metadata.");
    }

    std::ofstream file(output_filePath, std::ios::binary | std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to create requested file: " + output_filePath);
    }

    file.write(reinterpret_cast<const char*>(kMagic.data()), static_cast<std::streamsize>(kMagic.size()));
    file.put(static_cast<char>(kFormatVersion));
    file.put(static_cast<char>(result.compression_used ? 1 : 0));
    write_u64(file, result.original_size);
    write_u64(file, result.compressed_size);
    if (!result.payload.empty()) {
        file.write(reinterpret_cast<const char*>(result.payload.data()),
                   static_cast<std::streamsize>(result.payload.size()));
    }
    if (!file) {
        throw std::runtime_error("Failed to write compression file: " + output_filePath);
    }
} // namespace filehandler
