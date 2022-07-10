/*!
 * @file seq_queue.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 队列 顺序队列
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */


#include "seq_queue.h"
#include "stdlib.h"
#include "stdio.h"


/*!
 *
 * @param seq_queue
 * @return
 */
Status SeqQueueInit(seq_queue_t* seq_queue) {
    // 构造一个空队列Q
    seq_queue->elements = (QUEUE_ELEM*)malloc(MAX_SIZE * sizeof(QUEUE_ELEM));
    if (!seq_queue->elements) {
        return NON_ALLOCATED;
    }

    seq_queue->front = 0;
    seq_queue->rear = 0;

    return OK;
}


/*!
 *
 * @param seq_queue
 * @return
 */
int SeqQueueLength(seq_queue_t seq_queue) {
    // 返回Q的元素个数, 即队列的长度
    return (seq_queue.rear - seq_queue.front + MAX_SIZE) % MAX_SIZE;
}


/*!
 * 顺序队列入队
 * @param seq_queue 顺序队列(指针)
 * @param elem 入队元素
 * @return 执行结果
 */
Status SeqQueueEnQueue(seq_queue_t* seq_queue, QUEUE_ELEM elem) {

    // 判断队列是否已经满, 如果满, 返回OVERFLOW
    if ((seq_queue->rear + 1) % MAX_SIZE == seq_queue->front) {
        return OVERFLOW;
    }

    // 元素elem插入到队列seq_queue的队尾
    seq_queue->elements[seq_queue->rear] = elem;
    // 更新rear值
    seq_queue->rear = (seq_queue->rear + 1) % MAX_SIZE;

    return OK;
}


/*!
 *
 * @param seq_queue
 * @param elem
 * @return
 */
Status SeqQueueDeQueue(seq_queue_t* seq_queue, QUEUE_ELEM* elem) {
    // 若队列不空, 则删除Q的队头元素, 用e返回其值, 并返回OK;
    // 否则返回ERROR
    if (seq_queue->front == seq_queue->rear) {
        return ERROR;
    }

    *elem = seq_queue->elements[seq_queue->front];
    seq_queue->front = (seq_queue->front + 1) % MAX_SIZE;

    return OK;
}


/*!
 * @brief 打印顺序队列
 * @param seq_queue
 */
void SeqQueuePrint(seq_queue_t* seq_queue) {
    printf("从队头向队尾打印元素(队头 ... 队尾):\n");

    int cur = seq_queue->front;
    while (cur < seq_queue->rear) {
        printf("%d ", seq_queue->elements[cur]);
        cur++;
    }

    printf("\n");
}
