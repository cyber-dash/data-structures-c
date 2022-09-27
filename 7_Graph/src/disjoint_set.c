/*!
 * @file disjoint_set.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 并查集源文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdlib.h>
#include "disjoint_set.h"


/*!
 * @brief **初始化并查集**
 * @param disjoint_set 并查集(指针)
 * @param size 并查集size
 * @return 执行结果
 * @note
 * 初始化并查集
 * ----------
 * ----------
 *
 * ----------
 * ### 1 设置并查集size ###
 * ### 2 双亲结点索引数组parent_indexes分配内存 ###
 * &emsp; **if** 内存分配失败 : \n
 * &emsp;&emsp; 返回NON_ALLOCATED \n
 * ### 3 将parent_indexes每个结点的值(双亲结点索引)设置成-1
 */
status_t InitDisjointSet(disjoint_set_t* disjoint_set, int size) {
    // ----- 1 设置并查集size -----
    disjoint_set->size = size;

    // ----- 2 双亲结点索引数组parent_indexes分配内存 -----
    disjoint_set->parent_indexes = (int*)malloc(size * sizeof(int));
    if (!disjoint_set->parent_indexes) {    // if 内存分配失败
        return NON_ALLOCATED;   // 返回NON_ALLOCATED
    }

    // ----- 3 将parent_indexes每个结点的值(双亲结点索引)设置成-1 -----
    for (int i = 0; i < size; i++) {
        disjoint_set->parent_indexes[i] = ROOT_PARENT_INDEX;
    }

    return OK;
}


/*!
 * @brief **销毁并查集**
 * @param disjoint_set 并查集(二级指针)
 * @return 执行结果
 * @note
 * 销毁并查集
 * ---------
 * ---------
 *
 * ---------
 * - free并查集的父节点数组
 * - free并查集
 */
status_t DisjointSetDestroy(disjoint_set_t** disjoint_set) {
    free((*disjoint_set)->parent_indexes);  // free并查集的父节点数组
    free(*disjoint_set);    // free并查集
    *disjoint_set = NULL;

    return OK;
}


/*!
 * @brief **并查集合并**
 * @param disjoint_set 并查集指针)
 * @param index1 结点索引1
 * @param index2 结点索引2
 * @return 执行结果
 * @note
 * 并查集合并
 * ---------
 * ---------
 *
 * ---------
 */
status_t DisjointSetUnion(disjoint_set_t* disjoint_set, int index1, int index2) {
    int root1 = DisjointSetFindRecursive(disjoint_set, index1); // 取结点1的根结点索引root1
    int root2 = DisjointSetFindRecursive(disjoint_set, index2); // 取结点2的根结点索引root1

    /// - 边界条件判断 \n
    /// &emsp; **if** 两个根节点中任何一个小于0 : \n
    /// &emsp;&emsp; 返回ERROR \n
    /// &emsp; **if** 两个根节点相同 : \n
    /// &emsp;&emsp; 返回OK(已经在一个集合,不需要合并) \n
    if (root1 < 0 || root2 < 0) {
        return ERROR;
    }

    if (root1 == root2) {
        return OK;
    }

    /// - 将根root2加到另一根root1下面
    disjoint_set->parent_indexes[root1] += disjoint_set->parent_indexes[root2];
    disjoint_set->parent_indexes[root2] = root1;

    return OK;
}


/*!
 * @brief **并查集获取结点的根结点索引(递归)**
 * @param disjoint_set 并查集(指针)
 * @param index 结点索引
 * @return 根结点索引
 * @note
 * 并查集获取结点的根结点索引(递归)
 * ----------------------------
 * ----------------------------
 *
 * ----------------------------
 * - 根结点处理 \n
 * &emsp; **if** 参数结点的父节点索引 < 0 : \n
 * &emsp;&emsp; 返回参数结点索引(本身即为根节点索引) \n
 * - 递归调用DisjointSetFindRecursive \n
 */
int DisjointSetFindRecursive(disjoint_set_t* disjoint_set, int index) {
    // ----- 根结点处理 ----
    if (disjoint_set->parent_indexes[index] < 0) {  // if 参数结点的父节点索引 < 0
        return index;   // 返回参数结点索引(本身即为根节点索引)
    }

    // 递归调用DisjointSetFindRecursive
    return DisjointSetFindRecursive(disjoint_set, disjoint_set->parent_indexes[index]);
}


/*!
 * @brief **并查集获取结点的根结点索引**
 * @param disjoint_set 并查集(指针)
 * @param index 结点索引
 * @return 根结点索引
 * @note
 * 并查集获取结点的根结点索引
 * -----------------------
 * -----------------------
 *
 * -----------------------
 * **while** 结点的父节点索引 >= 0 : \n
 * &emsp; 结点索引 <== 父节点索引 \n
 * 返回结点索引值
 */
int DisjointSetFind(disjoint_set_t* disjoint_set, int index) {
    while (disjoint_set->parent_indexes[index] >= 0) {  // while 结点的父节点索引 >= 0
        index = disjoint_set->parent_indexes[index];    // 结点索引 <== 父节点索引
    }

    return index;   // 返回结点索引值
}
