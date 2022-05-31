//
// Created by cyberdash@163.com on 2022/1/3.
//

#include <stdio.h>
#include "link_queue.h"
#include "stdlib.h"


//----- 基本操作的函数原型说明 -----
Status InitQueue(LinkQueue *Q) {
    // 构造一个空队列Q
    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
    if (!Q->front) exit(OVERFLOW);
    Q->front->next = NULL;
    return OK;
}


Status LqDestroyQueue(LinkQueue *Q) {
    // 销毁队列Q
    while (Q->front) {
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
    return OK;
}


Status EnQueue(LinkQueue *Q, QElemType v) {
    // 插入元素e为Q的新的队尾元素
    QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
    if (!p) exit(OVERFLOW); // 存储分配失败
    p->data = v;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
    return OK;
}


Status DeQueue(LinkQueue *Q, QElemType *v) {
    // 若队列不空, 则删除Q的队头元素, 用e返回其值, 并返回OK;
    // 否则返回ERROR
    if (Q->front == Q->rear) return ERROR;
    QueuePtr p = Q->front->next;
    *v = p->data;
    Q->front->next = p->next;
    if (Q->rear == p) Q->rear = Q->front;
    free(p);
    return OK;
}


int LqQueueLength(LinkQueue Q) {
    // 返回Q的元素个数, 即为队列的长度
    QueuePtr cur = Q.front;
    int length = 0;

    while (cur != Q.rear) {
        length++;
        cur = cur->next;
    }

    return length;
}


/*
Status ClearQueue(LinkQueue *Q) {
    // 将Q清为空队列

}


Status QueueEmpty(LinkQueue Q) {
    // 若队列Q为空队列, 则返回TRUE, 否则返回FALSE

}


Status GetHead(LinkQueue Q, QElemType *e) {
    // 若度列不空, 则用e返回Q的队头元素, 并返回OK;否则返回ERROR

}


// 从队头到队尾一次对队列Q中每个元素调用函数visit, 一旦visit失败, 则操作失败
Status QueueTraverse(LinkQueue Q, void (*visit)(QNode qNode)) {

}
*/

void PrintLinkQueue(LinkQueue *Q) {
    printf("从队头向队尾打印元素(队头 ... 队尾): \n");

    QNode *cur = Q->front->next;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }

    printf("\n");
}

