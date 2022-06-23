//
// Created by cyberdash@163.com on 2022/5/2.
//

#ifndef CYBER_DASH_HEAP_H
#define CYBER_DASH_HEAP_H

#include "graph.h"
#include "queue.h"


typedef struct MinPriorityQueue {
    path_t* mst_item_array;
    int size;
    int capacity;
} MinPriorityQueue;


int LowerThan(edge_t* item1, edge_t* item2);


int LargerThan(edge_t* item1, edge_t* item2);


void MinHeapSiftDown(edge_t* item_arr, int index, int heap_size);


void MinHeapSiftUp(edge_t* item_arr, int index);


void MinHeapBuildBySiftDown(edge_t *item_arr, int heap_size);


Status MinPriorityQueueInit(MinPriorityQueue* min_priority_queue, int capacity);


Status MinPriorityQueuePush(MinPriorityQueue* min_priority_queue, edge_t item);


Status MinPriorityQueuePop(MinPriorityQueue* min_priority_queue, edge_t* item);




#endif // CYBER_DASH_HEAP_H