//
// Created by EDY on 2022/7/15.
//

#ifndef CYBER_DASH_TREE_QUEUE_H
#define CYBER_DASH_TREE_QUEUE_H

#include "common.h"
#include "binary_tree_node.h"


#define MAX_SIZE    100 //!< 队列最大长度
#define QUEUE_ELEM  binary_tree_node_t*    //!< 队列元素类型(二叉树结点指针)


/*!
 * @brief 顺序队列结构体
 */
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


#endif // CYBER_DASH_TREE_QUEUE_H
