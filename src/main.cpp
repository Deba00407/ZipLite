#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

#include "utility_impl.cpp"
#include "file_handler_impl.cpp"

// Logic flow:
// read_file -> compress -> write_file
// read_file(compressed) -> decompress -> write_file
// verify both written files are same

signed main(int argc, char** argv) {

    if (argc < 5) {
        std::cerr
            << "Insufficient arguments. Please specify "
            << "--in <input_file> and --out <output_file>\n";

        return 1;
    }

    std::unordered_map<std::string, std::string> args;

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

    if (!args.count("--in") || !args.count("--out")) {
        std::cerr << "Both --in and --out are required.\n";
        return 1;
    }

    std::string inputFile = args.at("--in");
    std::string outputFile = args.at("--out");

    std::cout << "Input: " << inputFile << '\n';
    std::cout << "Output: " << outputFile << '\n';

    // Compression workflow
    std::vector<uint8_t> bytes = filehandler::read_file(inputFile);
    std::vector<uint8_t> compressedBytes = ziplite::compress(bytes);

    // Print the compressed bytes
    filehandler::write_file(outputFile, compressedBytes);

    
    // Decompression workflow
    std::vector<uint8_t> decompressedBytes = ziplite::decompress(compressedBytes);

    // Print decompressed bytes
    // filehandler::write_file(outputFile, decompressedBytes);

    // Check for equality
    bool result = (decompressedBytes == bytes) ? true : false;
    std::cout << "\n\n Both files are equal: " << result << std::endl;
}