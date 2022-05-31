//
// Created by cyberdash@163.com on 2022/2/16.
//

#include "sq_queue.h"
#include "stdlib.h"
#include "stdio.h"


// ----- 循环队列的基本操作的算法描述 -----
Status SqInitQueue(SqQueue *Q) {
    // 构造一个空队列Q
    Q->base = (QElemType*)malloc(MAXSIZE * sizeof(QElemType));
    if (!Q->base) exit(OVERFLOW);   // 存储分配失败
    // Q->front = Q->rear = 0;
    Q->front = 0;
    Q->rear = 0;
    return OK;
}


int SqQueueLength(SqQueue Q) {
    // 返回Q的元素个数, 即队列的长度
    return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}


Status SqEnQueue(SqQueue *Q, QElemType e) {
    // 插入元素e为Q的新的队尾元素
    if ((Q->rear + 1) % MAXSIZE == Q->front)
        return ERROR; // 队列满
    Q->base[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}


Status SqDeQueue(SqQueue *Q, QElemType *e) {
    // 若队列不空, 则删除Q的队头元素, 用e返回其值, 并返回OK;
    // 否则返回ERROR
    if (Q->front == Q->rear) return ERROR;
    *e = Q->base[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return OK;
}


/*!
 * @brief 打印顺序队列
 * @param Q
 */
void PrintSqQueue(SqQueue *Q) {
    printf("从队头向队尾打印元素(队头 ... 队尾):\n");
    int cur = Q->front;
    while (cur < Q->rear) {
        printf("%d ", Q->base[cur]);
        cur++;
    }

    printf("\n");
}
