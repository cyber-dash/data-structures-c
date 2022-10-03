/*!
 * @file array.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 多维数组源文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdlib.h>
#include <stdarg.h>
#include "multi_dimensional_array.h"


/*!
 * @brief **多维数组初始化**
 * @param array 多数数组(指针)
 * @param dim 维数
 * @param ... 数组数据
 * @return 执行结果
 * 多维数组初始化
 * ------------
 * ------------
 */
status_t MultiDimensionalArrayInit(MultiDimensionalArray* array, int dim, ...) {
    va_list ap;
	if (dim < 1 || dim > MAX_ARRAY_DIM) {
		return ERROR;
	}

    array->dim = dim;
    array->bounds = (int*)malloc(dim * sizeof(int));
	if (!array->bounds) {
        return OVERFLOW;
    }

	int elem_total = 1;
	va_start(ap, dim);
	for (int i = 0; i < dim; ++i) {
        array->bounds[i] = va_arg(ap, int);
		if (array->bounds[i] < 0) {
            return NON_EXISTENT;
        }
        elem_total *= array->bounds[i];
	}
	va_end(ap);

    array->elements = (ELEM*)malloc(elem_total * sizeof(ELEM));
	if (!array->elements) {
		return OVERFLOW;
	}

	// 求映像函数的常数ci, 并存入A.constants[row - 1], row = 1, ..., dim
	array->constants = (int*)malloc(dim * sizeof(int));
	if (!array->constants) {
		return OVERFLOW;
	}

	for (int i = dim - 2; i >= 0; --i) {
        array->constants[i] = array->bounds[i + 1] * array->constants[i + 1];
	}

	return OK;
}
