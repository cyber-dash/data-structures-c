/*!
 * @file array.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 多维数组源文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_ARRAY_H
#define CYBER_DASH_ARRAY_H


#include <stdarg.h>
#include "common.h"

#define MAX_ARRAY_DIM   8

typedef struct {
    ELEM* elements; // 数组元素基址, 由InitArray分配
    int dim;        // 数组维数
    int* bounds;    // 数组维界基址, 由InitArray分配
    int* constants; // 数组映像函数常量基址, 由InitArray分配
} MultiDimensionalArray;


status_t MultiDimensionalArrayInit(MultiDimensionalArray* array, int dim, ...);

status_t MultiDimensionalArrayDestroy(MultiDimensionalArray* A);

status_t MultiDimensionalArrayValue(MultiDimensionalArray A, ELEM* e, ...);

status_t MultiDimensionalArrayAssign(MultiDimensionalArray *A, ELEM e, ...);



#endif // CYBER_DASH_ARRAY_H
