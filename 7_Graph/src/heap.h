//
// Created by cyberdash@163.com on 2022/5/2.
//

#ifndef CYBER_DASH_HEAP_H
#define CYBER_DASH_HEAP_H

#include "graph.h"
#include "queue.h"


int LowerThan(MST_node_t* node1, MST_node_t* node2);


int LargerThan(MST_node_t* node1, MST_node_t* node2);


void MinHeapSiftDown(MST_node_t* min_span_node_arr, int index, int heap_size);


void MinHeapSiftUp(MST_node_t* min_span_node_arr, int index);


void MinHeapBuildBySiftDown(MST_node_t *min_span_node_arr, int heap_size);


Status MinPriorityQueueInit(MST_node_t* min_priority_queue, int size);


Status MinPriorityQueueEnqueue(MST_node_t* min_priority_queue, linked_queue_node_t min_span_node);


Status MinPriorityQueueDequeue(MST_node_t* min_priority_queue, linked_queue_node_t* min_span_node);


#endif // CYBER_DASH_HEAP_H