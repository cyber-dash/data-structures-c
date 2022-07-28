/*!
 * @file queue.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 队列
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_GRAPH_QUEUE_H
#define CYBER_DASH_GRAPH_QUEUE_H


#include "graph.h"


typedef struct linked_queue_node linked_queue_node_t;
typedef struct linked_queue_node {
    int     vertex_index;   // 结点索引
    linked_queue_node_t* next;           // 下一结点
} linked_queue_node_t;

typedef struct {
    linked_queue_node_t* front;  // 队头指针
    linked_queue_node_t* rear;   // 队尾指针
} linked_queue_t;


status_t LinkedQueueInit(linked_queue_t* link_queue);

status_t LinkedQueueEnQueue(linked_queue_t* queue, int v);

status_t LinkedQueueDeQueue(linked_queue_t* queue, int* v);

int LinkedQueueIsEmpty(linked_queue_t* queue);


#endif // CYBER_DASH_GRAPH_QUEUE_H
