/*!
 * @file circular_queue.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  循环队列
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "circular_queue.h"
#include "stdlib.h"
#include "string.h"


// ----- 循环队列的基本操作的算法描述 -----
status_t CircularQueueInit(circular_queue_t* circular_queue) {
    // 构造一个空队列Q
    circular_queue->elements = (QUEUE_ELEM*)malloc(MAX_SIZE * sizeof(QUEUE_ELEM));
    // 存储分配失败
    if (!circular_queue->elements) {
        return NON_ALLOCATED;
    }

    memset(circular_queue->elements, 0, MAX_SIZE * sizeof(QUEUE_ELEM));

    circular_queue->front = 0;
    circular_queue->rear = 0;

    return OK;
}


int CircularQueueGetLength(circular_queue_t circular_queue) {
    // 返回Q的元素个数, 即队列的长度
    return (circular_queue.rear - circular_queue.front + MAX_SIZE) % MAX_SIZE;
}


status_t CircularQueueEnQueue(circular_queue_t* circular_queue, QUEUE_ELEM elem) {
    // 插入元素e为Q的新的队尾元素
    if ((circular_queue->rear + 1) % MAX_SIZE == circular_queue->front) {
        return OVERFLOW; // 队列满
    }

    circular_queue->elements[circular_queue->rear] = elem;
    circular_queue->rear = (circular_queue->rear + 1) % MAX_SIZE;

    return OK;
}


status_t CircularQueueDeQueue(circular_queue_t* circular_queue, QUEUE_ELEM* elem) {
    // 若队列不空, 则删除Q的队头元素, 用e返回其值, 并返回OK;
    // 否则返回ERROR
    if (circular_queue->front == circular_queue->rear) {
        return NON_EXISTENT;
    }

    *elem = circular_queue->elements[circular_queue->front];
    circular_queue->front = (circular_queue->front + 1) % MAX_SIZE;

    return OK;
}


/*!
 * <h1>顺序表转换成字符串</h1>
 * @param circular_queue **顺序表**(指针)
 * @param str **字符串**
 * @param str_len_limit **字符串长度限制**
 * @return 执行结果
 * @note
 */
status_t CircularQueueToString(circular_queue_t* circular_queue, char* str, int str_len_limit) {

    if (circular_queue->front == circular_queue->rear) {
        return OK;
    }

    int loop_stop_condition;
    if (circular_queue->front < circular_queue->rear) {
        loop_stop_condition = circular_queue->rear;
    } else {
        loop_stop_condition = circular_queue->rear + MAX_SIZE;
    }

    if (loop_stop_condition - circular_queue->front > str_len_limit) {
        return OVERFLOW;
    }

    int queue_str_idx = 0;
    for (int i = circular_queue->front; i < loop_stop_condition; i++) {
        str[queue_str_idx] = circular_queue->elements[i % MAX_SIZE];
        queue_str_idx++;
    }

    return OK;
}
