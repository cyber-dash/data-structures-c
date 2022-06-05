//
// Created by cyberdash@163.com(抖音: cyberdash_yuan) on 2022/6/4.
//

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

Status LinkedListMerge(linked_list_t linked_list_a, linked_list_t linked_list_b, linked_list_t merged_list);

void LinkedListPrint(linked_list_t linked_list_head);


#endif // CYBER_DASH_LINKED_LIST_H
