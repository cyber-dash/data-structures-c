/*!
 * @file disjoint_set.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 并查集
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_DISJOINT_SET_H
#define CYBER_DASH_DISJOINT_SET_H


#include "graph.h"


#define ROOT_PARENT_INDEX   -1

typedef struct DisjointSet {
    int size; //!< 大小
    int* parent_index_array; //!< 父节点数组
} DisjointSet;

// 构造函数
status_t InitDisjointSet(DisjointSet* disjoint_set, int size);

// 销毁并查集
status_t DisjointSetDestroy(DisjointSet** disjoint_set);

// 合并两个集合
status_t DisjointSetUnion(DisjointSet* disjoint_set, int root1, int root2);

// 查找
int DisjointSetFindRecursive(DisjointSet* disjoint_set, int index);

int DisjointSetFind(DisjointSet* disjoint_set, int index);
/*
// 合并集合(Weighted)
void WeightedUnion(int node1, int node2);

// 查找(非递归)
int FindNonRecursive(int weight);
*/

#endif // CYBER_DASH_DISJOINT_SET_H
