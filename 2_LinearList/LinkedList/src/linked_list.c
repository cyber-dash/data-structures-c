/*!
 * @file linked_list.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 链表
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>


/*!
 * 创建链表
 * @param linked_list_head 链表头结点(指针)
 * @param elements
 * @param elem_cnt
 * @return
 */
Status LinkedListCreate(linked_node_t** linked_list_head, ELEM_TYPE* elements, int elem_cnt) {
    *linked_list_head = (linked_node_t*)malloc(sizeof(linked_node_t)); // 链表头结点分配内存
    if (!(*linked_list_head)) {
        return NON_ALLOCATED;
    }

    (*linked_list_head)->next = NULL;

    for (int i = elem_cnt - 1; i >= 0; i--) {
        linked_node_t* linked_node = (linked_node_t*)malloc(sizeof(linked_node_t)); // 新结点分配内存
        if (!linked_node) {
            return NON_ALLOCATED;
        }

        linked_node->data = elements[i];            // elements[i]赋给新结点数据项
        linked_node->next = (*linked_list_head)->next; // 新结点next赋值
        (*linked_list_head)->next = linked_node;       // linked_list_head->next指向新结点
    }

    return OK;
}


/*!
 * 获取位置pos的结点数据
 * @param linked_list_head 链表头结点(指针)
 * @param pos 位置
 * @param elem 保存结点数据项的变量(指针)
 * @return 是否成功
 */
Status LinkedListGetElem(linked_list_t linked_list_head, int pos, ELEM_TYPE* elem) {
    linked_node_t* cur_node = linked_list_head->next;
    int cur_pos = 1;

    while (cur_node && cur_pos < pos) {
        cur_node = cur_node->next;
        cur_pos++;
    }

    // 位置pos的结点不存在, 返回NON_EXISTENT
    if (!cur_node || cur_pos > pos) {
        return NON_EXISTENT;
    }

    *elem = cur_node->data; // 将位置pos的数据项赋给*elem

    return OK;
}


Status LinkedListInsert(linked_list_t linked_list_head, int pos, ELEM_TYPE elem) {
    linked_node_t* insert_node_predecessor = linked_list_head;    // 插入完成后, 插入结点的前一结点(指针), 初始化指向链表头结点
    int insert_pos_predecessor = 0; // 插入位置的前一位置, 初始化为0

    // 遍历到插入位置的前一位置
    while(!insert_node_predecessor || insert_pos_predecessor < pos - 1) {
        insert_node_predecessor = insert_node_predecessor->next;
        insert_pos_predecessor++;
    }

    // 如果插入位置不存在, 返回ERROR
    if (!insert_node_predecessor || insert_pos_predecessor > pos - 1) {
        return ERROR;
    }

    linked_node_t* insert_node = (linked_node_t*)malloc(sizeof(linked_node_t)); // 插入结点分配内存
    if (!insert_node) {
        return NON_ALLOCATED;
    }

    insert_node->data = elem;
    insert_node->next = insert_node_predecessor->next;
    insert_node_predecessor->next = insert_node;

    return OK;
}


/*!
 * 链表删除结点
 * @param linked_list_head 链表头结点(指针)
 * @param pos 位置
 * @param elem 被删除结点数据项的保存变量(指针)
 * @return 是否成功
 */
Status LinkedListDelete(linked_list_t linked_list_head, int pos, ELEM_TYPE* elem) {
    linked_node_t* delete_node_predecessor = linked_list_head;    // 待删除结点前一结点(指针), 初始化指向链表头结点
    int delete_pos_predecessor = 0; // 待删除结点前一结点的位置, 初始化为0

    // 遍历到待删除结点的前一结点
    while(!(delete_node_predecessor->next) || delete_pos_predecessor < pos - 1) {
        delete_node_predecessor = delete_node_predecessor->next;
        delete_pos_predecessor++;
    }

    // 位置pos的结点不存在, 返回NON_EXISTENT
    if (!(delete_node_predecessor->next) || delete_pos_predecessor > pos - 1) {
        return NON_EXISTENT;
    }

    linked_node_t* delete_node = delete_node_predecessor->next; // delete_node指向待删除结点
    delete_node_predecessor->next = delete_node->next;
    *elem = delete_node->data;

    free(delete_node);  // 释放结点
    delete_node = NULL; // 避免野指针

    return OK;
}


/*!
 * 合并两个有序链表
 * @param list_a_head a链表头结点(指针)
 * @param list_b_head b链表头结点(指针)
 * @param merged_list_head 合并链表头结点(二级指针)
 * @return 合并结果
 */
Status LinkedListMergeTwoSortedList(linked_list_t list_a_head, linked_list_t list_b_head, linked_list_t* merged_list_head) {

    linked_node_t* a_cur = list_a_head->next;
    linked_node_t* b_cur = list_b_head->next;

    *merged_list_head = list_a_head;
    linked_node_t* cur = list_a_head;

    while (a_cur && b_cur) {
        if (a_cur->data <= b_cur->data) {
            cur->next = a_cur;
            cur = a_cur;
            a_cur = a_cur->next;
        } else {
            cur->next = b_cur;
            cur = b_cur;
            b_cur = b_cur->next;
        }
    }

    if (a_cur) {
        cur->next = a_cur;
    }

    return OK;
}


void LinkedListPrint(linked_list_t linked_list_head) {
    for (linked_node_t* cur = linked_list_head->next; cur != NULL; cur = cur->next) {
        printf("%d ", cur->data);
    }

    printf("\n");
}
