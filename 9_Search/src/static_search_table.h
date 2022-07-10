/*!
 * @file static_search_table.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 查找 静态查找
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_STATIC_SEARCH_TABLE_H
#define CYBER_DASH_STATIC_SEARCH_TABLE_H


#include "search.h"


typedef struct {
    ElemType*   elem;
    int         length;
} SSTable;


Status Init_Seq(SSTable* ssTable, ElemType* elem_array, int array_length);

void Print_Seq(SSTable* ssTable);

int Search_Seq(SSTable* ssTable, KeyType key);

int Search_Bin(SSTable* ssTable, KeyType key);

void SecondOptimal(BiTree* T, ElemType* R, double* sw, int low, int high);


#endif // CYBER_DASH_STATIC_SEARCH_TABLE_H
