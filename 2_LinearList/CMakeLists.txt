cmake_minimum_required(VERSION 3.21)

project(main)

include_directories("./*")

add_executable(main src/main.c src/SqList.h src/SqList.c src/test.c src/test.h)