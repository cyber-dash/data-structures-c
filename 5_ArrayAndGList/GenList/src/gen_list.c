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
 * @brief **广义表子表头结点初始化**
 * @param node 结点(二级指针)
 * @return 执行结果
 * @note
 * 广义表子表头结点初始化
 * -------------------
 * -------------------
 *
 * -------------------
 * ###1 结点分配内存###
 * &emsp; **if** 如果malloc失败 :\n
 * &emsp;&emsp; 返回NON_ALLOCATED\n
 * ###2 字表头结点元素赋值###
 * - **I**&nbsp;&nbsp; tag为LIST类型\n
 * - **II**&nbsp; item.head为NULL(初始化时为空表)\n
 * - **III** next为NULL\n
 */
status_t GenListInitListHeadNode(gen_list_node_t** node) {
    // ----- 1 结点分配内存 -----
    *node = (gen_list_node_t*)malloc(sizeof(gen_list_node_t));
    if (!(*node)) { // if 如果malloc失败
        return ERROR;   // 返回NON_ALLOCATED
    }

    // ----- 2 字表头结点元素赋值 -----
    (*node)->tag = LIST_HEAD;   // tag为LIST_HEAD类型
    (*node)->item.head = NULL;  // item.head为NULL(初始化时为空表)
    (*node)->next = NULL;       // next为NULL

    return OK;
}


/*!
 * @brief **广义表原子结点初始化**
 * @param node 结点(指针)
 * @param chr 原子结点字符
 * @return 执行结果
 * @note
 * 广义表原子结点初始化
 * -----------------
 * -----------------
 *
 * -----------------
 * ###1 结点分配内存###
 * &emsp; **if** 如果malloc失败 : \n
 * &emsp;&emsp; 返回NON_ALLOCATED \n
 * ###2 原子结点元素赋值###
 * - **I**&nbsp;&nbsp; tag为ATOM类型\n
 * - **II**&nbsp; item.atom为char(原子结点名)\n
 * - **III** next为NULL\n
 */
status_t GenListInitAtomNode(gen_list_node_t** node, ATOM_TYPE chr) {
    // ----- 1 结点分配内存 -----
    *node = (gen_list_node_t*)malloc(sizeof(gen_list_node_t));
    if (!(*node)) { // if 如果malloc失败
        return ERROR;   // 返回NON_ALLOCATED
    }

    // ----- 2 原子结点元素赋值 -----
    (*node)->tag = ATOM;        // tag为ATOM类型
    (*node)->item.atom = chr;   // item.atom为char(原子结点名)
    (*node)->next = NULL;       // next为NULL

    return OK;
}


/*!
 * @brief **广义表使用队列建表(递归)**
 * @param char_queue 字符队列(指针)
 * @param node 结点(广义表结点二级指针)
 * @note
 * 广义表使用队列建表(递归)
 * ---------------------
 * ---------------------
 *
 * ---------------------
 * ###1 空队判断###
 * &emsp; **if** 队列为空 :\n
 * &emsp;&emsp; 返回, **递归结束**\n
 * ###2 出队, 字符值赋给chr###
 * ###3 各类型chr分别处理###
 * - **I**&nbsp;&nbsp; chr为'('\n
 *  + 对node构造子表头结点\n
 *  + 对&(*node)->item.head执行递归\n
 *  + 对node执行递归\n
 * - **II**&nbsp; chr为小写字母(原子结点名称)\n
 *  + 对node构造原子结点\n
 *  + 对node执行递归\n
 * - **III** chr为','\n
 *  + 对&(*node)->next执行递归\n
 * - **IV**&nbsp; chr为')'\n
 * &emsp;&emsp; **if** *node不为NULL\n
 * &emsp;&emsp;&emsp; (*node)->next设置为NULL,
 * (如果*node为NULL, 则表示当前子表为空表, 字符串为"()")\n
 */
void GenListCreateByQueueRecursive(circular_queue_t* char_queue, gen_list_node_t** node) {

    // ----- 1 空队判断 -----
    if (CircularQueueGetLength(*char_queue) == 0) { // if 队列为空
        return; // 返回(递归结束)
    }

    // ----- 2 出队, 字符值赋给chr -----
    QUEUE_ELEM chr;
    CircularQueueDeQueue(char_queue, &chr);

    // ----- 3 各类型chr分别处理 -----
    if (chr == '(') {   // chr为'('
        GenListInitListHeadNode(node);  // 对node构造子表头结点
        GenListCreateByQueueRecursive(char_queue, &(*node)->item.head); // 对&(*node)->item.head执行递归
        GenListCreateByQueueRecursive(char_queue, node);    // 对node执行递归
    } else if (isalpha(chr)) {  // chr为小写字母(原子结点名称)
        GenListInitAtomNode(node, chr); // 对node构造原子结点
        GenListCreateByQueueRecursive(char_queue, node);    // 对node执行递归
    } else if (chr == ',') {    // chr为','
        GenListCreateByQueueRecursive(char_queue, &(*node)->next);  // 对&(*node)->next执行递归
    } else if (chr == ')') {    // chr为')'
        if (*node) {    // if *node不为NULL
            (*node)->next = NULL;   // (*node)->next设置为NULL, (如果*node为NULL, 则表示当前子表为空表, 字符串为"()")
        }
    }
}


/*!
 * @brief **广义表使用字符串建表**
 * @param gen_list 广义表(指针)
 * @param str 字符串
 * @param str_len 字符串长度
 * @note
 * 广义表使用字符串建表
 * -----------------
 * -----------------
 *
 * -----------------
 * ###1 初始化队列###
 * ###2 字符串的每个字符入队###
 * ###3 调用GenListCreateByQueueRecursive建表###
 */
void GenListCreateByStr(gen_list_node_t** gen_list, char* str, int str_len) {

    // ----- 1 初始化队列 -----
    circular_queue_t char_queue;
    CircularQueueInit(&char_queue);

    // ----- 2 字符串的每个字符入队 -----
    for (int i = 0; i < str_len; i++) {
        CircularQueueEnQueue(&char_queue, str[i]);
    }

    // ----- 3 调用GenListCreateByQueueRecursive建表 -----
    GenListCreateByQueueRecursive(&char_queue, gen_list);
}


/*!
 * @brief **广义表转换成字符串**
 * @param gen_list 广义表(指针)
 * @param gen_list_str 广义表字符串(用于转换)
 * @param str_len_limit 字符串长度限制
 * @return 执行结果
 * 广义表转换成字符串
 * ---------------
 * ---------------
 *
 * ---------------
 * ###1 初始化队列和字符串###
 * - **I**&nbsp;&nbsp; 初始化字符队列
 * - **II**&nbsp; 初始化字符串
 * ###2 调用GenListToStringRecursive, 生成字符串###
 * ###3 将字符队列转换成字符串 ###
 */
status_t GenListToString(gen_list_node_t* gen_list, char* gen_list_str, int str_len_limit) {

    // ----- 1 初始化队列和字符串 -----
    circular_queue_t char_queue;
    CircularQueueInit(&char_queue); // 初始化字符队列

    memset(gen_list_str, 0, str_len_limit * sizeof(char));  // 初始化字符串

    // ----- 2 调用GenListToStringRecursive, 生成字符串 -----
    GenListToCharQueueRecursive(gen_list, &char_queue);

    // ----- 3 将字符队列转换成字符串 -----
    CircularQueueToString(&char_queue, gen_list_str, str_len_limit);

    return OK;
}


/*!
 * @brief **广义表转换成字符队列**
 * @param gen_list 广义表
 * @param char_queue 字符队列
 * @note
 * 广义表转换成字符队列
 * -----------------
 * -----------------
 *
 *
 * -----------------
 * ###1 初始化cur结点指针###
 * &emsp; 指向当前(子)广义表表头\n
 * ###2 字符‘(’入队###
 * ###3 构造表内元素###
 * &emsp; **while** cur指向结点不为NULL :\n
 * &emsp;&emsp; **if** tag为LIST_HEAD类型 :\n
 * &emsp;&emsp;&emsp; 对cur进行递归\n
 * &emsp;&emsp; **if** tag为ATOM类型 :\n
 * &emsp;&emsp;&emsp; cur->item.atom入队\n
 * &emsp;&emsp; **if** cur->next不为NULL :\n
 * &emsp;&emsp;&emsp; ','入队\n
 * &emsp;&emsp; cur指向cur->next\n
 * ###4 子表遍历结束处理###
 * &emsp; ')'入队\n
 */
void GenListToCharQueueRecursive(gen_list_t gen_list, circular_queue_t* char_queue) {

    // ----- 1 初始化cur结点指针 -----
    gen_list_node_t* cur = gen_list->item.head; // 指向当前(子)广义表表头

    // ----- 2 字符‘(’入队 -----
    CircularQueueEnQueue(char_queue, '(');

    // ----- 3 构造表内元素 -----
    while (cur) {   // while cur指向结点不为NULL
        if (cur->tag == LIST_HEAD) {    // if tag为LIST_HEAD类型
            GenListToCharQueueRecursive(cur, char_queue);   // 对cur进行递归
        } else if (cur->tag == ATOM) {  // if tag为ATOM类型
            CircularQueueEnQueue(char_queue, cur->item.atom);   // cur->item.atom入队
        }

        if (cur->next != NULL) {    // if cur->next不为NULL
            CircularQueueEnQueue(char_queue, ',');  // ','入队
        }

        cur = cur->next;    // cur指向cur->next
    }

    // ----- 4 子表遍历结束处理 -----
    CircularQueueEnQueue(char_queue, ')');  // ')'入队
}


/*!
 * @brief **广义表深度(递归)**
 * @param gen_list_node 广义表结点
 * @return 深度值
 * @note
 * 广义表深度(递归)
 * --------------
 * --------------
 *
 * --------------
 * ###1 空表处理###
 * &emsp; 返回1\n
 * ###2 原子结点处理###
 * &emsp; 返回0\n
 * ###3 非空表处理###
 * &emsp; 子表最大深度, 初始化为0\n
 * &emsp; **while** 表内有未遍历结点 :\n
 * &emsp;&emsp; 对当前结点, 递归求该结点对应的子表深度\n
 * &emsp;&emsp; 更新最大子表深度\n
 * ###4 深度更新###
 * &emsp; 子表最大深度 + 1\n
 */
int GenListDepthRecursive(gen_list_node_t* gen_list_node) {

    // ----- 1 空表处理 -----
    if (!gen_list_node) {
        return 1;   // 返回1
    }

    // ----- 2 原子结点处理 -----
    if (gen_list_node->tag == ATOM) {
        return 0;   // 返回0
    }

    // ----- 3 非空表处理 -----
    int max_sub_gen_list_depth = 0; // 子表最大深度, 初始化为0

    // while 表内有未遍历结点
    for (gen_list_t cur_gen_list = gen_list_node->item.head; cur_gen_list != NULL; cur_gen_list = cur_gen_list->next) {
        // 对当前结点, 递归求该结点对应的子表深度
        int cur_sub_gen_list_depth = GenListDepthRecursive(cur_gen_list);
        // 更新最大子表深度
        if (max_sub_gen_list_depth < cur_sub_gen_list_depth) {
            max_sub_gen_list_depth = cur_sub_gen_list_depth;
        }
    }

    // ----- 4 深度更新 -----
    max_sub_gen_list_depth++;   // 子表最大深度 + 1

    return max_sub_gen_list_depth;
}


/*!
 * @brief **广义表复制(递归)**
 * @param target_list_node 目标广义表结点(二级指针)
 * @param src_list_node 源广义表结点(指针)
 * @return 执行结果
 * @note
 * 广义表复制(递归)
 * --------------
 * --------------
 *
 * --------------
 * ###1 源广义表结点为NULL的情况###
 * &emsp; 目标广义表结点设置为NULL\n
 * &emsp; 返回OK\n
 * ###2 目标广义表结点分配内存###
 * &emsp; **if** 如果malloc失败 :\n
 * &emsp;&emsp; 返回NON_ALLOCATED\n
 * ###3 递归复制过程###
 * - **I**&nbsp;&nbsp; tag复制\n
 * - **II**&nbsp; item处理\n
 * &emsp; **if** tag为原子类型ATOM :\n
 * &emsp;&emsp; item.atom复制\n
 * &emsp; **else** :\n
 * &emsp;&emsp; 对item.head执行递归\n
 * - **III** next处理\n
 * &emsp;&emsp; 对next执行递归\n
 */
status_t GenListCopyRecursive(gen_list_node_t** target_list_node, gen_list_node_t* src_list_node) {

    // ----- 1 源广义表结点为NULL的情况 -----
    if (src_list_node == NULL) {
        *target_list_node = NULL;   // 目标广义表结点设置为NULL
        return OK;  // 返回OK
    }

    // ----- 2 目标广义表结点分配内存 -----
    *target_list_node = (gen_list_t)malloc(sizeof(gen_list_node_t));
    if (*target_list_node == NULL) {    // if 如果malloc失败
        return NON_ALLOCATED;   // 返回NON_ALLOCATED
    }

    // ----- 3 递归复制过程 -----
    (*target_list_node)->tag = src_list_node->tag;  // tag复制

    if (src_list_node->tag == ATOM) {   // if tag为原子类型ATOM
        (*target_list_node)->item.atom = src_list_node->item.atom;  // item.atom复制
    } else {
        GenListCopyRecursive(&(*target_list_node)->item.head, src_list_node->item.head); // 对item.head执行递归
    }

    GenListCopyRecursive(&(*target_list_node)->next, src_list_node->next);  // 对next执行递归

    return OK;
}
