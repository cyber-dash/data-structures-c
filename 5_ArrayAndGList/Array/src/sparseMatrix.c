//
// Created by cyberdash@163.com on 2022/4/8.
//

#include "sparseMatrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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

    if (matrix.non_zero_count < 0 || matrix.column_num <= 0 || matrix.row_num <= 0) {
        return ERROR;
    }

    transposed_matrix->row_num = matrix.column_num;
    transposed_matrix->column_num = matrix.row_num;
    transposed_matrix->non_zero_count = matrix.non_zero_count;

    if (transposed_matrix->non_zero_count == 0) {
        return OK;
    }

    int index = 1;  // 三元组数组的索引, 初始化为1

    // 遍历原矩阵的列(转置矩阵的行)
    for (int column = 1; column <= matrix.column_num; column++) {
        // 遍历原矩阵的三元组数组
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
 * @param matrix 原矩阵
 * @param transposed_matrix 转置矩阵
 * @return 是否成功
 * @note
 *  注意, 索引是从1开始(不是从0)
 */
Status FastTransposeSMatrix(sparse_matrix_t matrix, sparse_matrix_t* transposed_matrix) {

    if (matrix.non_zero_count < 0 || matrix.column_num <= 0 || matrix.row_num <= 0) {
        return ERROR;
    }

    transposed_matrix->row_num = matrix.column_num;
    transposed_matrix->column_num = matrix.row_num;
    transposed_matrix->non_zero_count = matrix.non_zero_count;

    // 如果矩阵非零元素为0个, 则不做其他操作
    if (transposed_matrix->non_zero_count == 0) {
        return OK;
    }

    // 转置矩阵每行的非零项数数组, 初始化每行0个非零项
    int* non_zero_count_per_row_array = (int*)malloc((transposed_matrix->row_num + 1) * sizeof(int));
    for (int row = 1; row <= transposed_matrix->row_num; row++) {
        non_zero_count_per_row_array[row] = 0;
    }

    // 转置矩阵每行的迭代器数组
    int* iterator_per_row_array = (int*)malloc((transposed_matrix->row_num + 1) * sizeof(int));

    // 遍历原矩阵的三元组数组, 求出转置矩阵每行的非零项数
    for (int i = 1; i <= transposed_matrix->non_zero_count; ++i) {
        // 转置矩阵当前非零项的行号
        int cur_transposed_matrix_elem_row = matrix.elements[i].column;
        // 当前行的非零项数+1
        non_zero_count_per_row_array[cur_transposed_matrix_elem_row]++;
    }

    /// 构造转置矩阵的三元组数组elements的分布
    ///
    /// elements[ 0 第1行的首元素的位置   ...      第2行的首元素的位置      ...            第i行的首个元素的位置        ... ]
    ///                    ^                           ^                                      ^
    ///                    |                           |                                      |
    ///      iterator_per_row_array[1]      iterator_per_row_array[2]               iterator_per_row_array[i]   ...
    ///
    /// 核心算法:
    ///
    ///    iterator_per_row_array[i] = iterator_per_row_array[i - 1] + non_zero_count_per_row_array[i - 1];
    /// 即在三元组数组elements上, 转置矩阵每行首元素所在的位置, 等于上一行首个元素的位置 + 该行(上一行)的所有非零项数

    iterator_per_row_array[1] = 1;  // 表示转置矩阵的第1行首个元素将插入到elements[1]
    for (int row = 2; row <= transposed_matrix->row_num; row++) {
        iterator_per_row_array[row] = iterator_per_row_array[row - 1] + non_zero_count_per_row_array[row - 1];
    }

    // 转置矩阵的三元组数组elements更新
    for (int i = 1; i <= matrix.non_zero_count; i++) {
        int cur_elem_row = matrix.elements[i].column;           //!< 当前转置矩阵元素的行号
        int iterator = iterator_per_row_array[cur_elem_row];    //!< 当前转置矩阵元素在elements数组中对应的索引

        // 赋值
        transposed_matrix->elements[iterator].row = matrix.elements[i].column;
        transposed_matrix->elements[iterator].column = matrix.elements[i].row;
        transposed_matrix->elements[iterator].elem = matrix.elements[i].elem;

        // 第cur_elem_row行的迭代器加1(指向后面一个位置), 代表转置矩阵第cur_elem_row行刚刚完成了1个非零项的插入elements数组
        iterator_per_row_array[cur_elem_row]++;
    }

    return OK;
}


/*!
 * 销毁稀疏矩阵
 * @param sparse_matrix 稀疏矩阵
 * @return 执行结果
 */
Status DestroySMatrix(sparse_matrix_t* sparse_matrix) {
    free(sparse_matrix->elements);
    free(sparse_matrix);

    return OK;
}


/**
 * 打印稀疏矩阵
 * @param sparse_matrix 稀疏矩阵
 * @return 执行结果
 */
Status PrintSMatrix(sparse_matrix_t sparse_matrix) {
    printf("行数: %d\n", sparse_matrix.row_num);
    printf("列数: %d\n", sparse_matrix.column_num);
    printf("非零元素数: %d\n", sparse_matrix.non_zero_count);

    for (int i = 1; i <= sparse_matrix.non_zero_count; i++) {
        printf("sparse_matrix[%d][%d]: %d\n",
               sparse_matrix.elements[i].row, sparse_matrix.elements[i].column, sparse_matrix.elements[i].elem);
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
Status AddAndReplaceElem(sparse_matrix_t* M, int row, int col, ElemType elem) {
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
