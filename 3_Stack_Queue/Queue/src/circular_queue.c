/*!
 * @file circular_queue.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 循环队列源文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */


#include <stdlib.h>
#include <stdio.h>
#include "circular_queue.h"


/*!
 * <h1>顺序队列初始化</h1>
 * @param circular_queue **顺序队列**(指针)
 * @return **执行结果**
 */
status_t CircularQueueInit(circular_queue_t* circular_queue) {
    /// ###1 顺序队列数组分配内存###
    /// &emsp; **if** 如果malloc失败 :\n
    /// &emsp;&emsp; 返回NON_ALLOCATED
    circular_queue->elements = (QUEUE_ELEM*)malloc(MAX_SIZE * sizeof(QUEUE_ELEM));
    if (!circular_queue->elements) {
        return NON_ALLOCATED;
    }

    /// ###2 队头队尾初始化###
    /// &emsp; front和rear都为0\n
    circular_queue->front = 0;
    circular_queue->rear = 0;

    return OK;
}


/*!
 * @brief <h1>顺序队列长度</h1>
 * @param circular_queue **顺序队列**
 * @return **长度**
 * @note
 */
int CircularQueueLength(circular_queue_t circular_queue) {
    /// &emsp; 长度等于(rear - front + MAX_SIZE) % MAX_SIZE\n
    return (circular_queue.rear - circular_queue.front + MAX_SIZE) % MAX_SIZE;
}


/*!
 * @brief <h1>顺序队列入队</h1>
 * @param circular_queue **顺序队列**(指针)
 * @param elem **入队元素**
 * @return **执行结果**
 * @note
 */
status_t CircularQueueEnQueue(circular_queue_t* circular_queue, QUEUE_ELEM elem) {

    /// ###1 判断队列是否满###
    /// &emsp; **if** 队列满 :\n
    /// &emsp;&emsp; 返回OVERFLOW\n
    if ((circular_queue->rear + 1) % MAX_SIZE == circular_queue->front) {
        return OVERFLOW;
    }

    /// ###2 元素elem插入到队尾###
    /// - **I**&nbsp;&nbsp; elements数组rear索引位置赋值
    /// - **II**&nbsp; rear调整数值
    circular_queue->elements[circular_queue->rear] = elem;
    circular_queue->rear = (circular_queue->rear + 1) % MAX_SIZE;

    return OK;
}


/*!
 * <h1>顺序队列出队</h1>
 * @param circular_queue **顺序队列**(指针)
 * @param elem **出队元素保存变量**(指针)
 * @return **执行结果**
 * @note
 */
status_t CircularQueueDeQueue(circular_queue_t* circular_queue, QUEUE_ELEM* elem) {
    /// ###1 空队判断###
    /// &emsp; **if** front等于rear : \n
    /// &emsp;&emsp; 空队, 返回NON_EXISTENT\n
    if (circular_queue->front == circular_queue->rear) {
        return ERROR;
    }

    /// ###2 出队###
    /// - **I**&nbsp;&nbsp; elements数组front索引位置元素赋给*elem
    /// - **II**&nbsp; front调整数值
    *elem = circular_queue->elements[circular_queue->front];
    circular_queue->front = (circular_queue->front + 1) % MAX_SIZE;

    return OK;
}


/*!
 * @brief <h1>打印顺序队列</h1>
 * @param circular_queue **顺序队列**(指针)
 * @note
 */
void CircularQueuePrint(circular_queue_t* circular_queue) {
    /// &emsp; 从队头front向队尾rear打印队列元素, 相邻元素以空格分隔\n
    printf("从队头向队尾打印元素(队头 ... 队尾):\n");

    int cur = circular_queue->front;
    while (cur < circular_queue->rear) {
        printf("%d ", circular_queue->elements[cur]);
        cur++;
    }

    printf("\n");
}