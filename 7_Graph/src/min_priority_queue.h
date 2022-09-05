/*!
 * @file min_priority_queue.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 最小优先队列头文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_HEAP_H
#define CYBER_DASH_HEAP_H

#include "graph.h"
#include "queue.h"


/*! @brief 最小优先队列 */
typedef struct {
    edge_t* items;      //!< 队列元素数组
    int size;           //!< 队列长度
    int capacity;       //!< 队列容量
} min_priority_queue_t;


int LessThan(edge_t* item1, edge_t* item2);


int GreaterThan(edge_t* item1, edge_t* item2);


void MinHeapSiftDown(edge_t* items, int index, int heap_size);


void MinHeapSiftUp(edge_t* items, int index);


void MinHeapBuildBySiftDown(edge_t* items, int heap_size);


status_t MinPriorityQueueInit(min_priority_queue_t* min_priority_queue, int capacity);


status_t MinPriorityQueuePush(min_priority_queue_t* min_priority_queue, edge_t item);


status_t MinPriorityQueuePop(min_priority_queue_t* min_priority_queue, edge_t* item);


#endif // CYBER_DASH_HEAP_H