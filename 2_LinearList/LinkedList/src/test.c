//
// Created by cyberdash@163.com on 2022/6/4.
//

#include <stdio.h>
#include "test.h"


void TestLinkedListCreate() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                       测试链表的创建                        |\n");

    ELEM_TYPE arr[6] = { 1, 4, 2, 8, 5, 7 };    // 数据项数组
    linked_node_t* linked_list_head = NULL;     // 链表头结点linked_list_head初始化为NULL

    // 调用LinkedListCreate创建链表
    LinkedListCreate(&linked_list_head, arr, sizeof(arr)/ sizeof(ELEM_TYPE));

    // 打印链表
    LinkedListPrint(linked_list_head);

    printf("\n-------------------------------------------------------------\n\n");
}
