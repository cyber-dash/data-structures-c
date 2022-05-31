//
// Created by cyberdash@163.com on 2022/4/8.
//

#include "sparseMatrix.h"
#include <stdlib.h>
#include <stdio.h>


/*!
 * 初始化稀疏矩阵
 * @param M
 * @param rows
 * @param columns
 * @param terms
 * @return
 */
Status CreateSMatrix(TSMatrix* M, int rows, int columns) {
    M->mu = rows;       // 行数0
    M->nu = columns;    // 列数0
    M->tu = 0;          // 非零元素数初始化为0

    // 判断矩阵元素总数是否小于等于MAXSIZE
    int numberOfElem = rows * columns;
    if (numberOfElem > MAXSIZE) {
        return ERROR;
    }

    return OK;
}


/*!
 * 稀疏矩阵转置
 * @param M 原矩阵
 * @param T 转置矩阵
 * @return 是否成功
 */
Status TransposeSMatrix(TSMatrix M, TSMatrix *T) {
    // 采用三元组表存储表示, 求稀疏矩阵M的转置矩阵T
    T->mu = M.nu;
    T->nu = M.mu;
    T->tu = M.tu;

    if (T->tu) {
        int q = 1;
        for (int col = 1; col <= M.nu; ++col) {
            for (int p = 1; p <= M.tu; ++p) {
                if (M.data[p].j == col) {
                    T->data[q].i = M.data[p].j;
                    T->data[q].j = M.data[p].i;
                    T->data[q].e = M.data[p].e;
                    ++q;
                }
            }
        }
    }

    return OK;
}


/*!
 * 稀疏矩阵快速转置
 * @param M 原矩阵
 * @param T 转置矩阵
 * @return 是否成功
 * @note
 *  注意, 索引是从1开始(不是从0)
 *  **num**: 保存原矩阵各列分别有多少个元素, 对应转置矩阵的各行有多少个元素 \n
 *  **cpot**: 执行转置时, 原矩阵各列(转置矩阵各行)的每一列(转置矩阵每一行)的任务执行数组 \n
 *
 *  \n先初始化以上两个数组 \n\n
 *  遍历M.data \n
 *  对原矩阵三元组第p个元素, 进行转置矩阵内三元组对应位置的赋值
 *  赋值结束后, 更新cpot[M.data[p].j]的值(下一次转置矩阵数组执行的位置, 向后挪一位) \n
 */
Status FastTransposeSMatrix(TSMatrix M, TSMatrix *T) {
    T->mu = M.nu;
    T->nu = M.mu;
    T->tu = M.tu;

    // 如果矩阵非零元素为0个, 则不做其他操作
    if (T->tu == 0) {
        return OK;
    }

    int* num = (int*)malloc((M.nu + 1) * sizeof(int));
    int* cpot = (int*)malloc((M.tu + 1) * sizeof(int));

    if (T->tu) {
        for (int col = 1; col <= M.nu; ++col) {
            num[col] = 0;
        }
        for (int t = 1; t <= M.tu; ++t) {
            ++num[M.data[t].j]; // 求M中每一列含非零元素个数(也就是转置数组每行多少个非零元素)
        }
        cpot[1] = 1;
        for (int col = 2; col <=M.nu; ++col) {
            cpot[col] = cpot[col - 1] + num[col - 1];
        }
        for (int p = 1; p <= M.tu; ++p) {
            int col = M.data[p].j;
            int q = cpot[col];
            T->data[q].i = M.data[p].j;
            T->data[q].j = M.data[p].i;
            T->data[q].e = M.data[p].e;
            ++cpot[col];
        }
    }

    return OK;
}


/*!
 *
 * @param M
 * @return
 */
Status DestroySMatrix(TSMatrix* M) {
    free(M->data);
    free(M);
}


Status PrintSMatrix(TSMatrix M) {
    printf("行数: %d\n", M.mu);
    printf("列数: %d\n", M.nu);
    printf("非零元素数: %d\n", M.tu);

    for (int idx = 1; idx <= M.tu; idx++) {
        printf("M[%d][%d]: %d\n",
               M.data[idx].i, M.data[idx].j, M.data[idx].e);
    }

    return OK;
}


void swap(Triple* a, Triple* b) {
    Triple tmp = *a;
    *a = *b;
    *b = tmp;
}


/*!
 *
 * @param M
 * @param row
 * @param col
 * @param elem
 * @return
 */
Status AddAndReplaceElem(TSMatrix *M, int row, int col, ElemType elem) {
    if (row > M->mu ||col > M->nu) {
        return ERROR;
    }

    int insert_pos = 0;
    for (int idx = 1; idx <= M->tu; idx++) {
        if (M->data[idx].i == row) {
            if (M->data[idx].j >= col) {
                insert_pos = idx;
                break;
            }
        } else if (M->data[idx].i > row) {
            insert_pos = idx;
            break;
        }
    }

    // [row][col]位置已有数据, 执行替换
    if (insert_pos != 0 &&
        M->data[insert_pos].i == row &&
        M->data[insert_pos].j == col)
    {
        M->data[insert_pos].e = elem;
        return OK;
    }

    // 如果insert_pos为0, 此时没有找到插入位置, 因此在最后一位插入
    if (insert_pos == 0) {
        insert_pos = M->tu + 1;
    }

        // 不能再插入
    if (M->tu == MAXSIZE || M->tu == M->mu * M->nu) {
        return OVERFLOW;
    }

    // 先插入到最后一个位置
    M->data[M->tu + 1].i = row;
    M->data[M->tu + 1].j = col;
    M->data[M->tu + 1].e = elem;

    // 从后向前, 依次相邻交换, 完成插入
    for (int idx = M->tu + 1; idx > insert_pos; idx--) {
        swap(&M->data[idx], &M->data[idx - 1]);
    }

    M->tu++;    // 插入后, 非零元素个数+1

    return OK;
}
