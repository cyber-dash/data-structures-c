//
// Created by cyberdash@163.com on 2022/4/8.
//

#include "common.h"


#define MAXSIZE	12500	// 假设非零元个数的最大值为12500

typedef struct {
	int	i, j;			// 该非零元的行下标和列下标
	ElemType	e;
} Triple;

typedef struct {
	Triple	data[MAXSIZE + 1];	// 非零元三元组表, data[0]未用
	int		mu, nu, tu;			// 矩阵的行数, 列数和非零元个数
    int     terms;              // 当前矩阵多少个非零个数
} TSMatrix;


Status CreateSMatrix(TSMatrix *M, int rows, int columns);

Status DestroySMatrix(TSMatrix *M);

Status PrintSMatrix(TSMatrix M);

Status CopySMatrix(TSMatrix M, TSMatrix *T);

Status AddSMatrix(TSMatrix M, TSMatrix N, TSMatrix *Q);

Status SubMatrix(TSMatrix M, TSMatrix N, TSMatrix *Q);

Status MultSMatrix(TSMatrix M, TSMatrix N, TSMatrix *Q);

Status TransposeSMatrix(TSMatrix M, TSMatrix *Q);

Status FastTransposeSMatrix(TSMatrix M, TSMatrix *Q);

Status AddAndReplaceElem(TSMatrix *M, int row, int col, ElemType elem);

Status RemoveElemFromSMatrix(TSMatrix *M, int row, int col, ElemType *elem);