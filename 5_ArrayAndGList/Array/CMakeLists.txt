cmake_minimum_required(VERSION 3.13)

project(main)

include_directories("./*")

add_executable(main src/main.c src/multi_dimensional_array.c src/multi_dimensional_array.h "src/sparse_matrix.c" "src/sparse_matrix.h" "src/common.h" src/test.c src/test.h)
