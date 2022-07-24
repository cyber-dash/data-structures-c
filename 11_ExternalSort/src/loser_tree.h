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


#define SEQ_QUEUE_COUNT 5

typedef int KEY;        // 定义关键字类型为整数类型
typedef int loser_tree_t[SEQ_QUEUE_COUNT];

typedef struct leaf_t {
    KEY key;
} leaf_t;

typedef leaf_t leaves_t[SEQ_QUEUE_COUNT + 1];   // 外结点, 只存放待归并记录的关键字

void KWayMerge(loser_tree_t loser_tree, leaves_t leaves, int* K_way_sorted_lists[], int K, int limit_length);


#endif // CYBER_DASH_LOSER_TREE_H
