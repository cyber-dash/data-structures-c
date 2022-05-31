//
// Created by cyberdash@163.com on 2022/4/8.
//

#ifndef CYBER_DASH_ARRAY_H
#define CYBER_DASH_ARRAY_H


#include <stdarg.h>
#include "common.h"

#define MAX_ARRAY_DIM   8

typedef struct {
    ElemType    *base;      // 数组元素基址, 由InitArray分配
    int         dim;        // 数组维数
    int         *bounds;    // 数组维界基址, 由InitArray分配
    int         *constants; // 数组映像函数常量基址, 由InitArray分配
} Array;


Status InitArray(Array *A, int dim, ...);

Status DestroyArray(Array *A);

Status Value(Array A, ElemType* e, ...);

Status Assign(Array *A, ElemType e, ...);



#endif // CYBER_DASH_ARRAY_H
