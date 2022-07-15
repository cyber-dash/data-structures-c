cmake_minimum_required(VERSION 3.13)

project(main)

include_directories("./*")

add_executable(main
        src/common.h
        src/test.h
        src/binary_tree.h
        src/huffman_tree.h
        
        src/stack.h
        src/test.c
        src/binary_tree.c
        src/huffman_tree.c
        
        src/stack.c
        src/main.c
        src/queue.c src/queue.h)
