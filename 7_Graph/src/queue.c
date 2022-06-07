//
// Created by EDY on 2022/4/20.
//

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>


//----- 基本操作的函数原型说明 -----
Status InitQueue(linked_queue_node_t *queue) {
    // 构造一个空队列Q
    queue->rear = (node_t*)malloc(sizeof(node_t));
    if (!queue->front) {
        exit(OVERFLOW);
    }

    queue->front = queue->rear;
    queue->front->next = NULL;
    return OK;
}


/*!
 *
 * @param queue
 * @param v
 * @return
 */
Status EnQueue(linked_queue_node_t *queue, int v) {
    // 插入元素e为Q的新的队尾元素
    node_t *cur = (node_t*)malloc(sizeof(node_t));
    if (!cur) {
        return OVERFLOW;
    }

    cur->vertexIndex = v;
    cur->next = NULL;

    queue->rear->next = cur;
    queue->rear = cur;

    return OK;
}


/*!
 *
 * @param Q
 * @param v
 * @return
 */
Status DeQueue(linked_queue_node_t *Q, int *v) {
    // 若队列不空, 则删除Q的队头元素, 用e返回其值, 并返回OK;
    // 否则返回ERROR
    if (Q->front == Q->rear) {
        return ERROR;
    }

    node_t* p = Q->front->next;
    *v = p->vertexIndex;
    Q->front->next = p->next;

    if (Q->rear == p) {
        Q->rear = Q->front;
    }

    free(p);
    return OK;
}


/*!
 *
 * @param Q
 * @return
 */
int QueueEmpty(linked_queue_node_t *Q) {
    if (Q->front == Q->rear) {
        return 1;
    }

    return 0;
}
