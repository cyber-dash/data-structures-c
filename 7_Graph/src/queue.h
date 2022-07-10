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


typedef struct node_t {
    int             vertexIndex;    // 结点索引
    struct node_t*    next;           // 下一结点
} node_t;

typedef struct {
    node_t* front;  // 队头指针
    node_t* rear;   // 队尾指针
} linked_queue_node_t, *linked_queue_t;


Status InitQueue(linked_queue_node_t* link_queue);

Status EnQueue(linked_queue_node_t* queue, int v);

Status DeQueue(linked_queue_node_t* queue, int* v);

int QueueEmpty(linked_queue_node_t* queue);


#endif // CYBER_DASH_GRAPH_QUEUE_H
