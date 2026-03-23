cmake_minimum_required(VERSION 3.16)

project(demo-project
    VERSION 1.0
    LANGUAGES C CXX
)

# C / C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##
### Fetch GoogleTest (updated version)
##
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# Recommended on Windows; harmless elsewhere
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

# --- Fix: relax maybe-uninitialized ONLY for GoogleTest (not your code) ---
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # GTest::gtest / GTest::gtest_main are ALIAS targets, so we modify
    # the underlying real targets gtest and gtest_main instead.
    if (TARGET gtest)
        target_compile_options(gtest PRIVATE -Wno-error=maybe-uninitialized)
    endif()
    if (TARGET gtest_main)
        target_compile_options(gtest_main PRIVATE -Wno-error=maybe-uninitialized)
    endif()
endif()

##
### Project Sources
##
include_directories("${PROJECT_SOURCE_DIR}/include")

# All C sources
file(GLOB sources "${PROJECT_SOURCE_DIR}/src/*.c")

# Main executable for the project (not strictly needed for tests, but harmless)
add_executable(${PROJECT_NAME} ${sources})

##
### Tests
##
# Remove main.c so tests don’t get a duplicate main()
list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/src/main.c")

# All unit test .cpp files
file(GLOB tests "${PROJECT_SOURCE_DIR}/test/unit/*.cpp")

# Single combined test binary, as your Makefile expects: build/test/unit/all_tests
add_executable(all_tests ${sources} ${tests})

target_link_libraries(all_tests
    PRIVATE
        gtest_main
)

# Register tests with CTest (optional but nice)
gtest_discover_tests(all_tests)
