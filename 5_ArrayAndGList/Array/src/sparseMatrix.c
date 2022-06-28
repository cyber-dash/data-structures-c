//
// Created by cyberdash@163.com on 2022/4/8.
//

#include "sparseMatrix.h"
#include <stdlib.h>
#include <stdio.h>


/*!
 * 初始化稀疏矩阵
 * @param sparse_matrix
 * @param rows
 * @param columns
 * @param terms
 * @return
 */
Status CreateSMatrix(sparse_matrix_t* sparse_matrix, int rows, int columns) {
    sparse_matrix->row_num = rows;       // 行数0
    sparse_matrix->column_num = columns;    // 列数0
    sparse_matrix->non_zero_count = 0;          // 非零元素数初始化为0

    // 判断矩阵元素总数是否小于等于MAXSIZE
    int elem_count = rows * columns;
    if (elem_count > MAXSIZE) {
        return ERROR;
    }

    return OK;
}


/*!
 * 稀疏矩阵转置
 * @param matrix 原矩阵
 * @param transposed_matrix 转置矩阵
 * @return 执行结果
 */
Status TransposeSMatrix(sparse_matrix_t matrix, sparse_matrix_t* transposed_matrix) {
    transposed_matrix->row_num = matrix.column_num;
    transposed_matrix->column_num = matrix.row_num;
    transposed_matrix->non_zero_count = matrix.non_zero_count;

    if (transposed_matrix->non_zero_count < 0) {
        return ERROR;
    }

    if (transposed_matrix->non_zero_count == 0) {
        return OK;
    }

    int index = 1;  // 三元组数组的索引, 初始化为1

    // 遍历原数组的列(转置数组的行)
    for (int column = 1; column <= matrix.column_num; column++) {
        // 遍历原数组的三元组数组
        for (int i = 1; i <= matrix.non_zero_count; i++) {
            // 如果当前元素的列号等于column, 将该元素对应的新数据, 插入到三元组数组index位置
            if (matrix.elements[i].column == column) {
                transposed_matrix->elements[index].row = matrix.elements[i].column; // 设置行
                transposed_matrix->elements[index].column = matrix.elements[i].row; // 设置列
                transposed_matrix->elements[index].elem = matrix.elements[i].elem;

                index++;
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
 *  遍历M.elements \n
 *  对原矩阵三元组第p个元素, 进行转置矩阵内三元组对应位置的赋值
 *  赋值结束后, 更新cpot[M.elements[p].column]的值(下一次转置矩阵数组执行的位置, 向后挪一位) \n
 */
Status FastTransposeSMatrix(sparse_matrix_t M, sparse_matrix_t *T) {
    T->row_num = M.column_num;
    T->column_num = M.row_num;
    T->non_zero_count = M.non_zero_count;

    // 如果矩阵非零元素为0个, 则不做其他操作
    if (T->non_zero_count == 0) {
        return OK;
    }

    int* num = (int*)malloc((M.column_num + 1) * sizeof(int));
    int* cpot = (int*)malloc((M.column_num + 1) * sizeof(int));

    if (T->non_zero_count) {
        for (int col = 1; col <= M.column_num; ++col) {
            num[col] = 0;
        }
        for (int t = 1; t <= M.non_zero_count; ++t) {
            ++num[M.elements[t].column]; // 求M中每一列含非零元素个数(也就是转置数组每行多少个非零元素)
        }
        cpot[1] = 1;
        for (int col = 2; col <=M.column_num; ++col) {
            cpot[col] = cpot[col - 1] + num[col - 1];
        }
        for (int p = 1; p <= M.non_zero_count; ++p) {
            int col = M.elements[p].column;
            int q = cpot[col];
            T->elements[q].row = M.elements[p].column;
            T->elements[q].column = M.elements[p].row;
            T->elements[q].elem = M.elements[p].elem;
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
Status DestroySMatrix(sparse_matrix_t* M) {
    free(M->elements);
    free(M);
}


Status PrintSMatrix(sparse_matrix_t M) {
    printf("行数: %d\n", M.row_num);
    printf("列数: %d\n", M.column_num);
    printf("非零元素数: %d\n", M.non_zero_count);

    for (int i = 1; i <= M.non_zero_count; i++) {
        printf("M[%d][%d]: %d\n",
               M.elements[i].row, M.elements[i].column, M.elements[i].elem);
    }

    return OK;
}


void swap(triple_t* a, triple_t* b) {
    triple_t tmp = *a;
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
Status AddAndReplaceElem(sparse_matrix_t *M, int row, int col, ElemType elem) {
    if (row > M->row_num || col > M->column_num) {
        return ERROR;
    }

    int insert_pos = 0;
    for (int idx = 1; idx <= M->non_zero_count; idx++) {
        if (M->elements[idx].row == row) {
            if (M->elements[idx].column >= col) {
                insert_pos = idx;
                break;
            }
        } else if (M->elements[idx].row > row) {
            insert_pos = idx;
            break;
        }
    }

    // [row][col]位置已有数据, 执行替换
    if (insert_pos != 0 &&
        M->elements[insert_pos].row == row &&
        M->elements[insert_pos].column == col)
    {
        M->elements[insert_pos].elem = elem;
        return OK;
    }

    // 如果insert_pos为0, 此时没有找到插入位置, 因此在最后一位插入
    if (insert_pos == 0) {
        insert_pos = M->non_zero_count + 1;
    }

        // 不能再插入
    if (M->non_zero_count == MAXSIZE || M->non_zero_count == M->row_num * M->column_num) {
        return OVERFLOW;
    }

    // 先插入到最后一个位置
    M->elements[M->non_zero_count + 1].row = row;
    M->elements[M->non_zero_count + 1].column = col;
    M->elements[M->non_zero_count + 1].elem = elem;

    // 从后向前, 依次相邻交换, 完成插入
    for (int idx = M->non_zero_count + 1; idx > insert_pos; idx--) {
        swap(&M->elements[idx], &M->elements[idx - 1]);
    }

    M->non_zero_count++;    // 插入后, 非零元素个数+1

    return OK;
}
