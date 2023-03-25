add_executable(ExtendedIOTest ./src/main.cpp)

target_link_libraries(ExtendedIOTest PUBLIC ExtendedIO)

add_test(
    NAME ExtendedIOTest
    COMMAND ExtendedIOTest ./test_file.wav
)