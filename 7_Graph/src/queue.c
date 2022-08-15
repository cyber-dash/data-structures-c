/*!
 * @file queue.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 链式队列源文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


/*!
 * <h1>链式队列初始化</h1>
 * @param link_queue **链式队列**
 * @return **执行结果**
 * @note
 */
status_t LinkedQueueInit(linked_queue_t* link_queue) {
    // 构造一个空队列Q
    link_queue->rear = (linked_queue_node_t*)malloc(sizeof(linked_queue_node_t));
    if (!link_queue->rear) {
        return NON_ALLOCATED;
    }

    link_queue->front = link_queue->rear;
    link_queue->front->next = NULL;
    return OK;
}


/*!
 * <h1>链式队列入队</h1>
 * @param queue **链式队列**(指针)
 * @param vertex_index **图结点索引**
 * @return **执行结果**
 * @note
 */
status_t LinkedQueueEnQueue(linked_queue_t *queue, int vertex_index) {
    // 插入元素e为Q的新的队尾元素
    linked_queue_node_t* cur = (linked_queue_node_t*)malloc(sizeof(linked_queue_node_t));
    if (!cur) {
        return OVERFLOW;
    }

    cur->vertex_index = vertex_index;
    cur->next = NULL;

    queue->rear->next = cur;
    queue->rear = cur;

    return OK;
}


/*!
 *
 * @param queue
 * @param v
 * @return
 */
status_t LinkedQueueDeQueue(linked_queue_t* queue, int* v) {
    // 若队列不空, 则删除Q的队头元素, 用e返回其值, 并返回OK;
    // 否则返回ERROR
    if (queue->front == queue->rear) {
        return ERROR;
    }

    linked_queue_node_t* p = queue->front->next;
    *v = p->vertex_index;
    queue->front->next = p->next;

    if (queue->rear == p) {
        queue->rear = queue->front;
    }

    free(p);
    return OK;
}


/*!
 * <h1>链式队列是否为空</h1>
 * @param queue **链式队列**
 * @return 是/否
 * @note
 */
int LinkedQueueIsEmpty(linked_queue_t* queue) {
    /// **if** 头指针和为指针指向地址相同 : \n
    if (queue->front == queue->rear) {
        /// &emsp; 返回TRUE
        return TRUE;
    }

    /// 返回FALSE
    return FALSE;
}
