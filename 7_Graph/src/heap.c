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
void HeapAdjust(min_span_node_t* min_span_node_arr, int index, int heap_size)
{
    min_span_node_t node = min_span_node_arr[index];

    // 沿key较大的孩子结点向下筛选, 从1开始, 因此是乘以2
    for (int cur_child_idx = 2 * index; cur_child_idx <= heap_size; cur_child_idx *= 2) {
        if (cur_child_idx < heap_size &&
            LargerThan(min_span_node_arr + cur_child_idx, min_span_node_arr + cur_child_idx + 1))
        {
            cur_child_idx++; // 较小的值的下标
        }

        if (!LargerThan(&node, min_span_node_arr + cur_child_idx)) {
            break;
        }

        min_span_node_arr[index] = min_span_node_arr[cur_child_idx];
        index = cur_child_idx;
    }

    min_span_node_arr[index] = node;
}


/*!
 * 建堆
 * @param min_span_node_arr mst结点数组
 * @param heap_size
 */
void BuildHeap(min_span_node_t* min_span_node_arr, int heap_size) {

    for (int i = heap_size / 2; i > 0; i--) {
        HeapAdjust(min_span_node_arr, i, heap_size);
    }
}
