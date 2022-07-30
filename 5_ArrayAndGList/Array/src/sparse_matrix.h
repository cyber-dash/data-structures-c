/*!
 * @file sparse_matrix.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  稀疏矩阵头文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "common.h"


#define MAXSIZE	12500	// 假设非零元个数的最大值为12500

typedef struct {
    // 该非零元的行下标和列下标
	int	row;
    int column;
	ELEM	elem;
} triple_t;

typedef struct {
    // 矩阵的行数, 列数和非零元个数
    int row_num;
    int column_num;
    int non_zero_count;
	triple_t    elements[MAXSIZE + 1];	// 非零元三元组表, elements[0]未用
    // int     terms;              // 当前矩阵多少个非零个数
} sparse_matrix_t;


status_t SparseMatrixCreate(sparse_matrix_t *sparse_matrix, int rows, int columns);

status_t SparseMatrixDestroy(sparse_matrix_t *sparse_matrix);

status_t SparseMatrixPrint(sparse_matrix_t sparse_matrix);

status_t SparseMatrixCopy(sparse_matrix_t M, sparse_matrix_t* T);

status_t SparseMatrixAdd(sparse_matrix_t M, sparse_matrix_t N, sparse_matrix_t *Q);

status_t SparseMatrixSub(sparse_matrix_t M, sparse_matrix_t N, sparse_matrix_t *Q);

status_t SparseMatrixMultiply(sparse_matrix_t M, sparse_matrix_t N, sparse_matrix_t *Q);

status_t SparseMatrixTranspose(sparse_matrix_t matrix, sparse_matrix_t* transposed_matrix);

status_t SparseMatrixFastTranspose(sparse_matrix_t matrix, sparse_matrix_t* transposed_matrix);

status_t SparseMatrixAddAndReplaceElem(sparse_matrix_t* matrix, int row, int col, ELEM elem);

status_t SparseMatrixRemoveElem(sparse_matrix_t* matrix, int row, int col, ELEM* elem);