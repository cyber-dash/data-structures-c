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

    printf("创建链表: ");

    // 调用LinkedListCreate创建链表
    LinkedListCreate(&linked_list_head, arr, sizeof(arr)/ sizeof(ELEM_TYPE));

    // 打印链表
    LinkedListPrint(linked_list_head);

    printf("\n-------------------------------------------------------------\n\n");
}


void TestLinkedListGetElem() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                      测试链表的获取元素                      |\n");

    ELEM_TYPE arr[6] = { 1, 4, 2, 8, 5, 7 };    // 数据项数组
    linked_node_t* linked_list_head = NULL;     // 链表头结点linked_list_head初始化为NULL

    printf("创建链表: ");

    // 调用LinkedListCreate创建链表
    LinkedListCreate(&linked_list_head, arr, sizeof(arr) / sizeof(ELEM_TYPE));

    // 打印链表
    LinkedListPrint(linked_list_head);

    int pos = 3;
    ELEM_TYPE data;
    LinkedListGetElem(linked_list_head, pos, &data);

    printf("位置%d的结点, 数据项: %d\n", pos, data);

    printf("\n-------------------------------------------------------------\n\n");
}


void TestLinkedListDelete() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                      测试链表的删除结点                      |\n");

    ELEM_TYPE arr[6] = { 1, 4, 2, 8, 5, 7 };    // 数据项数组
    linked_node_t* linked_list_head = NULL;     // 链表头结点linked_list_head初始化为NULL

    // 调用LinkedListCreate创建链表
    printf("创建链表: ");
    LinkedListCreate(&linked_list_head, arr, sizeof(arr) / sizeof(ELEM_TYPE));

    // 打印链表
    LinkedListPrint(linked_list_head);

    int delete_pos = 4;             // 删除结点位置
    ELEM_TYPE delete_node_elem = 0; // 被删除结点数据项的保存变量

    printf("\n删除位置%d的结点(从1开始计数)\n\n", delete_pos);
    LinkedListDelete(linked_list_head, delete_pos, &delete_node_elem);

    // 打印链表
    printf("删除结点后的链表: ");
    LinkedListPrint(linked_list_head);

    printf("\n-------------------------------------------------------------\n\n");
}


void TestLinkedListInsert() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                      测试链表的插入结点                      |\n");

    ELEM_TYPE arr[6] = { 1, 4, 2, 8, 5, 7 };    // 数据项数组
    linked_node_t* linked_list_head = NULL;     // 链表头结点linked_list_head初始化为NULL

    // 调用LinkedListCreate创建链表
    printf("创建链表: ");
    LinkedListCreate(&linked_list_head, arr, sizeof(arr) / sizeof(ELEM_TYPE));

    // 打印链表
    LinkedListPrint(linked_list_head);

    // 插入新元素
    LinkedListInsert(linked_list_head, 2, 9);
    LinkedListInsert(linked_list_head, 2, 10);
    LinkedListInsert(linked_list_head, 2, 11);

    // 打印链表
    printf("插入3个新结点后的链表: ");
    LinkedListPrint(linked_list_head);

    printf("\n-------------------------------------------------------------\n\n");
}
