cmake_minimum_required(VERSION 3.13)

project(main)

include_directories("./*")

add_executable(main
        src/tree.h
        src/test.h
        src/BinaryTree.h
        src/HuffmanTree.h
        
        src/stack.h
        src/test.c
        src/BinaryTree.c
        src/HuffmanTree.c
        
        src/stack.c
        src/main.c
        )
