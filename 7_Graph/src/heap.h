//
// Created by cyberdash@163.com on 2022/5/2.
//

#ifndef CYBER_DASH_HEAP_H
#define CYBER_DASH_HEAP_H

#include "graph.h"


int LowerThan(min_span_node_t* node1, min_span_node_t* node2);


int LargerThan(min_span_node_t* node1, min_span_node_t* node2);


// @brief 迭代建立小顶堆
// @param H 堆数据
// @param s 结点值
// @param m 堆最大长度
void HeapAdjust(min_span_node_arr_t min_span_node_arr, int index, int heap_size);


void BuildHeap(min_span_node_arr_t min_span_node_arr, int heap_size);


#endif // CYBER_DASH_HEAP_H