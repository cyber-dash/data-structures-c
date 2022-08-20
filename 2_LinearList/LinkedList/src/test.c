/*!
 * @file test.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 链表测试源文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdio.h>
#include "test.h"


/*!
 * @brief 测试链表创建
 * @note
 */
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


/*!
 * @brief 测试链表获取结点数据
 */
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


void TestLinkedListMerge() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                      测试有序链表的合并                      |\n");

    ELEM_TYPE elements1[4] = { 2, 4, 6, 8 };
    ELEM_TYPE elements2[4] = { 1, 3, 5, 7 };

    linked_node_t* linked_list_head1 = NULL;
    linked_node_t* linked_list_head2 = NULL;
    linked_node_t* merged_linked_list_head = NULL;

    printf("创建链表1:\n");
    LinkedListCreate(&linked_list_head1, elements1, sizeof(elements1) / sizeof(ELEM_TYPE));
    LinkedListPrint(linked_list_head1);

    printf("创建链表2:\n");
    LinkedListCreate(&linked_list_head2, elements2, sizeof(elements1) / sizeof(ELEM_TYPE));
    LinkedListPrint(linked_list_head2);

    printf("合并链表:\n");
    LinkedListMergeTwoSortedList(linked_list_head1, linked_list_head2, &merged_linked_list_head);
    LinkedListPrint(merged_linked_list_head);

    printf("\n-------------------------------------------------------------\n\n");
}
