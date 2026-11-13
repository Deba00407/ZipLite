cmake_minimum_required(VERSION 3.20)

project(ziplite
  VERSION 1.0.0
  DESCRIPTION "A simple C++ file compression utility"
  LANGUAGES CXX
)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# core library
add_library(ziplite_core STATIC
        src/core/CompressionEngine.cpp
        src/core/CompressionEngine.h
        include/interfaces/ICompressor.h
        src/io/FileHandler.cpp
        src/io/FileHandler.h
        src/algorithms_impl/RLECompressor.cpp
        src/algorithms_impl/RLECompressor.h
        src/algorithms_impl/RLEDecompressor.cpp
        src/algorithms_impl/RLEDecompressor.h
        src/core/DeCompressionEngine.cpp
        src/core/DeCompressionEngine.h
)

# public headers
target_include_directories(ziplite_core
        PUBLIC
            ${PROJECT_SOURCE_DIR}/include
            ${PROJECT_SOURCE_DIR}/src
)

# executable
add_executable(ziplite
  src/main.cpp
        include/interfaces/IDecompressor.h
)

target_link_libraries(ziplite
  PRIVATE  ziplite_core
)

# Testing
include(CTest)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

