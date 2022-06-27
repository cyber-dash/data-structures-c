//
// Created by cyberdash@163.com on 2022/2/16.
//

#ifndef CYBER_DASH_SEQ_QUEUE_H
#define CYBER_DASH_SEQ_QUEUE_H

#include "type.h"


#define MAX_SIZE    100         // 最大队列长度
#define QUEUE_ELEM  int

typedef struct {
    QUEUE_ELEM* elements;
    int front;
    int rear;
} seq_queue_t;


Status SeqQueueInit(seq_queue_t* seq_queue);

int SeqQueueLength(seq_queue_t seq_queue);

Status SeqQueueEnQueue(seq_queue_t* seq_queue, QUEUE_ELEM elem);

Status SeqQueueDeQueue(seq_queue_t* seq_queue, QUEUE_ELEM* elem);

void SeqQueuePrint(seq_queue_t* seq_queue);


#endif // CYBER_DASH_SEQ_QUEUE_H
