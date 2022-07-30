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

#define ELEM_TYPE   int

typedef enum {
    OK,             //!< 成功/正确
    NON_ALLOCATED,  //!< 内存分配失败
    NON_EXISTENT,   //!< 不存在
    ERROR           //!< 错误
} Status;

typedef struct linked_node_t {
    ELEM_TYPE               data;   //!< 数据项
    struct linked_node_t*   next;   //!< 下一结点
} linked_node_t;

typedef linked_node_t* linked_list_t;


Status LinkedListCreate(linked_node_t** linked_list_head, ELEM_TYPE* elements, int elem_cnt);

Status LinkedListGetElem(linked_list_t linked_list_head, int pos, ELEM_TYPE* elem);

Status LinkedListInsert(linked_list_t linked_list_head, int pos, ELEM_TYPE elem);

Status LinkedListDelete(linked_list_t linked_list_head, int pos, ELEM_TYPE* elem);

Status LinkedListMergeTwoSortedList(linked_list_t list_a_head, linked_list_t list_b_head, linked_list_t* merged_list_head);

void LinkedListPrint(linked_list_t linked_list_head);


#endif // CYBER_DASH_LINKED_LIST_H
