//
// Created by cyberdash@163.com on 2022/4/8.
//

#include "common.h"


#define MAXSIZE	12500	// 假设非零元个数的最大值为12500

typedef struct {
    // 该非零元的行下标和列下标
	int	row;
    int column;
	ElemType	elem;
} triple_t;

typedef struct {
    // 矩阵的行数, 列数和非零元个数
    int row_num;
    int column_num;
    int non_zero_count;
	triple_t    elements[MAXSIZE + 1];	// 非零元三元组表, elements[0]未用
    // int     terms;              // 当前矩阵多少个非零个数
} sparse_matrix_t;


Status CreateSMatrix(sparse_matrix_t *sparse_matrix, int rows, int columns);

Status DestroySMatrix(sparse_matrix_t *sparse_matrix);

Status PrintSMatrix(sparse_matrix_t sparse_matrix);

Status CopySMatrix(sparse_matrix_t M, sparse_matrix_t *T);

Status AddSMatrix(sparse_matrix_t M, sparse_matrix_t N, sparse_matrix_t *Q);

Status SubMatrix(sparse_matrix_t M, sparse_matrix_t N, sparse_matrix_t *Q);

Status MultSMatrix(sparse_matrix_t M, sparse_matrix_t N, sparse_matrix_t *Q);

Status TransposeSMatrix(sparse_matrix_t matrix, sparse_matrix_t *transposed_matrix);

Status FastTransposeSMatrix(sparse_matrix_t matrix, sparse_matrix_t *transposed_matrix);

Status AddAndReplaceElem(sparse_matrix_t *M, int row, int col, ElemType elem);

Status RemoveElemFromSMatrix(sparse_matrix_t *M, int row, int col, ElemType *elem);