cmake_minimum_required(VERSION 3.13)

project(main)

include_directories("./*")

add_executable(main src/main.c src/search.h src/static_search_table.c src/static_search_table.h src/test.c src/test.h)
