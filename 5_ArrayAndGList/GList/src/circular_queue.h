/*!
 * @file circular_queue.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  循环队列
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_CIRCULAR_QUEUE_H
#define CYBER_DASH_CIRCULAR_QUEUE_H


#include "common.h"

#define QUEUE_ELEM char
#define MAX_SIZE 100         // 最大队列长度

typedef struct circular_queue circular_queue_t;

struct circular_queue {
    QUEUE_ELEM* elements;
    int front;
    int rear;
};


status_t CircularQueueInit(circular_queue_t* circular_queue);

int CircularQueueGetLength(circular_queue_t circular_queue);

status_t CircularQueueEnQueue(circular_queue_t* circular_queue, QUEUE_ELEM elem);

status_t CircularQueueDeQueue(circular_queue_t* circular_queue, QUEUE_ELEM* elem);

status_t CircularQueueToString(circular_queue_t* circular_queue, char* str, int str_len_limit);


#endif // CYBER_DASH_CIRCULAR_QUEUE_H
