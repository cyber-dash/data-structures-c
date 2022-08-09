/*!
 * @file min_priority_queue.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 最小优先队列源文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "min_priority_queue.h"
#include "stdlib.h"


/*!
 * <h1>小于(<)</h1>
 * @param item1 **元素1**
 * @param item2 **元素2***
 * @return **比较结果**
 * @note
 */
int LessThan(edge_t* item1, edge_t* item2) {
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
 * <h1>大于(>)</h1>
 * @param item1 **元素1**
 * @param item2 元素2
 * @return **比较结果**
 * @note
 */
int GreaterThan(edge_t* item1, edge_t* item2) {
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
 * <h1>交换元素值</h1>
 * @param item1 **元素1**(指针)
 * @param item2 **元素2**(指针)
 * @note
 */
void Swap(edge_t* item1, edge_t* item2) {
    edge_t tmp = *item1;
    *item1 = *item2;
    *item2 = tmp;
}


/*!
 * @brief <h1>小顶堆SiftDown</h1>
 * @param items **堆元素数组**
 * @param index **执行SiftDown的索引**
 * @param heap_size **堆size**
 */
void MinHeapSiftDown(edge_t* items, int index, int heap_size) {
    /// **for loop** 遍历index结点的子孙节点 : \n
    for (int child_index = 2 * index; child_index <= heap_size; child_index *= 2) {

        /// &emsp; 找到当前结点的左右孩子节点中, 较小的结点
        if (child_index < heap_size && GreaterThan(items + child_index, items + child_index + 1)) {
            child_index++;
        }

        /// &emsp; **if** 当前结点(index索引) <= 最大孩子节点 : \n
        if (!GreaterThan(items + index, items + child_index)) {
            /// &emsp;&emsp; 遍历结束(SiftDown结束) \n
            break;
        }

        /// &emsp; 交换当前结点与最大孩子结点\n
        Swap(items + index, items + child_index);
    }
}


/*!
 * <h1>小顶堆SiftUp</h1>
 * @param items **堆元素数组**
 * @param index **执行SiftUp的索引**
 * @note
 */
void MinHeapSiftUp(edge_t* items, int index) {
    /// **for loop** 遍历index结点的祖先节点 : \n
    for (int parent_index = index / 2; parent_index > 0; parent_index /= 2) {
        /// &emsp; **if** 双亲结点 <= 当前节点 : \n
        if (!GreaterThan(items + parent_index, items + index)) {
            /// &emsp;&emsp; 遍历结束(SiftUp结束) \n
            break;
        }

        /// &emsp; 交换当前结点与双亲结点\n
        Swap(items + parent_index, items + index);
    }
}


/*!
 * @brief <h1>建堆(使用SiftDown)</h1>
 * @param items **堆元素数组**
 * @param heap_size **堆size**
 * @note
 */
void MinHeapBuildBySiftDown(edge_t* items, int heap_size) {
    /// **for loop** 从数组中间向前遍历 : \n
    for (int i = heap_size / 2; i > 0; i--) {
        /// &emsp; 对当前结点执行SiftDown
        MinHeapSiftDown(items, i, heap_size);
    }
}


/*!
 * @brief <h1>最小优先队列初始化</h1>
 * @param min_priority_queue **最小优先队列**
 * @param capacity **队列容量**
 * @return **执行结果**
 * @note
 */
status_t MinPriorityQueueInit(min_priority_queue_t* min_priority_queue, int capacity) {
    /// ### 1 边界条件判断 ###
    /// &emsp; **if** 容量 < 0 或者 容量 > 图结点数的平方 : \n
    if (capacity < 0 || capacity > MAX_VERTEX_CNT * MAX_VERTEX_CNT) {
        /// &emsp;&emsp; 返回ERROR\n
        return ERROR;
    }

    /// ### 2 最小优先队列分配内存and设置属性 ###
    min_priority_queue->items = (edge_t*)malloc(sizeof(edge_t) * (capacity + 1));
    min_priority_queue->capacity = capacity;
    min_priority_queue->size = 0;

    return OK;
}


/*!
 * @brief <h1>最小优先队列入队</h1>
 * @param min_priority_queue **最小优先队列**(指针)
 * @param item **入队元素**
 * @return **执行结果**
 * @note
 */
status_t MinPriorityQueuePush(min_priority_queue_t* min_priority_queue, edge_t item) {

    /// ### 1 满队判断 ###
    /// &emsp; **if** 队列长度 等于 队列容量 : \n
    if (min_priority_queue->size == min_priority_queue->capacity) {
        /// &emsp;&emsp; 队列满, 无法入队, 返回OVERFLOW错误 \n
        return OVERFLOW;
    }

    /// ### 2 在队列元素数组尾部加入元素 ###
    min_priority_queue->items[min_priority_queue->size + 1] = item;
    min_priority_queue->size++;

    /// ### 3 对刚刚插入的元素执行SiftUp ###
    MinHeapSiftUp(min_priority_queue->items, min_priority_queue->size);

    return OK;
}


/*!
 * 最小优先队列队头出队
 * @param min_priority_queue 最小优先队列(指针)
 * @param item 保存出队元素的元素(指针)
 * @return 执行结果
 */
status_t MinPriorityQueuePop(min_priority_queue_t* min_priority_queue, edge_t* item) {
    if (min_priority_queue->size == 0) {
        return ERROR;
    }

    *item = min_priority_queue->items[1];

    min_priority_queue->items[1] = min_priority_queue->items[min_priority_queue->size];
    min_priority_queue->size--;

    MinHeapSiftDown(min_priority_queue->items, 1, min_priority_queue->size);

    return OK;
}

