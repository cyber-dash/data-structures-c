cmake_minimum_required(VERSION 3.13)

project(main)

include_directories("./*")

add_executable(main src/cyberdash_string.c src/cyberdash_string.h src/main.c src/test.c src/test.h)