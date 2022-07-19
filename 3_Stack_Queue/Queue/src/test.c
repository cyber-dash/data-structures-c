/*!
 * @file test.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  队列 测试用例
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "test.h"
#include <stdio.h>


void TestSeqQueueEnQueueAndDeQueue() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                Test SeqQueue EnQueue/DeQueue                \n");
    printf("                      测试顺序队列入队/出队                     \n\n\n");

    seq_queue_t seq_queue;
    Status status = SeqQueueInit(&seq_queue);

    QUEUE_ELEM elements[8] = { 3, 1, 4, 1, 5, 9, 2, 6 };
    for (int i = 0; i < sizeof(elements) / sizeof(int); i++) {
        printf("入队: %d\n", elements[i]);
        SeqQueueEnQueue(&seq_queue, elements[i]);
    }

    SeqQueuePrint(&seq_queue);

    printf("\n出队5次后:\n\n");

    QUEUE_ELEM top_elem;
    for (int i = 0; i < 5; i++) {
        SeqQueueDeQueue(&seq_queue, &top_elem);
    }

    SeqQueuePrint(&seq_queue);

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}


void TestSeqQueueDeQueue() {

}


void TestLinkQueueEnQueueAndDeQueue() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                Test linked_queue_t EnQueue/DeQueue               \n");
    printf("                      测试链式队列入队/出队                     \n\n\n");

    linked_queue_t link_queue;
    Status status = LinkQueueInit(&link_queue);

    QUEUE_ELEM elements[8] = { 3, 1, 4, 1, 5, 9, 2, 6 };
    for (int i = 0; i < sizeof(elements) / sizeof(int); i++) {
        printf("入队: %d\n", elements[i]);
        LinkQueueEnQueue(&link_queue, elements[i]);
    }

    LinkQueuePrint(&link_queue);

    printf("\n出队5次后:\n\n");

    QUEUE_ELEM top_elem;
    for (int i = 0; i < 8; i++) {
        LinkQueueDeQueue(&link_queue, &top_elem);
    }

    LinkQueuePrint(&link_queue);

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}


void TestLinkDeQueue() {

}
