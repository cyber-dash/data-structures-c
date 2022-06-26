cmake_minimum_required(VERSION 3.13)

project(main)

include_directories("./*")

add_executable(main src/main.c src/seq_stack.c src/seq_stack.h src/test.c src/test.h)
