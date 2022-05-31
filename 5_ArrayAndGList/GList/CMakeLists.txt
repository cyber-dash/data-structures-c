cmake_minimum_required(VERSION 3.13)

project(main)

include_directories("./*")

add_executable(main src/main.c src/gList.c src/gList.h src/type.h src/sq_queue.h src/sq_queue.c src/test.c src/test.h)
