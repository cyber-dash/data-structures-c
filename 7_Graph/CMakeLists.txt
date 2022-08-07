cmake_minimum_required(VERSION 3.13)

project(main)

include_directories("./*")

add_executable(main src/main.c src/matrix_graph.h src/matrix_graph.c src/test.c src/test.h src/adjacency_list_graph.h
    src/graph.h src/algorithm.c src/algorithm.h src/queue.c src/queue.h src/min_priority_queue.c
        src/min_priority_queue.h src/disjoint_set.c src/disjoint_set.h src/common.h)
