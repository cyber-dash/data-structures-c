/*!
 * @file queue.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 队列源文件
 * @version 1.0.0
 * @date 2022-07-15
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */


#include "queue.h"
#include "stdlib.h"


/*!
 * @brief <h1>顺序队列初始化</h1>
 * @param seq_queue **顺序队列**(指针)
 * @return **执行结果**
 * @note
 */
Status SeqQueueInit(seq_queue_t* seq_queue) {
    /// ###1 顺序队列数组分配内存###
    /// &emsp; **if** 如果malloc失败 :\n
    /// &emsp;&emsp; 返回NON_ALLOCATED
    seq_queue->elements = (QUEUE_ELEM*)malloc(MAX_SIZE * sizeof(QUEUE_ELEM));
    if (!seq_queue->elements) {
        return NON_ALLOCATED;
    }

    /// ###2 队头队尾初始化###
    /// &emsp; front和rear都为0\n
    seq_queue->front = 0;
    seq_queue->rear = 0;

    return OK;
}


/*!
 * @brief <h1>顺序队列长度</h1>
 * @param seq_queue **顺序队列**
 * @return **长度**
 * @note
 */
int SeqQueueLength(seq_queue_t seq_queue) {
    /// &emsp; 长度等于(rear - front + MAX_SIZE) % MAX_SIZE\n
    return (seq_queue.rear - seq_queue.front + MAX_SIZE) % MAX_SIZE;
}


/*!
 * @brief <h1>顺序队列入队</h1>
 * @param seq_queue **顺序队列**(指针)
 * @param elem **入队元素**
 * @return **执行结果**
 * @note
 */
Status SeqQueueEnQueue(seq_queue_t* seq_queue, QUEUE_ELEM elem) {

    /// ###1 判断队列是否满###
    /// &emsp; **if** 队列满 :\n
    /// &emsp;&emsp; 返回OVERFLOW\n
    if ((seq_queue->rear + 1) % MAX_SIZE == seq_queue->front) {
        return OVERFLOW;
    }

    /// ###2 元素elem插入到队尾###
    /// - **I**&nbsp;&nbsp; elements数组rear索引位置赋值
    /// - **II**&nbsp; rear调整数值
    seq_queue->elements[seq_queue->rear] = elem;
    seq_queue->rear = (seq_queue->rear + 1) % MAX_SIZE;

    return OK;
}


/*!
 * <h1>顺序队列出队</h1>
 * @param seq_queue **顺序队列**(指针)
 * @param elem **出队元素保存变量**(指针)
 * @return **执行结果**
 * @note
 */
Status SeqQueueDeQueue(seq_queue_t* seq_queue, QUEUE_ELEM* elem) {
    /// ###1 空队判断###
    /// &emsp; **if** front等于rear : \n
    /// &emsp;&emsp; 空队, 返回NON_EXISTENT\n
    if (seq_queue->front == seq_queue->rear) {
        return NON_EXISTENT;
    }

    /// ###2 出队###
    /// - **I**&nbsp;&nbsp; elements数组front索引位置元素赋给*elem
    /// - **II**&nbsp; front调整数值
    *elem = seq_queue->elements[seq_queue->front];
    seq_queue->front = (seq_queue->front + 1) % MAX_SIZE;

    return OK;
}
