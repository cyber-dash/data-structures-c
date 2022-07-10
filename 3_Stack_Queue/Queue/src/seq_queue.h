/*!
 * @file seq_queue.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 队列 顺序队列
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */


#ifndef CYBER_DASH_SEQ_QUEUE_H
#define CYBER_DASH_SEQ_QUEUE_H

#include "type.h"


#define MAX_SIZE    100 //!< 队列最大长度
#define QUEUE_ELEM  int //!< 队列元素的类型


//!< 顺序队列结构体
typedef struct {
    QUEUE_ELEM* elements;   //!< 队列元素数组
    int front;              //!< 队头
    int rear;               //!< 队尾
} seq_queue_t;


// 顺序队列初始化
Status SeqQueueInit(seq_queue_t* seq_queue);

// 顺序队列长度
int SeqQueueLength(seq_queue_t seq_queue);

// 顺序队列入队
Status SeqQueueEnQueue(seq_queue_t* seq_queue, QUEUE_ELEM elem);

// 顺序队列出队
Status SeqQueueDeQueue(seq_queue_t* seq_queue, QUEUE_ELEM* elem);

// 顺序队列屏幕打印
void SeqQueuePrint(seq_queue_t* seq_queue);


#endif // CYBER_DASH_SEQ_QUEUE_H
