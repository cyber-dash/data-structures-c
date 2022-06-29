cmake_minimum_required(VERSION 3.13)

project(main)

include_directories("./*")

add_executable(main
        src/type.h
        src/test.h
        src/binary_tree.h
        src/HuffmanTree.h
        
        src/stack.h
        src/test.c
        src/binary_tree.c
        src/HuffmanTree.c
        
        src/stack.c
        src/main.c
        )
