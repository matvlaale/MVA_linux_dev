cmake_minimum_required(VERSION 3.10)
project(LibTesting)

set(CMAKE_C_STANDARD 99)

option(CODE_COVERAGE "Enable coverage check" ON)
if(CODE_COVERAGE)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(-g -O0 --coverage)
        add_link_options(--coverage)
    endif()
endif()

add_library(buf src/tests.c)

enable_testing()
add_executable(test_buf tests/tests.c)
target_link_libraries(test_buf PRIVATE buf)
add_test(NAME BufTest COMMAND test_buf)
