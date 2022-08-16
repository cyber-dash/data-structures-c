cmake_minimum_required(VERSION 3.21)

project(main)

include_directories("./*")

add_executable(main src/main.c src/seq_list.h src/seq_list.c src/test.c src/test.h src/common.h)