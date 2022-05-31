//
// Created by cyberdash@163.com on 2022/4/8.
//

#ifndef CYBER_DASH_GLIST_H
#define CYBER_DASH_GLIST_H


#include "sq_queue.h"


#define AtomType char

typedef enum {ATOM, LIST} ElemTag;

typedef struct GLNode {
    ElemTag   tag;              // 公共部分, 用于区分原子结点还是表结点
    union {
        AtomType        atom;   // 原子结点的值域
        struct GLNode   *head;     // 表结点的标头指针
    } info;
    struct GLNode       *next;    // 相当于线性链表的next, 指向下一个元素结点
}GLNode, *GList;


void CreateGenListByQueueRecursive(SqQueue* char_queue, GLNode** node);

void CreateGenListByStr(GLNode** node, char* str, int str_len);

Status GenListToString(GLNode* node, char* gen_list_string);

void SubGenListToStringRecursive(GList gList, SqQueue* char_queue);

int GListDepth(GList gList);

Status CopyGenList(GList* target_list, GList src_list);

#endif // CYBER_DASH_GLIST_H
