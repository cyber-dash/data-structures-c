/*!
 * @file disjoint_set.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 并查集
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdlib.h>
#include "disjoint_set.h"


/*!
 * 初始化并查集
 * @param disjoint_set 并查集(指针)
 * @param size 并查集大小
 * @return 执行结果
 */
status_t InitDisjointSet(DisjointSet* disjoint_set, int size) {
    disjoint_set->size = size;
    disjoint_set->parent_index_array = (int*)malloc(size * sizeof(int));
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
status_t DisjointSetDestroy(DisjointSet** disjoint_set) {
    free((*disjoint_set)->parent_index_array);
    free(*disjoint_set);
    *disjoint_set = NULL;

    return OK;
}


/*!
 * 并查集合并
 * @param disjoint_set 并查集(指针)
 * @param index1 索引1
 * @param index2 索引2
 * @return 执行结果
 */
status_t DisjointSetUnion(DisjointSet* disjoint_set, int index1, int index2) {
    int root1 = DisjointSetFindRecursive(disjoint_set, index1);
    int root2 = DisjointSetFindRecursive(disjoint_set, index2);

    if (root1 < 0 || root2 < 0) {
        return ERROR;
    }

    if (root1 == root2) {   // 不需要合并
        return OK;
    }

    // 将根root2连接到另一根root1下面
    disjoint_set->parent_index_array[root1] += disjoint_set->parent_index_array[root2];
    disjoint_set->parent_index_array[root2] = root1;

    return OK;
}


/*!
 * 查找索引的根结点索引(递归)
 * @param disjoint_set 并查集(指针)
 * @param index 索引
 * @return 根结点索引
 */
int DisjointSetFindRecursive(DisjointSet* disjoint_set, int index) {
    if (disjoint_set->parent_index_array[index] < 0) {
        return index;
    }

    return DisjointSetFindRecursive(disjoint_set, disjoint_set->parent_index_array[index]);
}


/*!
 * 查找索引的根结点索引
 * @param disjoint_set 并查集(指针)
 * @param index 索引
 * @return 根结点索引
 */
int DisjointSetFind(DisjointSet* disjoint_set, int index) {
    while (disjoint_set->parent_index_array[index] >= 0) {
        index = disjoint_set->parent_index_array[index];
    }

    return index;
}
