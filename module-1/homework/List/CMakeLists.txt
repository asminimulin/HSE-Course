cmake_minimum_required(VERSION 3.16)

project("list")

option(ENABLE_SANITIZERS OFF)

add_executable(list tests.cpp list.h list.cpp)

if(ENABLE_SANITIZERS)
    message("Build with sanitizers")
    add_library(sanitizers INTERFACE)
    target_compile_options(sanitizers INTERFACE -fsanitize=address,undefined,leak -g -O0)
    target_link_options(sanitizers INTERFACE -fsanitize=address,undefined,leak)
    target_link_libraries(list PRIVATE sanitizers)
endif()

target_compile_options(list PRIVATE -Wall -Wextra)
target_compile_features(list PRIVATE cxx_std_20)
