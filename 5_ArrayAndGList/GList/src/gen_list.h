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


#define AtomType char

typedef enum { ATOM, LIST } ELEM_TAG;

typedef struct gen_list_node_t {
    ELEM_TAG   tag;              // 公共部分, 用于区分原子结点还是表结点
    union {
        AtomType        atom;   // 原子结点的值域
        struct GenListNode   *head;     // 表结点的标头指针
    } item;
    struct GenListNode       *next;    // 相当于线性链表的next, 指向下一个元素结点
}gen_list_node_t, *gen_list_t;


void CreateGenListByQueueRecursive(seq_queue_t* char_queue, gen_list_node_t** node);

void CreateGenListByStr(gen_list_node_t** node, char* str, int str_len);

Status GenListToString(gen_list_node_t* node, char* gen_list_string);

void SubGenListToStringRecursive(gen_list_t gList, seq_queue_t* char_queue);

int GListDepth(gen_list_t gList);

Status CopyGenList(gen_list_t* target_list, gen_list_t src_list);

#endif // CYBER_DASH_GENERALIZED_LIST_H
