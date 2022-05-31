//
// Created by cyberdash@163.com on 2022/4/20.
//

#include "test.h"
#include "link_queue.h"


void TestSqEnQueue() {

}


void TestSqDeQueue() {

}


/*
typedef struct QNode {
    QElemType       data;
    struct QNode    *next;
} QNode, *QueuePtr;
typedef struct LinkQueue {
    QueuePtr    front;  // 队头指针
    QueuePtr    rear;   // 队尾指针
}LinkQueue;
 */
void TestLinkEnQueue() {
    LinkQueue linkQueue;
    Status status = LqInitQueue(&linkQueue);

    // Status LqEnQueue(LinkQueue *Q, QElemType e) {
    int elements[8] = { 3, 1, 4, 1, 5, 9, 2, 6};
    for (int i = 0; i < sizeof(elements) / sizeof(int); i++) {
        LqEnQueue(&linkQueue, elements[i]);
    }

    PrintLinkQueue(&linkQueue);
}


void TestLinkDeQueue() {

}
