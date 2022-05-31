//
// Created by cyberdash@163.com on 2022/2/16.
//

#include "sq_queue.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"


// ----- 循环队列的基本操作的算法描述 -----
Status InitQueue(SqQueue *Q) {
    // 构造一个空队列Q
    Q->base = (QueueElem*)malloc(MAXSIZE * sizeof(QueueElem));
    // 存储分配失败
    if (!Q->base) {
        exit(ALLOC_UNINITIALIZED);
    }

    memset(Q->base, 0, MAXSIZE * sizeof(QueueElem));

    Q->front = 0;
    Q->rear = 0;

    return OK;
}


int GetLength(SqQueue Q) {
    // 返回Q的元素个数, 即队列的长度
    return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}


Status EnQueue(SqQueue *Q, QueueElem e) {
    // 插入元素e为Q的新的队尾元素
    if ((Q->rear + 1) % MAXSIZE == Q->front)
        return ERROR; // 队列满
    Q->base[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}


Status DeQueue(SqQueue *Q, QueueElem *e) {
    // 若队列不空, 则删除Q的队头元素, 用e返回其值, 并返回OK;
    // 否则返回ERROR
    if (Q->front == Q->rear) return ERROR;
    *e = Q->base[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return OK;
}


Status GetTop(SqQueue *Q, QueueElem *e) {
    // 若队列不空, 则删除Q的队头元素, 用e返回其值, 并返回OK;
    // 否则返回ERROR
    if (Q->front == Q->rear) return ERROR;
    *e = Q->base[Q->front];
    return OK;
}


// todo: 你可以加个参数, 限制字符串复制长度 :-)
Status ToString(SqQueue *Q, char *queue_str) {

    if (Q->front == Q->rear) {
        return OK;
    }

    int loop_stop_condition;
    if (Q->front < Q->rear) {
        loop_stop_condition = Q->rear;
    } else {
        loop_stop_condition = Q->rear + MAXSIZE;
    }

    int queue_str_idx = 0;
    for (int i = Q->front; i < loop_stop_condition; i++) {
        queue_str[queue_str_idx] = Q->base[i % MAXSIZE];
        queue_str_idx++;
    }

    return OK;
}


/*!
 * @brief 打印顺序队列
 * @param Q
 */
void PrintQueue(SqQueue *Q) {
    printf("从队头向队尾打印元素(队头 ... 队尾):\n");

    int cur = Q->front;
    while (cur < Q->rear) {
        printf("%d ", Q->base[cur]);
        cur++;
    }

    printf("\n");
}
