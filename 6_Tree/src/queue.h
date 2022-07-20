/*!
 * @file queue.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 队列头文件
 * @version 1.0.0
 * @date 2022-07-15
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_TREE_QUEUE_H
#define CYBER_DASH_TREE_QUEUE_H

#include "common.h"
#include "binary_tree_node.h"


#define MAX_SIZE    100                    //!< 队列最大长度
#define QUEUE_ELEM  binary_tree_node_t*    //!< 队列元素类型(二叉树结点指针)


/*! @brief 循环队列结构体 */
typedef struct {
    QUEUE_ELEM* elements;   //!< 队列元素数组
    int front;              //!< 队头
    int rear;               //!< 队尾
} circular_queue_t;


// 循环队列初始化
status_t CircularQueueInit(circular_queue_t* circular_queue);

// 循环队列长度
int CircularQueueGetLength(circular_queue_t circular_queue);

// 循环队列入队
status_t CircularQueueEnQueue(circular_queue_t* circular_queue, QUEUE_ELEM elem);

// 循环队列出队
status_t CircularQueueDeQueue(circular_queue_t* circular_queue, QUEUE_ELEM* elem);


#endif // CYBER_DASH_TREE_QUEUE_H
