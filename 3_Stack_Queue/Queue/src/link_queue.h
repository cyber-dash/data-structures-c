/*!
 * @file linked_queue.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 队列 链式队列
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_STACK_QUEUE_H
#define CYBER_DASH_STACK_QUEUE_H

#include "common.h"


typedef struct linked_queue_node_t {
    QUEUE_ELEM                  data;
    struct linked_queue_node_t* next;
} linked_queue_node_t;

typedef struct linked_queue_t {
    linked_queue_node_t*    front;  //!< 队头指针
    linked_queue_node_t*    rear;   //!< 队尾指针
} linked_queue_t;


status_t LinkQueueInit(linked_queue_t* linked_queue);

status_t LinkQueueEnQueue(linked_queue_t* linked_queue, QUEUE_ELEM elem);

status_t LinkQueueDeQueue(linked_queue_t* linked_queue, QUEUE_ELEM* elem);

int LinkQueueLength(linked_queue_t linked_queue);

void LinkQueuePrint(linked_queue_t* linked_queue);


#endif // CYBER_DASH_STACK_QUEUE_H
