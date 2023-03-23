cmake_minimum_required(VERSION 3.10)
project(binaryio VERSION 3.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_STATIC_LIBRARY_PREFIX "")

add_library(binaryio STATIC
    ./src/include/binaryio/util/align.h
    ./src/include/binaryio/util/bit_utils.h
    ./src/include/binaryio/util/swap.h
    ./src/include/binaryio/types.h
    ./src/include/binaryio/binary_reader.h
    ./src/include/binaryio/binary_writer.h
)

set_target_properties(binaryio PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(binaryio PUBLIC ./src/include/)
target_compile_options(binaryio PRIVATE -Wall -Wextra -fno-plt)
target_include_directories(binaryio SYSTEM PUBLIC ./lib/nonstd)

set(BUILD_TESTING ON)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)