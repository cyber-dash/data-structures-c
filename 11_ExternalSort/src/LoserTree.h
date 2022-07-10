/*!
 * @file loserTree.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 外部排序 败者树
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */
#ifndef CYBER_DASH_LOSER_TREE_H
#define CYBER_DASH_LOSER_TREE_H


#define k 5
typedef int KeyType;        // 定义关键字类型为整数类型

typedef int LoserTree[k];
typedef struct {
    KeyType  key;
}LeafNode, LeafArr[k + 1];   // 外结点, 只存放待归并记录的关键字

void K_Merge(LoserTree loserTree, LeafArr b, int* array[], int limitLen);


#endif // CYBER_DASH_LOSER_TREE_H
