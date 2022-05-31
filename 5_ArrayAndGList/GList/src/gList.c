//
// Created by cyberdash@163.com on 2022/4/8.
//

#include "gList.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


Status InitListHeadNode(GLNode** node) {
    *node = (GLNode*)malloc(sizeof(GLNode));
    if (!(*node)) {
        return ERROR;
    }

    (*node)->tag = LIST;
    (*node)->info.head = NULL;
    (*node)->next = NULL;

    return OK;
}


Status InitAtomNode(GLNode** node, AtomType chr) {
    *node = (GLNode*)malloc(sizeof(GLNode));
    if (!(*node)) {
        return ERROR;
    }

    (*node)->tag = ATOM;
    (*node)->info.atom = chr;
    (*node)->next = NULL;

    return OK;
}


void CreateGenListByQueueRecursive(SqQueue* char_queue, GLNode** node) {

    QueueElem chr;
    if (GetLength(*char_queue) == 0) {
        return;
    }

    DeQueue(char_queue, &chr);

    if (chr == '(') {
        InitListHeadNode(node);
        CreateGenListByQueueRecursive(char_queue, &(*node)->info.head);
        CreateGenListByQueueRecursive(char_queue, node);
    } else if (isalpha(chr)) {
        InitAtomNode(node, chr);
        CreateGenListByQueueRecursive(char_queue, node);
    } else if (chr == ',') {
        CreateGenListByQueueRecursive(char_queue, &(*node)->next);
    } else if (chr == ')') {
        // 如果*node为NULL, 则为"()"形式, 否则为"(...)"形式
        if (*node) {
            (*node)->next = NULL;
        }
    }
}


void CreateGenListByStr(GList* gList, char* str, int str_len) {

    SqQueue char_queue;
    InitQueue(&char_queue);
    for (int i = 0; i < str_len; i++) {
        EnQueue(&char_queue, str[i]);
    }

    CreateGenListByQueueRecursive(&char_queue, gList);
}


Status GenListToString(GList gList, char* gen_list_string) {

    SqQueue char_queue;
    InitQueue(&char_queue);

    // char queue_str[200];
    memset(gen_list_string, 0, 200 * sizeof(char));

    SubGenListToStringRecursive(gList, &char_queue);

    ToString(&char_queue, gen_list_string);

    return OK;
}


void SubGenListToStringRecursive(GList gList, SqQueue* char_queue) {
    GLNode* cur_head = gList->info.head;

    EnQueue(char_queue, '(');

    while (cur_head) {
        if (cur_head->tag == LIST) {
            SubGenListToStringRecursive(cur_head, char_queue);
        } else if (cur_head->tag == ATOM) {
            EnQueue(char_queue, cur_head->info.atom);
        }

        if (cur_head->next != NULL) {
            EnQueue(char_queue, ',');
        }

        cur_head = cur_head->next;
    }

    EnQueue(char_queue, ')');
}


int GListDepth(GList gList) {
    if (!gList) {
        return 1;
    }

    if (gList->tag == ATOM) {
        return 0;
    }

    int max_sub_gen_list_depth = 0; // 子表最大深度, 初始化为0
    for (GList cur_gen_list = gList->info.head; cur_gen_list != NULL; cur_gen_list = cur_gen_list->next) {
        int cur_sub_gen_list_depth = GListDepth(cur_gen_list);
        if (max_sub_gen_list_depth < cur_sub_gen_list_depth) {
            max_sub_gen_list_depth = cur_sub_gen_list_depth;
        }
    }

    max_sub_gen_list_depth++;

    return max_sub_gen_list_depth;
}


Status CopyGenList(GList* target_list, GList src_list) {

    if (src_list == NULL) {
        *target_list = NULL;
        return OK;
    }

    *target_list = (GList)malloc(sizeof(GLNode));
    if (*target_list == NULL) {
        return ALLOC_UNINITIALIZED;
    }

    (*target_list)->tag = src_list->tag;

    if (src_list->tag == ATOM) {
        (*target_list)->info.atom = src_list->info.atom;
    } else {
        CopyGenList(&(*target_list)->info.head, src_list->info.head);
    }

    CopyGenList(&(*target_list)->next, src_list->next);

    return OK;
}
