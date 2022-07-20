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
#include "string.h"


// ----- 循环队列的基本操作的算法描述 -----
Status SeqQueueInit(seq_queue_t* seq_queue) {
    // 构造一个空队列Q
    seq_queue->elements = (QUEUE_ELEM*)malloc(MAX_SIZE * sizeof(QUEUE_ELEM));
    // 存储分配失败
    if (!seq_queue->elements) {
        return NON_ALLOCATED;
    }

    memset(seq_queue->elements, 0, MAX_SIZE * sizeof(QUEUE_ELEM));

    seq_queue->front = 0;
    seq_queue->rear = 0;

    return OK;
}


int SeqQueueGetLength(seq_queue_t seq_queue) {
    // 返回Q的元素个数, 即队列的长度
    return (seq_queue.rear - seq_queue.front + MAX_SIZE) % MAX_SIZE;
}


Status SeqQueueEnQueue(seq_queue_t* seq_queue, QUEUE_ELEM e) {
    // 插入元素e为Q的新的队尾元素
    if ((seq_queue->rear + 1) % MAX_SIZE == seq_queue->front)
        return ERROR; // 队列满
    seq_queue->elements[seq_queue->rear] = e;
    seq_queue->rear = (seq_queue->rear + 1) % MAX_SIZE;
    return OK;
}


Status SeqQueueDeQueue(seq_queue_t* seq_queue, QUEUE_ELEM *e) {
    // 若队列不空, 则删除Q的队头元素, 用e返回其值, 并返回OK;
    // 否则返回ERROR
    if (seq_queue->front == seq_queue->rear) return ERROR;
    *e = seq_queue->elements[seq_queue->front];
    seq_queue->front = (seq_queue->front + 1) % MAX_SIZE;
    return OK;
}


/*!
 * <h1>顺序表转换成字符串</h1>
 * @param seq_queue **顺序表**(指针)
 * @param str **字符串**
 * @param str_len_limit **字符串长度限制**
 * @return 执行结果
 * @note
 */
Status SeqQueueToString(seq_queue_t* seq_queue, char* str, int str_len_limit) {

    if (seq_queue->front == seq_queue->rear) {
        return OK;
    }

    int loop_stop_condition;
    if (seq_queue->front < seq_queue->rear) {
        loop_stop_condition = seq_queue->rear;
    } else {
        loop_stop_condition = seq_queue->rear + MAX_SIZE;
    }

    if (loop_stop_condition - seq_queue->front > str_len_limit) {
        return OVERFLOW;
    }

    int queue_str_idx = 0;
    for (int i = seq_queue->front; i < loop_stop_condition; i++) {
        str[queue_str_idx] = seq_queue->elements[i % MAX_SIZE];
        queue_str_idx++;
    }

    return OK;
}
