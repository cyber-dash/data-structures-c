//
// Created by cyberdash@163.com on 2022/5/2.
//

#ifndef CYBER_DASH_HEAP_H
#define CYBER_DASH_HEAP_H

#include "graph.h"
#include "queue.h"


int LowerThan(min_span_node_t* node1, min_span_node_t* node2);


int LargerThan(min_span_node_t* node1, min_span_node_t* node2);


void MinHeapSiftDown(min_span_node_t* min_span_node_arr, int index, int heap_size);

void MinHeapSiftUp(min_span_node_t* min_span_node_arr, int index);


void MinHeapBuild(min_span_node_t *min_span_node_arr, int heap_size);


Status PriorityQueueInit(min_span_node_t* min_span_node_arr, int heap_size);

Status PriorityQueueEnqueue(min_span_node_t* min_span_node_arr, int* heap_size, linked_queue_node_t* min_span_node);

Status PriorityQueueDequeue(min_span_node_t* min_span_node_arr, int* heap_size, linked_queue_node_t* min_span_node);
// Status PriorityQueueDeQueue(linked_queue_node_t* queue, int* v);

#endif // CYBER_DASH_HEAP_H