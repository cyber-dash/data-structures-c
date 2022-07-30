/*!
 * @file queue.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 链式队列头文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_GRAPH_QUEUE_H
#define CYBER_DASH_GRAPH_QUEUE_H


#include "graph.h"

/*! @brief 链式队列结点类型 */
typedef struct linked_queue_node linked_queue_node_t;

/*! @brief 链式队列结点结构体 */
struct linked_queue_node {
    int     vertex_index;       //!< 图结点索引
    linked_queue_node_t* next;  //!< 下一队列结点
};

/*! @brief 链式队列 */
typedef struct {
    linked_queue_node_t* front;  //!< 队头指针
    linked_queue_node_t* rear;   //!< 队尾指针
} linked_queue_t;


status_t LinkedQueueInit(linked_queue_t* link_queue);

status_t LinkedQueueEnQueue(linked_queue_t* linked_queue, int vertex_index);

status_t LinkedQueueDeQueue(linked_queue_t* linked_queue, int* vertex_index);

int LinkedQueueIsEmpty(linked_queue_t* linked_queue);


#endif // CYBER_DASH_GRAPH_QUEUE_H
