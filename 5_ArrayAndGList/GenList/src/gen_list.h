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
typedef enum { ATOM, LIST_HEAD } ELEM_TAG;

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
typedef struct gen_list_node {
    ELEM_TAG    tag;              //!< 节点类型
    gen_list_node_item_t item;    //!< 结点数据项
    gen_list_node_t*    next;     //!< 下一个结点(指针)
} gen_list_node_t;


// 广义表使用队列建表(递归)
void GenListCreateByQueueRecursive(circular_queue_t* char_queue, gen_list_node_t** node);

// 广义表使用字符串建表
void GenListCreateByStr(gen_list_node_t** gen_list, char* str, int str_len);

// 广义表转换成字符串
status_t GenListToString(gen_list_node_t* gen_list, char* gen_list_str, int str_len_limit);

// 广义表转换成字符队列
void GenListToCharQueueRecursive(gen_list_t gen_list, circular_queue_t* char_queue);

// 广义表深度(递归)
int GenListDepthRecursive(gen_list_node_t* gen_list_node);

// 广义表复制(递归)
status_t GenListCopyRecursive(gen_list_node_t** target_list_node, gen_list_node_t* src_list_node);


#endif // CYBER_DASH_GENERALIZED_LIST_H
