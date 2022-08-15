cmake_minimum_required(VERSION 3.17)

project(ShaderShaker CXX)

enable_testing()

add_subdirectory(src)
add_subdirectory(test/src)

option(ENABLE_CLANG_TIDY "Use clang tidy" ON)

if(ENABLE_CLANG_TIDY)
    find_program(CMAKE_CXX_CLANG_TIDY NAMES clang-tidy)
    if(CMAKE_CXX_CLANG_TIDY)
        set(TESTS_ARGUMENT "-checks=modernize-*")
        set(TESTS_ARGUMENT "${TESTS_ARGUMENT},-modernize-use-trailing-return-type")
        list(APPEND CMAKE_CXX_CLANG_TIDY "${TESTS_ARGUMENT}")
        set(CMAKE_C_CLANG_TIDY ${CMAKE_CXX_CLANG_TIDY})
    endif()
endif()
