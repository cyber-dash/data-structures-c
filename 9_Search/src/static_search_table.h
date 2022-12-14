/*!
 * @file static_search_table.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 静态查找头文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_STATIC_SEARCH_TABLE_H
#define CYBER_DASH_STATIC_SEARCH_TABLE_H


#include "common.h"


/*! @brief 静态搜索表元素 */
typedef struct {
    KEY     key;    //!< 关键码
    VALUE   value;  //!< 值
} elem_t;

/*
typedef struct binary_search_tree_node {
    elem_t data; //!< 数据项
    struct binary_search_tree_node* left_child; //!< 左孩子指针
    struct binary_search_tree_node* right_child; //!< 右孩子指针
} binary_search_tree_node_t;

typedef binary_search_tree_node_t* binary_search_tree_t;
*/

/*! @brief 静态搜索表 */
typedef struct {
    elem_t* elements;   //!< 元素数组
    int length;         //!< 数组长度
} static_search_table_t;


// 静态搜索表初始化
status_t StaticSearchTableInit(static_search_table_t* static_search_table, elem_t* elements, int length);

// 静态搜索表打印
void StaticSearchTablePrint(static_search_table_t* static_search_table);

// 静态搜索表顺序搜索
int StaticSearchTableSeqSearch(static_search_table_t* static_search_table, KEY key);

// 静态搜索表二分查找
int StaticSearchTableBinarySearch(static_search_table_t* static_search_table, KEY key);


#endif // CYBER_DASH_STATIC_SEARCH_TABLE_H
