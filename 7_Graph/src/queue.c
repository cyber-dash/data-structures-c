//
// Created by EDY on 2022/4/20.
//

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>


//----- 基本操作的函数原型说明 -----
Status InitQueue(LinkQueue *Q) {
    // 构造一个空队列Q
    Q->rear = (Node*)malloc(sizeof(Node));
    if (!Q->front) {
        exit(OVERFLOW);
    }

    Q->front = Q->rear;
    Q->front->next = NULL;
    return OK;
}


/*!
 *
 * @param Q
 * @param v
 * @return
 */
Status EnQueue(LinkQueue *Q, int v) {
    // 插入元素e为Q的新的队尾元素
    Node *cur = (Node*)malloc(sizeof(Node));
    if (!cur) {
        return OVERFLOW;
    }

    cur->vertexIndex = v;
    cur->next = NULL;

    Q->rear->next = cur;
    Q->rear = cur;

    return OK;
}


/*!
 *
 * @param Q
 * @param v
 * @return
 */
Status DeQueue(LinkQueue *Q, int *v) {
    // 若队列不空, 则删除Q的队头元素, 用e返回其值, 并返回OK;
    // 否则返回ERROR
    if (Q->front == Q->rear) {
        return ERROR;
    }

    Node* p = Q->front->next;
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
int QueueEmpty(LinkQueue *Q) {
    if (Q->front == Q->rear) {
        return 1;
    }

    return 0;
}
