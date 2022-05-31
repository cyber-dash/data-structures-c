//
// Created by cyberdash@163.com on 2022/4/8.
//

#include "array.h"
#include <stdlib.h>
#include <stdarg.h>


Status InitArray(Array* A, int dim, ...) {
    va_list ap;
	if (dim < 1 || dim > MAX_ARRAY_DIM) {
		return ERROR;
	}

	A->dim = dim;
	A->bounds = (int*)malloc(dim * sizeof(int));
	if (!A->bounds) return OVERFLOW;

	int elemtotal = 1;
	va_start(ap, dim);
	for (int i = 0; i < dim; ++i) {
		A->bounds[i] = va_arg(ap, int);
		if (A->bounds[i] < 0) return UNDERFLOW;
		elemtotal *= A->bounds[i];
	}
	va_end(ap);

	A->base = (ElemType*)malloc(elemtotal * sizeof(ElemType));
	if (!A->base) {
		return OVERFLOW;
	}

	// 求映像函数的常数ci, 并存入A.constants[i - 1], i = 1, ..., dim
	A->constants = (int*)malloc(dim * sizeof(int));
	if (!A->constants) {
		return OVERFLOW;
	}

	for (int i = dim - 2; i >= 0; --i) {
		A->constants[i] = A->bounds[i + 1] * A->constants[i + 1];
	}

	return OK;
}
