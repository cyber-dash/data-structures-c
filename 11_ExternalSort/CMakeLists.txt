cmake_minimum_required(VERSION 3.13)

project(main)

include_directories("./*")

add_executable(main src/main.c src/test.h src/test.c src/loser_tree.c src/loser_tree.h)
