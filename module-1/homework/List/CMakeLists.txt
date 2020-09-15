cmake_minimum_required(VERSION 3.16)

project("list")

add_executable(list tests.cpp list.h list.cpp)

target_compile_options(list PRIVATE -Wall -Wextra)
target_compile_features(list PRIVATE cxx_std_20)
