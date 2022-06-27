//
// Created by cyberdash@163.com on 2022/1/3.
//

#ifndef CYBER_DASH_STACK_QUEUE_H
#define CYBER_DASH_STACK_QUEUE_H

#include "type.h"


typedef struct link_queue_node_t {
    QUEUE_ELEM                  data;
    struct link_queue_node_t*   next;
} link_queue_node_t;

typedef struct link_queue_t {
    link_queue_node_t*  front;  // 队头指针
    link_queue_node_t*  rear;   // 队尾指针
} link_queue_t;


Status LinkQueueInit(link_queue_t* link_queue);

Status LinkQueueEnQueue(link_queue_t *link_queue, QUEUE_ELEM elem);

Status LinkQueueDeQueue(link_queue_t *link_queue, QUEUE_ELEM *elem);

int LinkQueueLength(link_queue_t link_queue);

void LinkQueuePrint(link_queue_t *link_queue);


#endif // CYBER_DASH_STACK_QUEUE_H
