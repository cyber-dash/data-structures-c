/*!
 * @file link_queue.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 链式队列源文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdio.h>
#include "linked_queue.h"
#include "stdlib.h"


/*!
 * @brief **链式队列初始化**
 * @param link_queue 链式队列(指针)
 * @return 执行结果
 * @note
 * 链式队列初始化
 * ------------
 * ------------
 *
 * ------------
 * ###1 链式队列rear分配内存###
 * &emsp; **if** 如果malloc失败 :\n
 * &emsp;&emsp; 返回NON_ALLOCATED\n
 * ###2 链式队列front处理###
 * &emsp; front指向rear\n
 * &emsp; front->next = NULL\n
 */
status_t LinkedQueueInit(linked_queue_t* link_queue) {
    // ----- 1 链式队列rear分配内存 -----
    link_queue->rear = (linked_queue_node_t*)malloc(sizeof(linked_queue_node_t));
    if (!link_queue->rear) {    // if 如果malloc失败
        return NON_ALLOCATED;   // 返回NON_ALLOCATED
    }

    // ----- 2 链式队列front处理 -----
    link_queue->front = link_queue->rear;   // front指向rear
    link_queue->front->next = NULL;         // front->next = NULL

    return OK;
}


/*!
 * @brief **链式队列销毁**
 * @param link_queue 链式队列(指针)
 * @return 执行结果
 * @note
 * 链式队列销毁
 * ----------
 * ----------
 *
 * ----------
 */
status_t LinkedQueueDestroy(linked_queue_t* link_queue) {
    while (link_queue->front) {
        link_queue->rear = link_queue->front->next;
        free(link_queue->front);

        link_queue->front = link_queue->rear;
    }

    return OK;
}


/*!
 * @brief **链式队列入队**
 * @param link_queue 链式队列(指针)
 * @param elem 入队元素
 * @return 执行结果
 * @note
 * 链式队列入队
 * ----------
 * ----------
 *
 * ----------
 * ###1 新结点内存分配###
 * &emsp; **if** 如果malloc失败 :\n
 * &emsp;&emsp; 返回NON_ALLOCATED\n
 * ###2 新节点结构体变量赋值###
 * ###3 rear指针处理###
 * - **I**&nbsp;&nbsp; rear->next指向新节点
 * - **II**&nbsp; rear指向新节点
 */
status_t LinkedQueueEnQueue(linked_queue_t* link_queue, QUEUE_ELEM elem) {
    // ----- 1 新结点内存分配 -----
    linked_queue_node_t* new_node = (linked_queue_node_t*)malloc(sizeof(linked_queue_node_t));
    if (!new_node) {    // if 如果malloc失败
        return NON_ALLOCATED;   // 返回NON_ALLOCATED
    }

    // ----- 2 新节点结构体变量赋值 -----
    new_node->data = elem;
    new_node->next = NULL;

    // ----- 3 rear指针处理 -----
    link_queue->rear->next = new_node;  // rear->next指向新节点
    link_queue->rear = new_node;        // rear指向新节点

    return OK;
}


/*!
 * @brief **链式队列出队**
 * @param linked_queue 顺序队列(指针)
 * @param elem 出队元素保存变量(指针)
 * @return 执行结果
 * @note
 * 链式队列出队
 * ----------
 * ----------
 *
 * ----------
 * ###1 空队判断###
 * &emsp; **if** front等于rear : \n
 * &emsp;&emsp; 空队, 返回NON_EXISTENT\n
 * ###2 出队###
 * - **I**&nbsp;&nbsp; 出队结点数据项赋值给*elem
 * - **II**&nbsp; front->next指向出队结点的next
 * - **III** 释放出队结点
 */
status_t LinkedQueueDeQueue(linked_queue_t* linked_queue, QUEUE_ELEM* elem) {
    // ----- 1 空队判断 -----
    if (linked_queue->front == linked_queue->rear) {    // if front等于rear
        return NON_EXISTENT;    // 空队, 返回NON_EXISTENT
    }

    // ----- 2 出队 -----
    linked_queue_node_t* dequeue_node = linked_queue->front->next;
    *elem = dequeue_node->data; // 出队结点数据项赋值给*elem

    linked_queue->front->next = dequeue_node->next; // front->next指向出队结点的next

    free(dequeue_node); // 释放出队结点
    dequeue_node = NULL;

    return OK;
}


/*!
 * @brief **链式队列长度**
 * @param linked_queue 链式队列
 * @return 长度
 * @note
 * 链式队列长度
 * ----------
 * ----------
 *
 * ----------
 */
int LinkedQueueLength(linked_queue_t linked_queue) {
    linked_queue_node_t* cur = linked_queue.front;
    int length = 0;

    while (cur != linked_queue.rear) {
        length++;
        cur = cur->next;
    }

    return length;
}


/*!
 * @brief **打印队列**
 * @param linked_queue 链式队列
 * 打印队列
 * -------
 * -------
 *
 * -------
 */
void LinkedQueuePrint(linked_queue_t* linked_queue) {
    printf("从队头向队尾打印元素(队头 ... 队尾): \n");

    linked_queue_node_t *cur = linked_queue->front->next;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }

    printf("\n");
}

