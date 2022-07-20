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


#include "circular_queue.h"


/*! @brief 广义表原子结点数据项类型 */
typedef char ATOM_TYPE;

/*! @brief 广义表原子结点类型 */
typedef enum { ATOM, LIST } ELEM_TAG;

/*! @brief 广义表结点 */
typedef struct gen_list_node gen_list_node_t;

/*! @brief 广义表 */
typedef gen_list_node_t* gen_list_t;

/*! @brief 广义表数据项 */
typedef union {
    ATOM_TYPE   atom;           //!< 原子结点的值域
    gen_list_node_t*    head;   //!< 表结点的头结点(指针)
} gen_list_node_item_t;

/*! @brief 广义表 */
struct gen_list_node {
    ELEM_TAG    tag;              //!< 节点类型
    gen_list_node_item_t item;    //!< 结点数据项
    gen_list_node_t*    next;     //!< 下一个结点(指针)
};


void GenListCreateByQueueRecursive(circular_queue_t* char_queue, gen_list_node_t** node);

void GenListCreateByStr(gen_list_node_t** gen_list, char* str, int str_len);

status_t GenListToString(gen_list_node_t* gen_list, char* gen_list_str, int str_len_limit);

void GenListToCharQueueRecursive(gen_list_t gen_list, circular_queue_t* char_queue);

int GenListDepthRecursive(gen_list_t gen_list_node);

status_t GenListCopyRecursive(gen_list_t* target_list_node, gen_list_t src_list_node);


#endif // CYBER_DASH_GENERALIZED_LIST_H
