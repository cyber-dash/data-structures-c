//
// Created by cyberdash@163.com(抖音: cyberdash_yuan) on 2022/6/4.
//

#include "linked_list.h"
#include <stdlib.h>


/*!
 * 创建链表
 * @param linked_list_head 链表头节点(指针)
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


Status LinkedListGetElem(linked_list_t linked_list, ELEM_TYPE* elem) {

    return OK;
}


Status LinkedListDeleteElem(linked_list_t linked_list, int pos, ELEM_TYPE* elem) {

    return OK;
}


Status LinkedListMerge(linked_list_t linked_list_a, linked_list_t linked_list_b, linked_list_t merged_list) {

    return OK;
}


void LinkedListPrint(linked_list_t linked_list_head) {
    for (linked_node_t* cur = linked_list_head->next; cur != NULL; cur = cur->next) {
        printf("%d ", cur->data);
    }

    printf("\n");
}
