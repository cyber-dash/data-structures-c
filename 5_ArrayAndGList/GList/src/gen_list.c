/*!
 * @file gen_list.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  广义表
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "gen_list.h"


/*!
 * @brief <h1>广义表子表头结点初始化</h1>
 * @param node **结点**(广义表结点二级指针)
 * @return 执行结果
 * @note
 */
Status GenListInitListHeadNode(gen_list_node_t** node) {
    /// ###1 结点分配内存###
    /// &emsp; **if** 如果malloc失败 :\n
    /// &emsp;&emsp; 返回NON_ALLOCATED\n
    *node = (gen_list_node_t*)malloc(sizeof(gen_list_node_t));
    if (!(*node)) {
        return ERROR;
    }

    /// ###2 字表头结点元素赋值###
    /// - **I**&nbsp;&nbsp; tag为LIST类型\n
    /// - **II**&nbsp; item.head为NULL(初始化时为空表)\n
    /// - **III** next为NULL\n
    (*node)->tag = LIST;
    (*node)->item.head = NULL;
    (*node)->next = NULL;

    return OK;
}


/*!
 * <h1>广义表原子结点初始化</h1>
 * @param node **结点**(指针)
 * @param chr **原子结点字符**
 * @return 执行结果
 * @note
 */
Status GenListInitAtomNode(gen_list_node_t** node, ATOM_TYPE chr) {
    /// ###1 结点分配内存###
    /// &emsp; **if** 如果malloc失败 :\n
    /// &emsp;&emsp; 返回NON_ALLOCATED\n
    *node = (gen_list_node_t*)malloc(sizeof(gen_list_node_t));
    if (!(*node)) {
        return ERROR;
    }

    /// ###2 原子结点元素赋值###
    /// - **I**&nbsp;&nbsp; tag为ATOM类型\n
    /// - **II**&nbsp; item.atom为char(原子结点名)\n
    /// - **III** next为NULL\n
    (*node)->tag = ATOM;
    (*node)->item.atom = chr;
    (*node)->next = NULL;

    return OK;
}


/*!
 * <h1>广义表使用队列建表(递归)</h1>
 * @param char_queue **字符队列**(指针)
 * @param node **结点**(广义表结点二级指针)
 * @note
 */
void GenListCreateByQueueRecursive(seq_queue_t* char_queue, gen_list_node_t** node) {

    /// ###1 空队判断###
    /// &emsp; **if** 队列为空 :\n
    /// &emsp;&emsp; 返回, **递归结束**\n
    if (SeqQueueGetLength(*char_queue) == 0) {
        return;
    }

    /// ###2 出队, 字符值赋给chr###
    QUEUE_ELEM chr;
    SeqQueueDeQueue(char_queue, &chr);

    /// ###3 各类型chr分别处理###
    /// - **I**&nbsp;&nbsp; chr为'('\n
    ///  + 对node构造子表头结点\n
    ///  + 对&(*node)->item.head执行递归\n
    ///  + 对node执行递归\n
    /// - **II**&nbsp; chr为小写字母(原子结点名称)\n
    ///  + 对node构造原子结点\n
    ///  + 对node执行递归\n
    /// - **III** chr为','\n
    ///  + 对&(*node)->next执行递归\n
    /// - **IV**&nbsp; chr为')'\n
    /// &emsp;&emsp;&emsp;&emsp; **if** *node不为NULL\n
    /// &emsp;&emsp;&emsp;&emsp;&emsp; (*node)->next设置为NULL\n
    /// &emsp;&emsp;&emsp;&emsp; (如果*node为NULL, 则表示当前子表为空表, 字符串为"()")\n
    if (chr == '(') {
        GenListInitListHeadNode(node);
        GenListCreateByQueueRecursive(char_queue, &(*node)->item.head);
        GenListCreateByQueueRecursive(char_queue, node);
    } else if (isalpha(chr)) {
        GenListInitAtomNode(node, chr);
        GenListCreateByQueueRecursive(char_queue, node);
    } else if (chr == ',') {
        GenListCreateByQueueRecursive(char_queue, &(*node)->next);
    } else if (chr == ')') {
        if (*node) {
            (*node)->next = NULL;
        }
    }
}


/*!
 * @brief <h1>广义表使用字符串建表</h1>
 * @param gen_list **广义表**(指针)
 * @param str **字符串**
 * @param str_len **字符串长度**
 * @note
 */
void GenListCreateByStr(gen_list_t* gen_list, char* str, int str_len) {

    /// ###1 初始化队列###
    seq_queue_t char_queue;
    SeqQueueInit(&char_queue);

    /// ###2 字符串的每个字符入队###
    for (int i = 0; i < str_len; i++) {
        SeqQueueEnQueue(&char_queue, str[i]);
    }

    /// ###3 调用GenListCreateByQueueRecursive建表###
    GenListCreateByQueueRecursive(&char_queue, gen_list);
}


/*!
 * @brief <h1>广义表转换成字符串</h1>
 * @param gen_list **广义表**(指针)
 * @param gen_list_str **广义表字符串**(用于转换)
 * @param str_len_limit **字符串长度限制**
 * @return **执行结果**
 */
Status GenListToString(gen_list_t gen_list, char* gen_list_str, int str_len_limit) {

    /// ###1 初始化队列和字符串###
    /// - **I**&nbsp;&nbsp; 初始化字符队列
    seq_queue_t char_queue;
    SeqQueueInit(&char_queue);

    /// - **II**&nbsp; 初始化字符串
    memset(gen_list_str, 0, str_len_limit * sizeof(char));

    /// ###2 调用GenListToStringRecursive, 生成字符串###
    GenListToStringRecursive(gen_list, &char_queue);

    /// ###3 将字符队列转换成
    SeqQueueToString(&char_queue, gen_list_str, str_len_limit);

    return OK;
}


// todo: 应该加个str_len限制, 防止溢出
void GenListToStringRecursive(gen_list_t gList, seq_queue_t* char_queue) {
    gen_list_node_t* cur_head = gList->item.head;

    SeqQueueEnQueue(char_queue, '(');

    while (cur_head) {
        if (cur_head->tag == LIST) {
            GenListToStringRecursive(cur_head, char_queue);
        } else if (cur_head->tag == ATOM) {
            SeqQueueEnQueue(char_queue, cur_head->item.atom);
        }

        if (cur_head->next != NULL) {
            SeqQueueEnQueue(char_queue, ',');
        }

        cur_head = cur_head->next;
    }

    SeqQueueEnQueue(char_queue, ')');
}


int GenListDepthRecursive(gen_list_t gen_list) {
    if (!gen_list) {
        return 1;
    }

    if (gen_list->tag == ATOM) {
        return 0;
    }

    int max_sub_gen_list_depth = 0; // 子表最大深度, 初始化为0
    for (gen_list_t cur_gen_list = gen_list->item.head; cur_gen_list != NULL; cur_gen_list = cur_gen_list->next) {
        int cur_sub_gen_list_depth = GenListDepthRecursive(cur_gen_list);
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
        return NON_ALLOCATED;
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
