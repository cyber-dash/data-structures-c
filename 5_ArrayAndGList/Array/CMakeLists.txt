cmake_minimum_required(VERSION 3.13)

project(main)

include_directories("./*")

add_executable(main src/main.c src/array.c src/array.h "src/sparseMatrix.c" "src/sparseMatrix.h" "src/common.h" src/test.c src/test.h)
