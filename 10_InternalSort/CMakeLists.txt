cmake_minimum_required(VERSION 3.13)

project(main)

include_directories("./*")

add_executable(main src/main.c src/sort.h src/sort.c src/test.c src/test.h)
