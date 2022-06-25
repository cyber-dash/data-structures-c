//
// Created by cyberdash@163.com on 2022/4/25.
//

#include <stdlib.h>
#include "disjoint_set.h"


/*!
 * 初始化并查集
 * @param disjoint_set 并查集(指针)
 * @param size 并查集大小
 * @return 执行结果
 */
Status InitDisjointSet(DisjointSet* disjoint_set, int size) {
    disjoint_set->size = size;
    disjoint_set->parent_index_array = (int*)malloc(size * sizeof(int));
    // disjoint_set->parent_index_array = (int*)malloc(MAX_EDGE_CNT * sizeof(int));
    if (!disjoint_set->parent_index_array) {
        return NON_ALLOCATED;
    }

    for (int i = 0; i < size; i++) {
        disjoint_set->parent_index_array[i] = -1;
    }

    return OK;
}


/*!
 * 销毁并查集
 * @param disjoint_set 并查集(二级指针)
 * @return 是否成功
 */
Status DisjointSetDestroy(DisjointSet** disjoint_set) {
    free((*disjoint_set)->parent_index_array);
    free(*disjoint_set);
    *disjoint_set = NULL;

    return OK;
}


// 合并两个集合
Status DisjointSetUnion(DisjointSet* disjoint_set, int node1, int node2) {
    int root1 = DisjointSetFindRecursive(disjoint_set, node1);
    int root2 = DisjointSetFindRecursive(disjoint_set, node2);
    // int root1 = DisjointSetFind(disjoint_set, node1);
    // int root2 = DisjointSetFind(disjoint_set, node2);

    if (root1 < 0 || root2 < 0) {
        return ERROR;
    }

    if (root1 == root2) {   // 不需要合并
        return OK;
    }

    disjoint_set->parent_index_array[root1] += disjoint_set->parent_index_array[root2];
    disjoint_set->parent_index_array[root2] = root1; // 将根root2连接到另一根root1下面

    return OK;
}


/*!
 * 查找索引对应的根结点索引
 * @param disjoint_set 并查集(指针)
 * @param index 索引
 * @return 根结点索引
 */
int DisjointSetFindRecursive(DisjointSet* disjoint_set, int index) {
    int parent_index = disjoint_set->parent_index_array[index];
    // if (disjoint_set->parent_index_array[index] < 0) {
    if (parent_index < 0) {
        return index;
    }

    // return DisjointSetFindRecursive(disjoint_set, disjoint_set->parent_index_array[index]);
    return DisjointSetFindRecursive(disjoint_set, parent_index);
}


/*
int DisjointSet::FindNonRecursive(int value) {

    while (parent_[value] >= 0) {
        value = parent_[value];
    }

    return value;
}
 */
int DisjointSetFind(DisjointSet* disjoint_set, int index) {
    while (disjoint_set->parent_index_array[index] >= 0) {
        index = disjoint_set->parent_index_array[index];
    }

    return index;
}
