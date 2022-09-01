cmake_minimum_required(VERSION 3.21)

project(main)

include_directories("./*")

add_executable(main src/main.c src/linked_list.c src/linked_list.h src/test.c src/test.h src/static_linked_list.c src/static_linked_list.h src/common.h)