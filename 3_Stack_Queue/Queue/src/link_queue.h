//
// Created by cyberdash@163.com on 2022/1/3.
//

#ifndef CYBER_DASH_STACK_QUEUE_H
#define CYBER_DASH_STACK_QUEUE_H

#include "type.h"


typedef struct QNode {
    QElemType       data;
    struct QNode    *next;
} QNode, *QueuePtr;
typedef struct LinkQueue {
    QueuePtr    front;  // 队头指针
    QueuePtr    rear;   // 队尾指针
}LinkQueue;


Status InitQueue(LinkQueue *Q);

Status EnQueue(LinkQueue *Q, QElemType v);

Status DeQueue(LinkQueue *Q, QElemType *v);

int LqQueueLength(LinkQueue Q);

void PrintLinkQueue(LinkQueue *Q);


#endif // CYBER_DASH_STACK_QUEUE_H
