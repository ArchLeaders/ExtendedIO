add_executable(binaryio_test ./src/main.cpp)

target_link_libraries(binaryio_test PUBLIC binaryio)

add_test(
    NAME binaryio_test
    COMMAND binaryio_test ./test_file.wav
)