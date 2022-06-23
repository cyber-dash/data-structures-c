// 
// Created by cyberdash@163.com on 2022/4/25.
//

#ifndef CYBER_DASH_DISJOINT_SET_H
#define CYBER_DASH_DISJOINT_SET_H


#include "graph.h"


#define ROOT_PARENT_INDEX   -1

typedef struct {
    int size; //!< 大小
    int* parent_index_array; //!< 父节点数组
} DisjointSet;

// 构造函数
Status InitDisjointSet(DisjointSet* disjoint_set, int size);

// 销毁并查集
Status DisjointSetDestroy(DisjointSet** disjoint_set);

// 合并两个集合
Status DisjointSetUnion(DisjointSet* disjoint_set, int root1, int root2);

// 查找
int DisjointSetFindRecursive(DisjointSet* disjoint_set, int index);

/*
// 合并集合(Weighted)
void WeightedUnion(int node1, int node2);

// 查找(非递归)
int FindNonRecursive(int weight);
*/

#endif // CYBER_DASH_DISJOINT_SET_H
