cmake_minimum_required(VERSION 3.21)

project(main)

include_directories("./*")

add_executable(main src/main.c src/link_queue.c src/link_queue.h src/circular_queue.c src/circular_queue.h src/common.h src/bank_simulation.c src/bank_simulation.h src/test.c src/test.h src/test.c src/test.h)

