/*!
 * @file loser_tree.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 败者树头文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */
#ifndef CYBER_DASH_LOSER_TREE_H
#define CYBER_DASH_LOSER_TREE_H


typedef int KEY;        // 定义关键字类型为整数类型

typedef struct {
    KEY key;
} leaf_t;

void KWayMerge(int* K_way_sorted_lists[], int K, int* sorted_list_lengths);


#endif // CYBER_DASH_LOSER_TREE_H
