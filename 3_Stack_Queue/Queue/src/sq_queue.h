//
// Created by cyberdash@163.com on 2022/2/16.
//

#ifndef CYBER_DASH_SQ_QUEUE_H
#define CYBER_DASH_SQ_QUEUE_H

#include "type.h"


#define MAXSIZE 100         // 最大队列长度
#define QElemType int
typedef struct {
    QElemType   *base;
    int front;
    int rear;
}SqQueue;


Status SqInitQueue(SqQueue *Q);

int SqQueueLength(SqQueue Q);

Status SqEnQueue(SqQueue *Q, QElemType e);

Status SqDeQueue(SqQueue *Q, QElemType *e);

void PrintSqQueue(SqQueue *Q);


#endif // CYBER_DASH_SQ_QUEUE_H
