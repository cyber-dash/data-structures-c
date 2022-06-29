//
// Created by cyberdash@163.com on 2022/4/8.
//

#include "gen_list.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


Status InitListHeadNode(gen_list_node_t** node) {
    *node = (gen_list_node_t*)malloc(sizeof(gen_list_node_t));
    if (!(*node)) {
        return ERROR;
    }

    (*node)->tag = LIST;
    (*node)->item.head = NULL;
    (*node)->next = NULL;

    return OK;
}


Status InitAtomNode(gen_list_node_t** node, AtomType chr) {
    *node = (gen_list_node_t*)malloc(sizeof(gen_list_node_t));
    if (!(*node)) {
        return ERROR;
    }

    (*node)->tag = ATOM;
    (*node)->item.atom = chr;
    (*node)->next = NULL;

    return OK;
}


void CreateGenListByQueueRecursive(seq_queue_t* char_queue, gen_list_node_t** node) {

    QUEUE_ELEM chr;
    if (GetLength(*char_queue) == 0) {
        return;
    }

    DeQueue(char_queue, &chr);

    if (chr == '(') {
        InitListHeadNode(node);
        CreateGenListByQueueRecursive(char_queue, &(*node)->item.head);
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


void CreateGenListByStr(gen_list_t* gList, char* str, int str_len) {

    seq_queue_t char_queue;
    InitQueue(&char_queue);
    for (int i = 0; i < str_len; i++) {
        EnQueue(&char_queue, str[i]);
    }

    CreateGenListByQueueRecursive(&char_queue, gList);
}


Status GenListToString(gen_list_t gList, char* gen_list_string) {

    seq_queue_t char_queue;
    InitQueue(&char_queue);

    // char queue_str[200];
    memset(gen_list_string, 0, 200 * sizeof(char));

    SubGenListToStringRecursive(gList, &char_queue);

    ToString(&char_queue, gen_list_string);

    return OK;
}


void SubGenListToStringRecursive(gen_list_t gList, seq_queue_t* char_queue) {
    gen_list_node_t* cur_head = gList->item.head;

    EnQueue(char_queue, '(');

    while (cur_head) {
        if (cur_head->tag == LIST) {
            SubGenListToStringRecursive(cur_head, char_queue);
        } else if (cur_head->tag == ATOM) {
            EnQueue(char_queue, cur_head->item.atom);
        }

        if (cur_head->next != NULL) {
            EnQueue(char_queue, ',');
        }

        cur_head = cur_head->next;
    }

    EnQueue(char_queue, ')');
}


int GListDepth(gen_list_t gList) {
    if (!gList) {
        return 1;
    }

    if (gList->tag == ATOM) {
        return 0;
    }

    int max_sub_gen_list_depth = 0; // 子表最大深度, 初始化为0
    for (gen_list_t cur_gen_list = gList->item.head; cur_gen_list != NULL; cur_gen_list = cur_gen_list->next) {
        int cur_sub_gen_list_depth = GListDepth(cur_gen_list);
        if (max_sub_gen_list_depth < cur_sub_gen_list_depth) {
            max_sub_gen_list_depth = cur_sub_gen_list_depth;
        }
    }

    max_sub_gen_list_depth++;

    return max_sub_gen_list_depth;
}


Status CopyGenList(gen_list_t* target_list, gen_list_t src_list) {

    if (src_list == NULL) {
        *target_list = NULL;
        return OK;
    }

    *target_list = (gen_list_t)malloc(sizeof(gen_list_node_t));
    if (*target_list == NULL) {
        return ALLOC_UNINITIALIZED;
    }

    (*target_list)->tag = src_list->tag;

    if (src_list->tag == ATOM) {
        (*target_list)->item.atom = src_list->item.atom;
    } else {
        CopyGenList(&(*target_list)->item.head, src_list->item.head);
    }

    CopyGenList(&(*target_list)->next, src_list->next);

    return OK;
}
