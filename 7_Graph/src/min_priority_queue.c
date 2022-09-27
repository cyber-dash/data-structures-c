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
 * @brief **小于(<)**
 * @param item1 元素1
 * @param item2 元素2
 * @return 比较结果
 * @note
 * 小于(<)
 * ------
 * ------
 *
 * ------
 * 小于: 1, 等于: 0, 大于: -1
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
 * @brief **大于(>)**
 * @param item1 元素1
 * @param item2 元素2
 * @return 比较结果
 * @note
 * 大于(>)
 * ------
 * ------
 *
 * ------
 * 大于: 1, 等于: 0, 小于: -1
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
 * @brief **交换元素值**
 * @param item1 元素1(指针)
 * @param item2 元素2(指针)
 * @note
 * 交换元素值
 * ---------
 * ---------
 *
 * ---------
 */
void Swap(edge_t* item1, edge_t* item2) {
    edge_t tmp = *item1;
    *item1 = *item2;
    *item2 = tmp;
}


/*!
 * @brief **小顶堆SiftDown**
 * @param items 堆元素数组
 * @param index 执行SiftDown的索引
 * @param heap_size 堆size
 * @note
 * 小顶堆SiftDown
 * -------------
 * -------------
 *
 * -------------
 * **for loop** 遍历index结点的子孙节点 : \n
 * &emsp; 找到当前结点的左右孩子节点中, 最小的结点 \n
 * &emsp; **if** 当前结点(index索引) <= 最小孩子节点 : \n
 * &emsp;&emsp; 遍历结束(SiftDown结束) \n
 * &emsp; 交换当前结点与最小孩子结点\n
 */
void MinHeapSiftDown(edge_t* items, int index, int heap_size) {
    // for loop 遍历index结点的子孙节点
    for (int child_index = 2 * index; child_index <= heap_size; index = child_index, child_index *= 2) {

        // 找到当前结点的左右孩子节点中, 较小的结点
        if (child_index < heap_size && GreaterThan(items + child_index, items + child_index + 1)) {
            child_index++;
        }

        if (!GreaterThan(items + index, items + child_index)) { // if 当前结点(index索引) <= 最小孩子节点
            break;  // 遍历结束(SiftDown结束)
        }

        Swap(items + index, items + child_index);   // 交换当前结点与最小孩子结点
    }
}


/*!
 * @brief **小顶堆SiftUp**
 * @param items 堆元素数组
 * @param index 执行SiftUp的索引
 * @note
 * 小顶堆SiftUp
 * -----------
 * -----------
 *
 * -----------
 * **for loop** 遍历index结点的祖先节点 : \n
 * &emsp; **if** 双亲结点 <= 当前节点 : \n
 * &emsp;&emsp; 遍历结束(SiftUp结束) \n
 * &emsp; 交换当前结点与双亲结点\n
 */
void MinHeapSiftUp(edge_t* items, int index) {
    // for loop 遍历index结点的祖先节点
    for (int parent_index = index / 2; parent_index > 0; index = parent_index, parent_index /= 2) {
        if (!GreaterThan(items + parent_index, items + index)) {    // if 双亲结点 <= 当前节点
            break;  // 遍历结束(SiftUp结束)
        }

        Swap(items + parent_index, items + index);  // 交换当前结点与双亲结点
    }
}


/*!
 * @brief **建堆(使用SiftDown)**
 * @param items 堆元素数组
 * @param heap_size 堆size
 * @note
 * 建堆(使用SiftDown)
 * -----------------
 * -----------------
 *
 * -----------------
 * **for loop** 从数组中间向前遍历 : \n
 * &emsp; 对当前结点执行SiftDown
 */
void MinHeapBuildBySiftDown(edge_t* items, int heap_size) {
    for (int i = heap_size / 2; i > 0; i--) {   // for loop 从数组中间向前遍历
        MinHeapSiftDown(items, i, heap_size);    // 对当前结点执行SiftDown
    }
}


/*!
 * @brief **最小优先队列初始化**
 * @param min_priority_queue 最小优先队列
 * @param capacity 队列容量
 * @return 执行结果
 * @note
 * 最小优先队列初始化
 * ----------------
 * ----------------
 *
 * ----------------
 * ### 1 边界条件判断 ###
 * &emsp; **if** 容量 < 0 或者 容量 > 图结点数的平方 : \n
 * &emsp;&emsp; 返回ERROR\n
 * ### 2 最小优先队列分配内存and设置属性 ###
 */
status_t MinPriorityQueueInit(min_priority_queue_t* min_priority_queue, int capacity) {
    // ----- 1 边界条件判断 -----
    if (capacity < 0 || capacity > MAX_VERTEX_CNT * MAX_VERTEX_CNT) {   // if 容量 < 0 或者 容量 > 图结点数的平方
        return ERROR;   // 返回ERROR
    }

    // ----- 2 最小优先队列分配内存and设置属性 -----
    min_priority_queue->items = (edge_t*)malloc(sizeof(edge_t) * (capacity + 1));
    min_priority_queue->capacity = capacity;
    min_priority_queue->size = 0;

    return OK;
}


/*!
 * @brief **最小优先队列入队**
 * @param min_priority_queue 最小优先队列(指针)
 * @param item 入队元素
 * @return 执行结果
 * @note
 * 最小优先队列入队
 * --------------
 * --------------
 *
 * --------------
 * ### 1 满队判断 ###
 * &emsp; **if** 队列长度 等于 队列容量 : \n
 * &emsp;&emsp; 队列满, 无法入队, 返回OVERFLOW错误 \n
 * ### 2 在队列元素数组尾部加入元素 ###
 * ### 3 对刚刚插入的元素执行SiftUp ###
 */
status_t MinPriorityQueuePush(min_priority_queue_t* min_priority_queue, edge_t item) {

    // ----- 1 满队判断 -----
    if (min_priority_queue->size == min_priority_queue->capacity) { // if 队列长度 等于 队列容量
        return OVERFLOW;    // 队列满, 无法入队, 返回OVERFLOW错误
    }

    // ----- 2 在队列元素数组尾部加入元素 -----
    min_priority_queue->items[min_priority_queue->size + 1] = item;
    min_priority_queue->size++;

    // ----- 3 对刚刚插入的元素执行SiftUp -----
    MinHeapSiftUp(min_priority_queue->items, min_priority_queue->size);

    return OK;
}


/*!
 * @brief **最小优先队列队头出队**
 * @param min_priority_queue 最小优先队列(指针)
 * @param item 保存出队元素的元素(指针)
 * @return 执行结果
 * @note
 * 最小优先队列队头出队
 * -----------------
 * -----------------
 *
 * -----------------
 * ### 1 空队判断 ###
 * &emsp; **if** 队列长度 等于 0: \n
 * &emsp;&emsp; 空队, 无法出队, 返回ERROR错误 \n
 * ### 2 队头元素赋给*item ###
 * ### 3 调整优先队列 ###
 * &emsp; 队尾元素赋值给队头 \n
 * &emsp; size - 1 \n
 * &emsp; 对队头执行SiftDown \n
 */
status_t MinPriorityQueuePop(min_priority_queue_t* min_priority_queue, edge_t* item) {
    // ----- 1 空队判断 -----
    if (min_priority_queue->size == 0) {    // if 队列长度 等于 0
        return ERROR;   // 空队, 无法出队, 返回ERROR错误
    }

    // ----- 2 队头元素赋给*item -----
    *item = min_priority_queue->items[1];

    // ----- 3 调整优先队列 -----
    min_priority_queue->items[1] = min_priority_queue->items[min_priority_queue->size]; // 队尾元素赋值给队头
    min_priority_queue->size--; // size - 1

    MinHeapSiftDown(min_priority_queue->items, 1, min_priority_queue->size);    // 对队头执行SiftDown

    return OK;
}

