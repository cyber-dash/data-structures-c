//
// Created by svenlee on 2022/9/1.
//

#ifndef CYBER_DASH_STATIC_LINKED_LIST_H
#define CYBER_DASH_STATIC_LINKED_LIST_H


#include "common.h"


#define STATIC_LINKED_LIST_MAX_SIZE 1000    //!< 静态链表的最大长度

typedef struct {
    ELEM_TYPE data;
    int link;
} component;

typedef component static_linked_list_t[STATIC_LINKED_LIST_MAX_SIZE];


// 静态链表查找, todo
int StaticLinkedListLocate(static_linked_list_t static_linked_list, ELEM_TYPE elem);


#endif // CYBER_DASH_STATIC_LINKED_LIST_H
