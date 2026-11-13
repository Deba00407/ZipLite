
include(FetchContent)

# Download GoogleTest
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
)

FetchContent_MakeAvailable(googletest)

# Create test executable
add_executable(ziplite_tests
        dependencies.h
        unit_test_compression.cpp
        unit_test_decompression.cpp
)

# Link the core library and GoogleTest
target_link_libraries(ziplite_tests
    PRIVATE
        ziplite_core
        GTest::gtest_main
)

# Automatically discover GoogleTest test cases
include(GoogleTest)
gtest_discover_tests(ziplite_tests)
