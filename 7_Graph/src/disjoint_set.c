//
// Created by cyberdash@163.com on 2022/4/25.
//

#include <stdlib.h>
#include "disjoint_set.h"


/*!
 * 初始化并查集
 * @param disjointSet
 * @param size
 * @return
 */
Status InitDisjointSet(DisjointSet* disjointSet, int size) {
    disjointSet->size = size;
    disjointSet->parent = (int*)malloc(size * sizeof(int));
    /* error handler */

    for (int i = 0; i < size; i++) {
        disjointSet->parent[i] = -1;
    }

    return OK;
}


Status DeleteDisjointSet(DisjointSet* disjointSet) {
    free(disjointSet->parent);
    free(disjointSet);

    return OK;
}


// 合并两个集合
Status DisjointSetUnion(DisjointSet* disjointSet, int node1, int node2) {
    int root1 = Find(disjointSet, node1);
    int root2 = Find(disjointSet, node2);

    if (root1 == root2) {   // 不需要合并
        return OK;
    }

    disjointSet->parent[root1] += disjointSet->parent[root2];
    disjointSet->parent[root2] = root1; // 将根root2连接到另一根root1下面

    return OK;
}


/*!
 *
 * @param disjointSet
 * @param index
 * @return
 */
int Find(DisjointSet* disjointSet, int index) {
    if (disjointSet->parent[index] < 0) {
        return index;
    }

    return Find(disjointSet, disjointSet->parent[index]);
}
