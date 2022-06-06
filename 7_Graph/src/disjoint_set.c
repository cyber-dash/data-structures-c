//
// Created by cyberdash@163.com on 2022/4/25.
//

#include <stdlib.h>
#include "disjoint_set.h"


/*!
 * 初始化并查集
 * @param disjoint_set
 * @param size
 * @return
 */
Status InitDisjointSet(DisjointSet* disjoint_set, int size) {
    disjoint_set->size = size;
    disjoint_set->parent = (int*)malloc(size * sizeof(int));
    if (!disjoint_set->parent) {
        return NON_ALLOCATED;
    }

    for (int i = 0; i < size; i++) {
        disjoint_set->parent[i] = -1;
    }

    return OK;
}


/*!
 * 销毁并查集
 * @param disjoint_set 并查集(二级指针)
 * @return 是否成功
 */
Status DisjointSetDestroy(DisjointSet** disjoint_set) {
    free((*disjoint_set)->parent);
    free(*disjoint_set);
    *disjoint_set = NULL;

    return OK;
}


// 合并两个集合
Status DisjointSetUnion(DisjointSet* disjoint_set, int node1, int node2) {
    int root1 = DisjointSetFindRecursive(disjoint_set, node1);
    int root2 = DisjointSetFindRecursive(disjoint_set, node2);

    if (root1 == root2) {   // 不需要合并
        return OK;
    }

    disjoint_set->parent[root1] += disjoint_set->parent[root2];
    disjoint_set->parent[root2] = root1; // 将根root2连接到另一根root1下面

    return OK;
}


/*!
 * 查找索引对应的根结点索引
 * @param disjoint_set 并查集(指针)
 * @param index 索引
 * @return 根结点索引
 */
int DisjointSetFindRecursive(DisjointSet* disjoint_set, int index) {
    if (disjoint_set->parent[index] < 0) {
        return index;
    }

    return DisjointSetFindRecursive(disjoint_set, disjoint_set->parent[index]);
}
