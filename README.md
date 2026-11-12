# ZipLite

A lightweight, lossless file compression utility written in **C++20**, implementing incremental compression algorithms, starting out with RLE.

ZipLite is a learning-oriented project focused on understanding lossless compression algorithms, binary file handling, modern C++ development, CMake, and unit testing.

## Features

- Lossless compression using Run-Length Encoding (RLE).
- Binary file handling using C++ file streams.
- Supports arbitrary byte sequences, not just text files.
- Handles consecutive runs of up to 255 identical bytes.
- Splits longer runs into multiple encoded sequences.
- Compression and decompression support.
- Unit testing with GoogleTest.
- CMake-based build system.

## How RLE Works

Run-Length Encoding is a simple lossless compression technique that replaces consecutive occurrences of the same byte with a pair containing the byte and its repetition count.

For example:

**Original data:**

```text
AAAAABBBCC
```

**RLE encoded representation:**

```text
A 5 B 3 C 2
```

ZipLite uses the following binary representation:

```text
[BYTE][COUNT][BYTE][COUNT]...
```

Each encoded pair occupies two bytes:

- `BYTE`: The repeated byte.
- `COUNT`: Number of consecutive occurrences, between 1 and 255.

For runs exceeding 255 bytes, multiple pairs are generated.

For example, 300 consecutive occurrences of `A` become:

```text
[A][255][A][45]
```

## Project Structure

```text
ziplite/
│
├── build/
│
├── include/
│   └── utils.hpp
│
├── src/
│   ├── main.cpp
│   ├── utility_impl.cpp
│   └── file_handler_impl.cpp
│
├── tests/
│   ├── CMakeLists.txt
│   └── unit_test_compression.cpp
│
├── CMakeLists.txt
├── input.txt
└── README.md
```

## Tech Stack

| Technology | Purpose |
|---|---|
| C++20 | Core implementation |
| CMake | Build system |
| GoogleTest | Unit testing |
| STL | Vectors and file handling |

## Getting Started

### Prerequisites

- C++20 compatible compiler (MSVC, GCC, or Clang).
- CMake 3.20 or later.
- Git (for fetching GoogleTest through CMake FetchContent).
- Internet connection during the initial GoogleTest dependency download.

### Build Instructions

Clone the repository:

```bash
git clone <repository-url>
cd ziplite
```

Configure the project:

```bash
cmake -S . -B build
```

Build the application:

```bash
cmake --build build --config Debug
```

For a Release build:

```bash
cmake --build build --config Release
```

### Running ZipLite

On Windows with the Visual Studio CMake generator:

```powershell
./build/Debug/ziplite.exe --in "input.txt" --out "compressed.txt"
```

Replace the input and output paths with your desired file locations.

### Running Unit Tests

Execute the test suite using CTest:

```bash
ctest --test-dir build -C Debug --output-on-failure
```

## Compression Characteristics

RLE is particularly effective when input data contains long sequences of identical consecutive bytes.

| Input characteristics | Expected effectiveness |
|---|---|
| Long repeated byte sequences | High |
| Repetitive text | High |
| Ordinary English text | Usually low |
| Random binary data | Usually low |
| Already compressed files | Usually low |

RLE is not guaranteed to reduce file size. When consecutive repetitions are uncommon, the encoded representation can be larger than the original input.

## Testing

The project uses GoogleTest to validate the compression and decompression logic.

The test suite covers:

- Compression of repeated bytes.
- Handling empty input.
- Handling long runs exceeding 255 bytes.
- Compression-decompression round-trip correctness.

The round-trip property is particularly important for lossless compression:

```text
decompress(compress(original_data)) == original_data
```

## Future Improvements

Potential extensions to ZipLite include:

- [ ] Adaptive compression to avoid expansion when RLE is ineffective.
- [ ] A custom binary file format with headers and metadata.
- [ ] Huffman Coding.
- [ ] LZ77 compression.
- [ ] Compression ratio and execution-time statistics.
- [ ] Improved malformed-input validation.
- [ ] Benchmarking against existing compression utilities.
- [ ] Support for additional compression strategies.

## Learning Objectives

This project explores several important systems programming concepts:

1. Binary file I/O and byte-level data manipulation.
2. Lossless data compression.
3. C++ standard library containers and algorithms.
4. Modular project organization using headers and implementation files.
5. CMake targets, libraries, and dependency management.
6. Automated unit testing with GoogleTest.
