//
// Created by cyberdash@163.com on 2022/2/16.
//

#ifndef CYBER_DASH_SQ_QUEUE_H
#define CYBER_DASH_SQ_QUEUE_H


#include "type.h"

#define QueueElem char
#define MAXSIZE 100         // 最大队列长度

typedef struct {
    QueueElem   *base;
    int front;
    int rear;
}SqQueue;


Status InitQueue(SqQueue *Q);

int GetLength(SqQueue Q);

Status EnQueue(SqQueue *Q, QueueElem e);

Status DeQueue(SqQueue *Q, QueueElem *e);

Status GetTop(SqQueue *Q, QueueElem *e);

Status ToString(SqQueue *Q, char *queue_str);




void PrintQueue(SqQueue *Q);


#endif // CYBER_DASH_SQ_QUEUE_H
