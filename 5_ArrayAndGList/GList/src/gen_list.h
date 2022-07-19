/*!
 * @file gen_list.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  广义表
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_GENERALIZED_LIST_H
#define CYBER_DASH_GENERALIZED_LIST_H


#include "seq_queue.h"


#define ATOM_TYPE char

typedef enum { ATOM, LIST } ELEM_TAG;
typedef struct gen_list_node gen_list_node_t;
typedef gen_list_node_t* gen_list_t;
typedef union {
    ATOM_TYPE   atom;   // 原子结点的值域
    gen_list_node_t*    head;     // 表结点的标头指针
} gen_list_node_item_t;

struct gen_list_node {
    ELEM_TAG    tag;              // 公共部分, 用于区分原子结点还是表结点
    gen_list_node_item_t item;
    gen_list_node_t*    next;    // 相当于线性链表的next, 指向下一个元素结点
};


void GenListCreateByQueueRecursive(seq_queue_t* char_queue, gen_list_node_t** node);

void GenListCreateByStr(gen_list_node_t** gen_list, char* str, int str_len);

Status GenListToString(gen_list_node_t* gen_list, char* gen_list_str, int str_len_limit);

void GenListToStringRecursive(gen_list_t gList, seq_queue_t* char_queue);

int GenListDepthRecursive(gen_list_t gen_list);

Status CopyGenList(gen_list_t* target_list, gen_list_t src_list);

#endif // CYBER_DASH_GENERALIZED_LIST_H
