#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

#include "algorithms_impl//RLECompressor.h"
#include "algorithms_impl/RLEDecompressor.h"
#include "core/CompressionEngine.h"
#include "core/DeCompressionEngine.h"
#include "io/FileHandler.h"

// Logic flow:
// read_file -> compress -> write_file
// read_file(compressed) -> decompress -> write_file
// verify both written files are same


signed main(const int argc, char** argv) {

    // User flags
    std::unordered_map<std::string, std::string> args;

    if (argc < 5) {
        std::cerr
            << "Insufficient arguments. Please specify "
            << "--in <input_file> and --out <output_file>\n";

        return 1;
    }

    for (int i = 1; i < argc; i++) {

        std::string flag = argv[i];

        if (flag != "--in" && flag != "--out") {
            std::cerr << "Unknown flag: " << flag << '\n';
            return 1;
        }

        if (i + 1 >= argc) {
            std::cerr << "Missing value for " << flag << '\n';
            return 1;
        }

        args[flag] = argv[++i];
    }

    if (!args.contains("--in") || !args.contains("--out")) {
        std::cerr << "Both --in and --out are required.\n";
        return 1;
    }

    std::string inputFile = args.at("--in");
    std::string outputFile = args.at("--out");

    std::cout << "Input: " << inputFile << '\n';
    std::cout << "Output: " << outputFile << '\n';


    // Compression workflow

    auto *compressor = new ziplite::RLECompressor();

    auto* compression_engine = new ziplite::CompressionEngine(*compressor);

    auto bytes = filehandler::FileHandler::read_bytes(inputFile);

    auto result = compression_engine->execute(bytes);

    filehandler::FileHandler::write_file(outputFile, result);

    
    // Decompression workflow

    auto *decompressor = new ziplite::RLEDecompressor();

    auto compressedFile = filehandler::FileHandler::read_file(outputFile);

    auto* decompression_engine = new ziplite::DeCompressionEngine(*decompressor);

    const std::vector<uint8_t> decompressedBytes = decompression_engine->execute(
        compressedFile.payload, compressedFile.compression_used
    );

    // Check for equality
    const bool check = (decompressedBytes == result.payload);
    std::cout << "\n\n Both files are equal: " << check << std::endl;
}