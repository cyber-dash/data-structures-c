/*!
 * @file seq_queue.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  循环队列
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */


#ifndef CYBER_DASH_SEQ_QUEUE_H
#define CYBER_DASH_SEQ_QUEUE_H


#include "common.h"

#define QUEUE_ELEM char
#define MAX_SIZE 100         // 最大队列长度

typedef struct seq_queue_t {
    QUEUE_ELEM* elements;
    int front;
    int rear;
} seq_queue_t;


Status SeqQueueInit(seq_queue_t* seq_queue);

int SeqQueueGetLength(seq_queue_t seq_queue);

Status SeqQueueEnQueue(seq_queue_t* seq_queue, QUEUE_ELEM e);

Status SeqQueueDeQueue(seq_queue_t* seq_queue, QUEUE_ELEM *e);

Status GetTop(seq_queue_t* Q, QUEUE_ELEM *e);

Status SeqQueueToString(seq_queue_t* seq_queue, char* str, int str_len_limit);

void SeqQueuePrint(seq_queue_t *Q);


#endif // CYBER_DASH_SEQ_QUEUE_H
