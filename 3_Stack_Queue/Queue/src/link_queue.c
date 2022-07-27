/*!
 * @file link_queue.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  队列 链式队列
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdio.h>
#include "link_queue.h"
#include "stdlib.h"


/*!
 * <h1>链式队列初始化</h1>
 * @param link_queue **链式队列**(指针)
 * @return **执行结果**
 * @note
 */
status_t LinkQueueInit(linked_queue_t* link_queue) {
    /// ###1 链式队列rear分配内存###
    /// &emsp; **if** 如果malloc失败 :\n
    /// &emsp;&emsp; 返回NON_ALLOCATED
    link_queue->rear = (linked_queue_node_t*)malloc(sizeof(linked_queue_node_t));
    if (!link_queue->rear) {
        return NON_ALLOCATED;
    }

    /// ###2 链式队列front处理###
    /// &emsp; front指向rear, front->next = NULL;
    link_queue->front = link_queue->rear;
    link_queue->front->next = NULL;

    return OK;
}


/*!
 * <h1>链式队列销毁</h1>
 * @param link_queue **链式队列**(指针)
 * @return **执行结果**
 * @note
 */
status_t LinkQueueDestroy(linked_queue_t* link_queue) {
    while (link_queue->front) {
        link_queue->rear = link_queue->front->next;
        free(link_queue->front);

        link_queue->front = link_queue->rear;
    }

    return OK;
}


/*!
 * @brief <h1>链式队列入队</h1>
 * @param link_queue **链式队列**(指针)
 * @param elem **入队元素**
 * @return **执行结果**
 * @note
 */
status_t LinkQueueEnQueue(linked_queue_t* link_queue, QUEUE_ELEM elem) {
    /// ###1 新结点内存分配###
    /// &emsp; **if** 如果malloc失败 :\n
    /// &emsp;&emsp; 返回NON_ALLOCATED
    linked_queue_node_t* new_node = (linked_queue_node_t*)malloc(sizeof(linked_queue_node_t));
    if (!new_node) {
        return NON_ALLOCATED; // 存储分配失败
    }

    /// ###2 新节点结构体变量赋值###
    new_node->data = elem;
    new_node->next = NULL;

    /// ###3 rear指针处理###
    /// - **I**&nbsp;&nbsp; rear->next指向新节点
    /// - **II**&nbsp; rear指向新节点
    link_queue->rear->next = new_node;
    link_queue->rear = new_node;

    return OK;
}


/*!
 * <h1>链式队列出队</h1>
 * @param seq_queue **顺序队列**(指针)
 * @param elem **出队元素保存变量**(指针)
 * @return **执行结果**
 * @note
 */
status_t LinkQueueDeQueue(linked_queue_t* linked_queue, QUEUE_ELEM* elem) {
    /// ###1 空队判断###
    /// &emsp; **if** front等于rear : \n
    /// &emsp;&emsp; 空队, 返回NON_EXISTENT\n
    if (linked_queue->front == linked_queue->rear) {
        return NON_EXISTENT;
    }

    /// ###2 出队###
    /// - **I**&nbsp;&nbsp; 出队结点数据项赋值给*elem
    /// - **II**&nbsp; front->next指向出队结点的next
    /// - **III** 释放出队结点
    linked_queue_node_t* dequeue_node = linked_queue->front->next;
    *elem = dequeue_node->data;

    linked_queue->front->next = dequeue_node->next;

    free(dequeue_node);
    dequeue_node = NULL;

    return OK;
}


/*!
 * @brief <h1>链式队列长度</h1>
 * @param linked_queue **链式队列**
 * @return **长度**
 * @note
 */
int LinkQueueLength(linked_queue_t linked_queue) {
    linked_queue_node_t* cur = linked_queue.front;
    int length = 0;

    while (cur != linked_queue.rear) {
        length++;
        cur = cur->next;
    }

    return length;
}


/*!
 *
 * @param linked_queue
 */
void LinkQueuePrint(linked_queue_t* linked_queue) {
    printf("从队头向队尾打印元素(队头 ... 队尾): \n");

    linked_queue_node_t *cur = linked_queue->front->next;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }

    printf("\n");
}

