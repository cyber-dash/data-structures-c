//
// Created by cyberdash@163.com on 2022/5/2.
//

#include "heap.h"
#include "stdlib.h"


/*!
 * 小于(<)
 * @param item1 元素1
 * @param item2 元素2
 * @return 比较结果
 */
int LowerThan(edge_t* item1, edge_t* item2) {
    if (item1->weight_type == DOUBLE && item2->weight_type == DOUBLE) {
        if (item1->weight.double_value < item2->weight.double_value) {
            return 1;
        } else {
            return 0;
        }
    }

    return -1;
}


/*!
 * 大于(>)
 * @param item1 元素1
 * @param item2 元素2
 * @return 比较结果
 */
int LargerThan(edge_t* item1, edge_t* item2) {
    if (item1->weight_type == DOUBLE && item2->weight_type == DOUBLE) {
        if (item1->weight.double_value > item2->weight.double_value) {
            return 1;
        } else {
            return 0;
        }
    }

    return -1;
}


/*!
 * 交换元素值
 * @param item1 元素1(指针)
 * @param item2 元素2(指针)
 */
void Swap(edge_t* item1, edge_t* item2) {
    edge_t tmp = *item1;
    *item1 = *item2;
    *item2 = tmp;
}


/*!
 * 小顶堆SiftDown
 * @brief 迭代建立小顶堆
 * @param item_array 堆元素数组
 * @param index 执行SiftDown的索引
 * @param heap_size 堆size
 */
void MinHeapSiftDown(edge_t* item_array, int index, int heap_size)
{
    for (int child_index = 2 * index; child_index <= heap_size; child_index *= 2) {

        // index的孩子结点中, 权重较小的结点索引, 赋给child_idx
        if (child_index < heap_size && LargerThan(item_array + child_index, item_array + child_index + 1)) {
            child_index++;
        }

        // 如果父节点<=子节点, sift down结束
        if (!LargerThan(item_array + index, item_array + child_index)) {
            break;
        }

        //! 交换父子结点
        Swap(item_array + index, item_array + child_index);
    }
}


/*!
 * 小顶堆SiftUp
 * @param item_array 堆元素数组
 * @param index 执行SiftUp的索引
 */
void MinHeapSiftUp(edge_t* item_array, int index) {
    for (int parent_idx = index / 2; parent_idx > 0; parent_idx /= 2) {
        if (!LargerThan(item_array + parent_idx, item_array + index)) {
            break;
        }

        Swap(item_array + parent_idx, item_array + index);
    }
}


/*!
 * 建堆(使用SiftDown)
 * @param item_array 堆元素数组
 * @param heap_size 堆size
 */
void MinHeapBuildBySiftDown(edge_t* item_array, int heap_size) {
    for (int i = heap_size / 2; i > 0; i--) {
        MinHeapSiftDown(item_array, i, heap_size);
    }
}


/*!
 * 最小优先队列初始化
 * @param min_priority_queue 最小优先队列
 * @param capacity 队列容量
 * @return 执行结果
 */
Status MinPriorityQueueInit(MinPriorityQueue* min_priority_queue, int capacity) {
    if (capacity < 0 || capacity > MAX_VERTEX_CNT * MAX_VERTEX_CNT) {
        return ERROR;
    }
    min_priority_queue->mst_item_array = (edge_t*)malloc(sizeof(edge_t) * (capacity + 1));
    min_priority_queue->capacity = capacity;
    min_priority_queue->size = 0;

    return OK;
}


/*!
 * 最小优先队列入队
 * @param min_priority_queue 最小优先队列(指针)
 * @param item 入队元素
 * @return 执行结果
 */
Status MinPriorityQueuePush(MinPriorityQueue* min_priority_queue, edge_t item) {
    if (min_priority_queue->size == min_priority_queue->capacity) {
        return ERROR;
    }

    min_priority_queue->mst_item_array[min_priority_queue->size + 1] = item;
    min_priority_queue->size++;

    MinHeapSiftUp(min_priority_queue->mst_item_array, min_priority_queue->size);

    return OK;
}


/*!
 * 最小优先队列队头出队
 * @param min_priority_queue 最小优先队列(指针)
 * @param item 保存出队元素的元素(指针)
 * @return 执行结果
 */
Status MinPriorityQueuePop(MinPriorityQueue* min_priority_queue, edge_t* item) {
    if (min_priority_queue->size == 0) {
        return ERROR;
    }

    *item = min_priority_queue->mst_item_array[1];

    min_priority_queue->mst_item_array[1] = min_priority_queue->mst_item_array[min_priority_queue->size];
    min_priority_queue->size--;

    MinHeapSiftDown(min_priority_queue->mst_item_array, 1, min_priority_queue->size);

    return OK;
}

