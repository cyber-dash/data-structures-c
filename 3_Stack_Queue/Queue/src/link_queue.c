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
 * 构造一个空队列
 * @param link_queue 链式队列(指针)
 * @return 执行结果
 */
Status LinkQueueInit(link_queue_t* link_queue) {
    link_queue->rear = (link_queue_node_t*)malloc(sizeof(link_queue_node_t));
    if (!link_queue->rear) {
        return NON_ALLOCATED;
    }

    link_queue->front = link_queue->rear;
    link_queue->front->next = NULL;

    return OK;
}


/*!
 *
 * @param link_queue
 * @return
 */
Status LinkQueueDestroy(link_queue_t* link_queue) {
    // 销毁队列Q
    while (link_queue->front) {
        link_queue->rear = link_queue->front->next;
        free(link_queue->front);

        link_queue->front = link_queue->rear;
    }

    return OK;
}


/*!
 *
 * @param link_queue
 * @param elem
 * @return
 */
Status LinkQueueEnQueue(link_queue_t* link_queue, QUEUE_ELEM elem) {
    // 插入元素e为Q的新的队尾元素
    link_queue_node_t* new_node = (link_queue_node_t*)malloc(sizeof(link_queue_node_t));
    if (!new_node) {
        return NON_ALLOCATED; // 存储分配失败
    }

    new_node->data = elem;
    new_node->next = NULL;

    link_queue->rear->next = new_node;
    link_queue->rear = new_node;

    return OK;
}


/*!
 *
 * @param link_queue
 * @param elem
 * @return
 */
Status LinkQueueDeQueue(link_queue_t* link_queue, QUEUE_ELEM* elem) {
    if (link_queue->front == link_queue->rear) {
        return NON_EXISTENT;
    }

    link_queue_node_t* dequeue_node = link_queue->front->next;
    *elem = dequeue_node->data;

    link_queue->front->next = dequeue_node->next;

    free(dequeue_node);
    dequeue_node = NULL;

    return OK;
}


/*!
 *
 * @param link_queue
 * @return
 */
int LinkQueueLength(link_queue_t link_queue) {
    // 返回Q的元素个数, 即为队列的长度
    link_queue_node_t* cur = link_queue.front;
    int length = 0;

    while (cur != link_queue.rear) {
        length++;
        cur = cur->next;
    }

    return length;
}


/*
Status ClearQueue(link_queue_t *Q) {
    // 将Q清为空队列

}


Status QueueEmpty(link_queue_t Q) {
    // 若队列Q为空队列, 则返回TRUE, 否则返回FALSE

}


Status GetHead(link_queue_t Q, QUEUE_ELEM *e) {
    // 若度列不空, 则用e返回Q的队头元素, 并返回OK;否则返回ERROR

}


// 从队头到队尾一次对队列Q中每个元素调用函数visit, 一旦visit失败, 则操作失败
Status QueueTraverse(link_queue_t Q, void (*visit)(link_queue_node_t qNode)) {

}
*/


/*!
 *
 * @param link_queue
 */
void LinkQueuePrint(link_queue_t* link_queue) {
    printf("从队头向队尾打印元素(队头 ... 队尾): \n");

    link_queue_node_t *cur = link_queue->front->next;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }

    printf("\n");
}

