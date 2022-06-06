//
// Created by cyberdash@163.com on 2022/5/2.
//

#include "heap.h"

int LowerThan(min_span_node_t* node1, min_span_node_t* node2) {
    if (node1->weight_type == DOUBLE && node2->weight_type == DOUBLE) {
        if (node1->weight.double_value < node2->weight.double_value) {
            return 1;
        } else {
            return 0;
        }
    } else if (node1->weight_type == INT && node2->weight_type == INT) {
        if (node1->weight.int_value < node2->weight.int_value) {
            return 1;
        } else {
            return 0;
        }
    }

    return -1;
}


int LargerThan(min_span_node_t* node1, min_span_node_t* node2) {
    if (node1->weight_type == DOUBLE && node2->weight_type == DOUBLE) {
        if (node1->weight.double_value > node2->weight.double_value) {
            return 1;
        } else {
            return 0;
        }
    } else if (node1->weight_type == INT && node2->weight_type == INT) {
        if (node1->weight.int_value > node2->weight.int_value) {
            return 1;
        } else {
            return 0;
        }
    }

    return -1;
}


// @brief 迭代建立小顶堆
// @param H 堆数据
// @param s 结点值
// @param m 堆最大长度
void HeapAdjust(min_span_node_arr_t minSpanNodeArr, int index, int heapSize)
{
    min_span_node_t node = minSpanNodeArr[index];

    for (int curChildIdx = 2 * index; curChildIdx <= heapSize; curChildIdx *= 2)
        // 沿key较大的孩子结点向下筛选, 从1开始, 因此是乘以2
    {
        if (curChildIdx < heapSize &&
            LargerThan(minSpanNodeArr + curChildIdx, minSpanNodeArr + curChildIdx + 1))
        {
            curChildIdx++; // 较小的值的下标
        }

        if (!LargerThan(&node, minSpanNodeArr + curChildIdx)) {
            break;
        }

        minSpanNodeArr[index] = minSpanNodeArr[curChildIdx];
        index = curChildIdx;
    }

    minSpanNodeArr[index] = node;
} // HeapAdjust


void BuildHeap(min_span_node_arr_t minSpanNodeArr, int heapSize) {

    for (int i = heapSize / 2; i > 0; i--) {
        HeapAdjust(minSpanNodeArr, i, heapSize);
    }
}
