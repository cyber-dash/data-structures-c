/*!
 * @file loser_tree_t.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 外部排序 败者树
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */
#ifndef CYBER_DASH_LOSER_TREE_H
#define CYBER_DASH_LOSER_TREE_H


#define SIZE 5

typedef int KEY;        // 定义关键字类型为整数类型
typedef int loser_tree_t[SIZE];

typedef struct leaf_t {
    KEY key;
} leaf_t;// , leaves_t[SIZE + 1];   // 外结点, 只存放待归并记录的关键字

typedef leaf_t leaves_t[SIZE + 1];   // 外结点, 只存放待归并记录的关键字

void K_Merge(loser_tree_t loser_tree, leaves_t leaves, int* array[], int limit_length);


#endif // CYBER_DASH_LOSER_TREE_H
