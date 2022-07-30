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


typedef struct static_search_table_t {
    elem_t* elements;
    int length;
} static_search_table_t;


status_t StaticSearchTableInit(static_search_table_t* static_search_table, elem_t* elements, int length);

void StaticSearchTablePrint(static_search_table_t* static_search_table);

int StaticSearchTableSeqSearch(static_search_table_t* static_search_table, KEY key);

int StaticSearchTableBinarySearch(static_search_table_t* static_search_table, KEY key);


#endif // CYBER_DASH_STATIC_SEARCH_TABLE_H
