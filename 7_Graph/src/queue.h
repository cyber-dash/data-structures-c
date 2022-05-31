//
// Created by cyberdash@163.com on 2022/4/20.
//

#ifndef CYBER_DASH_GRAPH_QUEUE_H
#define CYBER_DASH_GRAPH_QUEUE_H

#include "graph.h"

typedef struct Node {
    int             vertexIndex;    // 结点索引
    struct Node*    next;           // 下一结点
} Node;

typedef struct LinkQueue {
    Node* front;  // 队头指针
    Node* rear;   // 队尾指针
}LinkQueue;


Status InitQueue(LinkQueue *Q);

Status EnQueue(LinkQueue *Q, int v);

Status DeQueue(LinkQueue *Q, int *v);

int QueueEmpty(LinkQueue *Q);

#endif // CYBER_DASH_GRAPH_QUEUE_H
