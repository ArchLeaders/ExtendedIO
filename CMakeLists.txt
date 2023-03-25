cmake_minimum_required(VERSION 3.10)
project(ExtendedIO VERSION 3.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_STATIC_LIBRARY_PREFIX "")

add_library(ExtendedIO STATIC
    ./src/include/exio/util/align.h
    ./src/include/exio/util/bit_utils.h
    ./src/include/exio/util/magic_utils.h
    ./src/include/exio/binary_reader.h
    ./src/include/exio/binary_writer.h
    ./src/include/exio/error.h
    ./src/include/exio/swap.h
    ./src/include/exio/types.h
)

set_target_properties(ExtendedIO PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(ExtendedIO PUBLIC ./src/include/)
target_compile_options(ExtendedIO PRIVATE -Wall -Wextra -fno-plt)
target_include_directories(ExtendedIO SYSTEM PUBLIC ./lib/nonstd)

set(BUILD_TESTING ON)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)