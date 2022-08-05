﻿/*!
 * @file sparse_matrix.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  稀疏矩阵源文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdlib.h>
#include <stdio.h>
#include "sparse_matrix.h"


/*!
 * @brief **交换函数**
 * @param item1 元素1
 * @param item2 元素2
 * @note
 */
void swap(triple_t* item1, triple_t* item2) {
    triple_t tmp = *item1;
    *item1 = *item2;
    *item2 = tmp;
}


/*!
 * @brief <h1>稀疏矩阵创建</h1>
 * @param sparse_matrix **稀疏矩阵**(指针)
 * @param rows **行数**
 * @param columns **列数**
 * @return **执行结果**
 * @note
 */
status_t SparseMatrixCreate(sparse_matrix_t* sparse_matrix, int rows, int columns) {

    /// - 初始化行数/列数/非0元素数
    sparse_matrix->row_num = rows;       // 行数0
    sparse_matrix->column_num = columns;    // 列数0
    sparse_matrix->non_zero_count = 0;          // 非零元素数初始化为0

    /// - 检查是否超过最大元素数MAX_SIZE限制
    int elem_count = rows * columns;
    if (elem_count > MAX_SIZE) {
        return ERROR;
    }

    return OK;
}


/*!
 * <h1>稀疏矩阵转置</h1>
 * @param matrix **原矩阵**
 * @param transposed_matrix **转置矩阵**
 * @return **执行结果**
 * @note
 */
status_t SparseMatrixTranspose(sparse_matrix_t matrix, sparse_matrix_t* transposed_matrix) {

    /// ### 1 非法参数判断 ###
    if (matrix.non_zero_count < 0 || matrix.column_num <= 0 || matrix.row_num <= 0) {
        return ERROR;
    }

    /// ### 2 初始化行数/列数/非0元素数 ###
    transposed_matrix->row_num = matrix.column_num;
    transposed_matrix->column_num = matrix.row_num;
    transposed_matrix->non_zero_count = matrix.non_zero_count;

    /// &emsp; **if** 非0元素的个数为0 \n
    /// &emsp;&emsp; 返回OK \n
    if (transposed_matrix->non_zero_count == 0) {
        return OK;
    }

    /// ### 3 转置 ###
    int index = 1;  // 三元组数组的索引, 初始化为1

    /// &emsp; **for loop** 遍历原矩阵的列(转置矩阵的行) : \n
    for (int column = 1; column <= matrix.column_num; column++) {
        /// &emsp;&emsp **for loop** 遍历原矩阵的三元组数组 : \n
        for (int i = 1; i <= matrix.non_zero_count; i++) {
            /// &emsp;&emsp; **if** 三元组元素的列号等于当前遍历列号 : \n
            /// &emsp;&emsp;&emsp; 使用三元组元素构造转置后的三元组元素, 赋值到新三元组数组index位置
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
 * <h1>稀疏矩阵快速转置</h1>
 * @param matrix **原矩阵**
 * @param transposed_matrix **转置矩阵**
 * @return 执行结果
 * @note
 */
status_t SparseMatrixFastTranspose(sparse_matrix_t matrix, sparse_matrix_t* transposed_matrix) {

    /// ### 1 非法参数判断 ###
    if (matrix.non_zero_count < 0 || matrix.column_num <= 0 || matrix.row_num <= 0) {
        return ERROR;
    }

    /// ### 2 初始化行数/列数/非0元素数 ###
    transposed_matrix->row_num = matrix.column_num;
    transposed_matrix->column_num = matrix.row_num;
    transposed_matrix->non_zero_count = matrix.non_zero_count;

    /// &emsp; **if** 非0元素的个数为0 \n
    /// &emsp;&emsp; 返回OK \n
    if (transposed_matrix->non_zero_count == 0) {
        return OK;
    }

    /// ### 3 构造"转置矩阵每行非0个数数组"和"转置矩阵每行遍历位置数组"###
    /// &emsp; "转置矩阵每行非0个数数组"分配内存\n
    int* non_zero_counts= (int*)malloc((transposed_matrix->row_num + 1) * sizeof(int));
    if (!non_zero_counts) {
        return NON_ALLOCATED;
    }

    /// &emsp; 将每个元素设置为0
    for (int row = 1; row <= transposed_matrix->row_num; row++) {
        non_zero_counts[row] = 0;
    }

    /// &emsp; "转置矩阵每行的遍历位置数组"分配内存
    int* traverse_indexes = (int*)malloc((transposed_matrix->row_num + 1) * sizeof(int));
    if (!traverse_indexes) {
        return NON_ALLOCATED;
    }

    /// ### 3 遍历求出转置矩阵每行的非0项数 ###
    for (int i = 1; i <= transposed_matrix->non_zero_count; ++i) {
        // 转置矩阵当前非零项的行号, 等于原数组该项的列号
        int cur_transposed_matrix_elem_row = matrix.elements[i].column;
        // 当前行的非零项数+1
        non_zero_counts[cur_transposed_matrix_elem_row]++;
    }

    /// ```
    /// 构造转置矩阵的三元组数组elements的分布
    ///
    /// elements[ 0, 第1行的首元素的位置,  ...   , 第2行的首元素的位置,      ...           ,第i行的首个元素的位置,        ... ]
    ///                    ^                           ^                                      ^
    ///                    |                           |                                      |
    ///      traverse_indexes[1]   traverse_indexes[2]     traverse_indexes[i]   ...
    ///
    /// 核心算法:
    ///
    ///    traverse_indexes[i] = traverse_indexes[i - 1] + non_zero_counts[i - 1];
    ///
    /// 即在三元组数组elements上, 转置矩阵每行首元素所在的位置, 等于上一行首个元素的位置 + 该行(上一行)的所有非零项数
    /// ```

    /// ### 4 遍历求出"转置矩阵每行的遍历位置数组"的每项元素值 ###
    /// &emsp; traverse_indexes[1]为1, 表示转置矩阵的第1行首个元素将插入到elements[1]
    traverse_indexes[1] = 1;
    /// &emsp; **for loop** 2到transposed_matrix->row_num : \n
    for (int row = 2; row <= transposed_matrix->row_num; row++) {
        /// &emsp;&emsp; traverse_indexes[i] = traverse_indexes[i - 1] + non_zero_counts[i - 1]; \n
        traverse_indexes[row] = traverse_indexes[row - 1] + non_zero_counts[row - 1];
    }

    /// ### 5 转置矩阵三元组数组更新 ###
    /// &emsp; **for loop** 遍历转置矩阵三元组数组 : \n
    for (int i = 1; i <= matrix.non_zero_count; i++) {
        /// 获取当前元素在转置矩阵的行号row \n
        int row = matrix.elements[i].column;
        /// 获取当前元素在转置矩阵三元组数组elements的索引traverse_index \n
        int traverse_index = traverse_indexes[row];

        /// 对索引traverse_index的三元组元素赋值, 行号/列号/值 \n
        transposed_matrix->elements[traverse_index].row = matrix.elements[i].column;
        transposed_matrix->elements[traverse_index].column = matrix.elements[i].row;
        transposed_matrix->elements[traverse_index].elem = matrix.elements[i].elem;

        /// 第row行的遍历索引traverse_indexes[row]加1(指向后面一个位置), 代表转置矩阵第row行刚刚完成了1个非零项的插入三元组数组
        traverse_indexes[row]++;
    }

    return OK;
}


/*!
 * <h1>销毁稀疏矩阵</h1>
 * @param sparse_matrix **稀疏矩阵**
 * @return **执行结果**
 * @note
 */
status_t SparseMatrixDestroy(sparse_matrix_t* sparse_matrix) {
    /// - 释放三元组数组
    free(sparse_matrix->elements);
    /// - 释放稀疏矩阵
    free(sparse_matrix);

    return OK;
}


/**
 * <h1>打印稀疏矩阵</h1>
 * @param sparse_matrix **稀疏矩阵**
 * @return **执行结果**
 * @note
 */
status_t SparseMatrixPrint(sparse_matrix_t sparse_matrix) {
    /// 打印行数/列数/非0元素数\n
    printf("行数: %d\n", sparse_matrix.row_num);
    printf("列数: %d\n", sparse_matrix.column_num);
    printf("非零元素数: %d\n", sparse_matrix.non_zero_count);

    /// **for loop** 遍历三元组数组 : \n
    for (int i = 1; i <= sparse_matrix.non_zero_count; i++) {
        /// &emsp; 打印遍历元素\n
        printf("sparse_matrix[%d][%d]: %d\n",
               sparse_matrix.elements[i].row, sparse_matrix.elements[i].column, sparse_matrix.elements[i].elem);
    }

    return OK;
}


/*!
 * <h1>添加或替换矩阵的值</h1>
 * @param sparse_matrix **稀疏矩阵**
 * @param row **行号**
 * @param col **列号**
 * @param elem **值**
 * @return
 */
status_t SparseMatrixAddAndReplaceElem(sparse_matrix_t* sparse_matrix, int row, int col, ELEM elem) {

    /// ### 1 行号列号合法性检查 ###
    /// &emsp; **if** 行号越界 或者 列号越界 : \n
    if (row > sparse_matrix->row_num || col > sparse_matrix->column_num) {
        /// &emsp;&emsp; 返回OVERFLOW \n
        return OVERFLOW;
    }

    /// ### 2 找到插入位置 ###
    /// &emsp; 初始化插入位置为0
    int insert_pos = 0;
    /// &emsp; **for loop** 遍历三元组数组 :\n
    for (int i = 1; i <= sparse_matrix->non_zero_count; i++) {
        // &emsp;&emsp; **if** 三元组数组
        if (sparse_matrix->elements[i].row == row) {
            if (sparse_matrix->elements[i].column >= col) {
                insert_pos = i;
                break;
            }
        } else if (sparse_matrix->elements[i].row > row) {
            insert_pos = i;
            break;
        }
    }

    // [row][col]位置已有数据, 执行替换
    if (insert_pos != 0 &&
        sparse_matrix->elements[insert_pos].row == row &&
        sparse_matrix->elements[insert_pos].column == col)
    {
        sparse_matrix->elements[insert_pos].elem = elem;
        return OK;
    }

    // 如果insert_pos为0, 此时没有找到插入位置, 因此在最后一位插入
    if (insert_pos == 0) {
        insert_pos = sparse_matrix->non_zero_count + 1;
    }

    // 不能再插入
    if (sparse_matrix->non_zero_count == MAX_SIZE || sparse_matrix->non_zero_count == sparse_matrix->row_num * sparse_matrix->column_num) {
        return OVERFLOW;
    }

    // 先插入到最后一个位置
    sparse_matrix->elements[sparse_matrix->non_zero_count + 1].row = row;
    sparse_matrix->elements[sparse_matrix->non_zero_count + 1].column = col;
    sparse_matrix->elements[sparse_matrix->non_zero_count + 1].elem = elem;

    // 从后向前, 依次相邻交换, 完成插入
    for (int idx = sparse_matrix->non_zero_count + 1; idx > insert_pos; idx--) {
        swap(&sparse_matrix->elements[idx], &sparse_matrix->elements[idx - 1]);
    }

    sparse_matrix->non_zero_count++;    // 插入后, 非零元素个数+1

    return OK;
}
