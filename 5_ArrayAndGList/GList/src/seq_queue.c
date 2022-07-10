/*!
 * @file seq_queue.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  循环队列
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "seq_queue.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"


// ----- 循环队列的基本操作的算法描述 -----
Status InitQueue(seq_queue_t *Q) {
    // 构造一个空队列Q
    Q->elements = (QUEUE_ELEM*)malloc(MAX_SIZE * sizeof(QUEUE_ELEM));
    // 存储分配失败
    if (!Q->elements) {
        exit(ALLOC_UNINITIALIZED);
    }

    memset(Q->elements, 0, MAX_SIZE * sizeof(QUEUE_ELEM));

    Q->front = 0;
    Q->rear = 0;

    return OK;
}


int GetLength(seq_queue_t Q) {
    // 返回Q的元素个数, 即队列的长度
    return (Q.rear - Q.front + MAX_SIZE) % MAX_SIZE;
}


Status EnQueue(seq_queue_t *Q, QUEUE_ELEM e) {
    // 插入元素e为Q的新的队尾元素
    if ((Q->rear + 1) % MAX_SIZE == Q->front)
        return ERROR; // 队列满
    Q->elements[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAX_SIZE;
    return OK;
}


Status DeQueue(seq_queue_t *Q, QUEUE_ELEM *e) {
    // 若队列不空, 则删除Q的队头元素, 用e返回其值, 并返回OK;
    // 否则返回ERROR
    if (Q->front == Q->rear) return ERROR;
    *e = Q->elements[Q->front];
    Q->front = (Q->front + 1) % MAX_SIZE;
    return OK;
}


Status GetTop(seq_queue_t *Q, QUEUE_ELEM *e) {
    // 若队列不空, 则删除Q的队头元素, 用e返回其值, 并返回OK;
    // 否则返回ERROR
    if (Q->front == Q->rear) return ERROR;
    *e = Q->elements[Q->front];
    return OK;
}


// todo: 你可以加个参数, 限制字符串复制长度 :-)
Status ToString(seq_queue_t *Q, char *queue_str) {

    if (Q->front == Q->rear) {
        return OK;
    }

    int loop_stop_condition;
    if (Q->front < Q->rear) {
        loop_stop_condition = Q->rear;
    } else {
        loop_stop_condition = Q->rear + MAX_SIZE;
    }

    int queue_str_idx = 0;
    for (int i = Q->front; i < loop_stop_condition; i++) {
        queue_str[queue_str_idx] = Q->elements[i % MAX_SIZE];
        queue_str_idx++;
    }

    return OK;
}


/*!
 * @brief 打印顺序队列
 * @param Q
 */
void PrintQueue(seq_queue_t *Q) {
    printf("从队头向队尾打印元素(队头 ... 队尾):\n");

    int cur = Q->front;
    while (cur < Q->rear) {
        printf("%d ", Q->elements[cur]);
        cur++;
    }

    printf("\n");
}
