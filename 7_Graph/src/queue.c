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
 * @brief **链式队列初始化**
 * @param link_queue 链式队列
 * @return 执行结果
 * @note
 * 链式队列初始化
 * ------------
 * ------------
 *
 * ------------
 * - 链式队列rear指向的结点分配内存 \n
 * &emsp; **if** 内存分配失败 : \n
 * &emsp;&emsp; 返回NON_ALLOCATED \n
 * - 链式队列front处理 \n
 * &emsp; front指向和rear相同 \n
 * &emsp; front->next设为NULL \n
 */
status_t LinkedQueueInit(linked_queue_t* link_queue) {
    // ----- 链式队列rear指向的结点分配内存 -----
    link_queue->rear = (linked_queue_node_t*)malloc(sizeof(linked_queue_node_t));
    if (!link_queue->rear) {    // if 内存分配失败
        return NON_ALLOCATED;       // 返回NON_ALLOCATED
    }

    // ----- 链式队列front处理 -----
    link_queue->front = link_queue->rear;   // front指向和rear相同
    link_queue->front->next = NULL;         // front->next设为NULL

    return OK;
}


/*!
 * @brief **链式队列入队**
 * @param queue 链式队列(指针)
 * @param vertex_index 图结点索引
 * @return 执行结果
 * @note
 * 链式队列入队
 * ----------
 * ----------
 *
 * ----------
 * - 入队结点分配内存 \n
 * &emsp; **if** 内存分配失败 : \n
 * &emsp;&emsp; 返回NON_ALLOCATED \n
 * - 入队结点成员变量赋值
 * &emsp; vertex_index设为参数结点索引 \n
 * &emsp; next设为NULL \n
 * - 入队结点插入到队尾
 * &emsp; rear->next指向入队结点(插入队尾) \n
 * &emsp; rear指向入队结点(成为新队尾) \n
 */
status_t LinkedQueueEnQueue(linked_queue_t *queue, int vertex_index) {
    // ----- 入队结点分配内存 -----
    linked_queue_node_t* enqueue_node = (linked_queue_node_t*)malloc(sizeof(linked_queue_node_t));
    if (!enqueue_node) {        // if 内存分配失败
        return NON_ALLOCATED;       // 返回NON_ALLOCATED
    }

    // ----- 入队结点成员变量赋值 -----
    enqueue_node->vertex_index = vertex_index;  // vertex_index设为参数结点索引
    enqueue_node->next = NULL;                  // next设为NULL

    // ----- 入队结点插入到队尾 -----
    queue->rear->next = enqueue_node;   // rear->next指向入队结点(插入队尾)
    queue->rear = enqueue_node;         // rear指向入队结点(成为新队尾)

    return OK;
}


/*!
 * @brief **链式队列出队**
 * @param linked_queue 链式队列
 * @param vertex_index 出队结点索引值保存变量
 * @return 执行结果
 * @note
 * 链式队列出队
 * ----------
 * ----------
 *
 * ----------
 *
 * 若队列不空, 则删除Q的队头元素, 用e返回其值, 并返回OK; \n
 * 否则返回ERROR \n
 *
 * ----------
 * - 空队处理 \n
 * &emsp; **if** front和rear指向相同(空队): \n
 * &emsp;&emsp; 返回NON_EXISTENT \n
 * - 队头出队 \n
 * &emsp; dequeue_node指针指向队头, 将队头的vertex_index赋给参数vertex_index \n
 * &emsp; front->next指向dequeue_node->next \n
 * - 队列内只有1个元素的边界条件处理 \n
 * &emsp; **if** 队尾出队 : \n
 * &emsp;&emsp; rear值设为front值 \n
 * - free出队结点 \n
 */
status_t LinkedQueueDeQueue(linked_queue_t* linked_queue, int* vertex_index) {

    // ----- 空队处理 -----
    if (linked_queue->front == linked_queue->rear) { // if front和rear指向相同(空队), 返回NON_EXISTENT
        return NON_EXISTENT;
    }

    // ----- 队头出队 -----
    linked_queue_node_t* dequeue_node = linked_queue->front->next;  // dequeue_node指针指向队头
    *vertex_index = dequeue_node->vertex_index;                     // 将队头的vertex_index赋给参数vertex_index

    linked_queue->front->next = dequeue_node->next;                 // front->next指向dequeue_node->next

    // ----- 队列内只有1个元素的边界条件处理 -----
    if (linked_queue->rear == dequeue_node) {   // if 队尾出队
        linked_queue->rear = linked_queue->front;   // rear值设为front值
    }

    // ----- free出队结点 -----
    free(dequeue_node);

    return OK;
}


/*!
 * @brief **链式队列是否为空**
 * @param linked_queue 链式队列
 * @return 是/否
 * @note
 * 链式队列是否为空
 * --------------
 * --------------
 *
 * --------------
 * **if** 头指针和为指针指向地址相同 : \n
 * &emsp; 返回TRUE
 */
int LinkedQueueIsEmpty(linked_queue_t* linked_queue) {
    if (linked_queue->front == linked_queue->rear) {  // if 头指针和为指针指向地址相同
        return TRUE;    // 返回TRUE
    }

    return FALSE;   // 返回FALSE
}
