cmake_minimum_required(VERSION 3.13)

project(main)

include_directories("./*")

add_executable(main src/main.c src/gen_list.c src/gen_list.h src/common.h src/circular_queue.h src/circular_queue.c src/test.c src/test.h)
