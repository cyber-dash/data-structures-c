//
// Created by cyberdash@163.com on 2022/5/2.
//

#include "heap.h"


typedef struct MSTMinHeap {
    MST_node_t* min_span_node_arr;
    int size;
    int capacity;
} MSTMinHeap;


int LowerThan(MST_node_t* node1, MST_node_t* node2) {
    if (node1->weight_type == DOUBLE && node2->weight_type == DOUBLE) {
        if (node1->weight.double_value < node2->weight.double_value) {
            return 1;
        } else {
            return 0;
        }
    }

    return -1;
}


int LargerThan(MST_node_t* node1, MST_node_t* node2) {
    if (node1->weight_type == DOUBLE && node2->weight_type == DOUBLE) {
        if (node1->weight.double_value > node2->weight.double_value) {
            return 1;
        } else {
            return 0;
        }
    }

    return -1;
}


void swap(MST_node_t* node1, MST_node_t* node2) {
    MST_node_t tmp = *node1;
    *node1 = *node2;
    *node2 = tmp;
}


// @brief 迭代建立小顶堆
// @param H 堆数据
// @param s 结点值
// @param m 堆最大长度
// 索引从1开始, 因此是乘以2
void MinHeapSiftDown(MST_node_t* min_span_node_arr, int index, int heap_size)
{
    for (int child_idx = 2 * index; child_idx <= heap_size; child_idx *= 2) {

        //! index的孩子结点中, 权重较小的结点索引, 赋给child_idx
        if (child_idx < heap_size && LargerThan(min_span_node_arr + child_idx, min_span_node_arr + child_idx + 1)) {
            child_idx++;
        }

        //! 如果父节点<=子节点, sift down结束
        if (!LargerThan(min_span_node_arr + index, min_span_node_arr + child_idx)) {
            break;
        }

        //! 交换父子结点
        swap(min_span_node_arr + index, min_span_node_arr + child_idx);
    }
}


void MinHeapSiftUp(MST_node_t* min_span_node_arr, int index) {
    for (int parent_idx = index / 2; parent_idx > 0; parent_idx /= 2) {
        if (!LargerThan(min_span_node_arr + parent_idx, min_span_node_arr + index)) {
            break;
        }

        swap(min_span_node_arr + parent_idx, min_span_node_arr + index);
    }
}


/*!
 * 建堆
 * @param min_span_node_arr mst结点数组
 * @param heap_size
 */
void MinHeapBuildBySiftDown(MST_node_t* min_span_node_arr, int heap_size) {

    for (int i = heap_size / 2; i > 0; i--) {
        MinHeapSiftDown(min_span_node_arr, i, heap_size);
    }
}


/*!
 * 最小优先队列初始化
 * @param min_priority_queue 最小优先队列
 * @param size 队列size
 * @return 执行结果
 */
Status MinPriorityQueueInit(MST_node_t* min_priority_queue, int size) {
    MinHeapBuildBySiftDown(min_priority_queue, size);

    return OK;  // todo: 其他错误返回值的边界条件, 如果有兴趣的话自行补充:-)
}


Status MinPriorityQueueEnqueue(MST_node_t* min_priority_queue, linked_queue_node_t min_span_node) {

}


Status MinPriorityQueueDequeue(MST_node_t* min_priority_queue, linked_queue_node_t* min_span_node) {

}

