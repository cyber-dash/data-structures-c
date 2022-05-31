// 
// Created by cyberdash@163.com on 2022/4/25.
//

#ifndef CYBER_DASH_DISJOINT_SET_H
#define CYBER_DASH_DISJOINT_SET_H


#include "graph.h"

typedef struct {
    int size; //!< 大小
    int* parent; //!< 父节点数组
} DisjointSet;


// 构造函数
Status InitDisjointSet(DisjointSet* disjointSet, int size);

Status DeleteDisjointSet(DisjointSet* disjointSet);

// 合并两个集合
Status DisjointSetUnion(DisjointSet* disjointSet, int root1, int root2);

// 查找
int Find(DisjointSet* disjointSet, int value);

/*
// 合并集合(Weighted)
void WeightedUnion(int node1, int node2);

// 查找(非递归)
int FindNonRecursive(int value);
*/

#endif // CYBER_DASH_DISJOINT_SET_H
