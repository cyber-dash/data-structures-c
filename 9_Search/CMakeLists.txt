cmake_minimum_required(VERSION 3.13)

project(main)

include_directories("./*")

add_executable(main src/main.c src/common.h src/static_search_table_t.c src/static_search_table_t.h src/test.c src/test.h)
