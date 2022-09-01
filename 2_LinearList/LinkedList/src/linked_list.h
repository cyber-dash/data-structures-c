/*!
 * @file linked_list.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 单链表头文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_LINKED_LIST_H
#define CYBER_DASH_LINKED_LIST_H


#include "common.h"


/*! @brief 链表结点 */
typedef struct linked_node {
    ELEM_TYPE               data;   //!< 数据项
    struct linked_node*   next;   //!< 下一结点
} linked_node_t;

typedef linked_node_t* linked_list_t;   //!< 链表


status_t LinkedListCreate(linked_node_t** linked_list_head, ELEM_TYPE* elements, int elem_count);

status_t LinkedListGetElem(linked_node_t* linked_list_head, int pos, ELEM_TYPE* elem);

status_t LinkedListInsert(linked_node_t* linked_list_head, int pos, ELEM_TYPE elem);

status_t LinkedListDelete(linked_node_t* linked_list_head, int pos, ELEM_TYPE* elem);

status_t LinkedListMergeTwoSortedList(linked_node_t* list_a_head,
                                      linked_node_t* list_b_head,
                                      linked_node_t** merged_list_head);

void LinkedListPrint(linked_node_t* linked_list_head);


#endif // CYBER_DASH_LINKED_LIST_H
