/*!
 * @file linked_queue.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 链式队列头文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_STACK_QUEUE_H
#define CYBER_DASH_STACK_QUEUE_H


#include "common.h"


/*! @brief 链式队列结点 */
typedef struct linked_queue_node_t {
    QUEUE_ELEM                  data;   //!< 数据项
    struct linked_queue_node_t* next;   //!< 下一结点
} linked_queue_node_t;

/*! @brief 链式队列 */
typedef struct linked_queue_t {
    linked_queue_node_t*    front;  //!< 队头指针
    linked_queue_node_t*    rear;   //!< 队尾指针
} linked_queue_t;


// 链式队列初始化
status_t LinkedQueueInit(linked_queue_t* link_queue);

// 链式队列入队
status_t LinkedQueueEnQueue(linked_queue_t* link_queue, QUEUE_ELEM elem);

// 链式队列出队
status_t LinkedQueueDeQueue(linked_queue_t* linked_queue, QUEUE_ELEM* elem);

// 链式队列长度
int LinkedQueueLength(linked_queue_t linked_queue);

// 打印队列
void LinkedQueuePrint(linked_queue_t* linked_queue);


#endif // CYBER_DASH_STACK_QUEUE_H
