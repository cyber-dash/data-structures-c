//
// Created by cyberdash@163.com on 2022/5/2.
//

#ifndef CYBER_DASH_HEAP_H
#define CYBER_DASH_HEAP_H

#include "graph.h"


int LowerThan(MinSpanNode* node1, MinSpanNode* node2);


int LargerThan(MinSpanNode* node1, MinSpanNode* node2);


// @brief 迭代建立小顶堆
// @param H 堆数据
// @param s 结点值
// @param m 堆最大长度
void HeapAdjust(MinSpanNodeArr minSpanNodeArr, int index, int heapSize);


void BuildHeap(MinSpanNodeArr minSpanNodeArr, int heapSize);


#endif // CYBER_DASH_HEAP_H