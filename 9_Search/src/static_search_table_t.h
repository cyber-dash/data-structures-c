/*!
 * @file static_search_table_t.h
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
    KEY     key;
    VALUE   value;
} elem_t;

typedef struct binary_search_tree_node binary_search_tree_node_t;
struct binary_search_tree_node {
    elem_t data;
    binary_search_tree_node_t* left_child; // 左孩子指针
    binary_search_tree_node_t* right_child; // 右孩子指针
};

typedef binary_search_tree_node_t* binary_search_tree_t;


/*! @brief 静态搜索表 */
typedef struct static_search_table static_search_table_t;

/*! @brief 静态搜索表结构体 */
struct static_search_table {
    elem_t* elements;   //!< 元素数组
    int length;         //!< 数组长度
};


// 静态搜索表初始化
status_t StaticSearchTableInit(static_search_table_t* static_search_table, elem_t* elements, int length);

// 静态搜索表打印
void StaticSearchTablePrint(static_search_table_t* static_search_table);

// 静态搜索表顺序搜索
int StaticSearchTableSeqSearch(static_search_table_t* static_search_table, KEY key);

// 静态搜索表二分查找
int StaticSearchTableBinarySearch(static_search_table_t* static_search_table, KEY key);


#endif // CYBER_DASH_STATIC_SEARCH_TABLE_H
