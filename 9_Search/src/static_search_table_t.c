/*!
 * @file static_search_table_t.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 静态查找源文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "static_search_table_t.h"


Status StaticSearchTableInit(static_search_table_t* static_search_table, elem_t* elements, int length) {
    if (static_search_table == NULL) {
        return ERROR;
    }

    static_search_table->elements = (elem_t*)malloc(sizeof(elem_t) * (length + 1));
    static_search_table->length = length;

    for (int i = 1; i <= length; i++) {
        static_search_table->elements[i] = elements[i - 1];
    }

    return OK;
}


void StaticSearchTablePrint(static_search_table_t* static_search_table) {
    if (static_search_table == NULL || static_search_table->length == 0) {
        printf("空静态表");
    }

    printf("静态表:\n");
    for (int i = 1; i <= static_search_table->length; i++) {
        printf("{ key:%d, value:%.1lf }", static_search_table->elements[i].key, static_search_table->elements[i].value);
        if (i != static_search_table->length) {
            printf(", ");
        }
    }

    printf("\n\n");
}


int StaticSearchTableSeqSearch(static_search_table_t* static_search_table, KEY key) {
    static_search_table->elements[0].key = key; // 哨兵

    int i = static_search_table->length;
    while (!EQUAL(static_search_table->elements[i].key, key)) {
        i--;
    }

    return i;
}


int StaticSearchTableBinarySearch(static_search_table_t* static_search_table, KEY key) {
    int low = 1;
    int high = static_search_table->length;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (EQUAL(key, static_search_table->elements[mid].key)) {
            return mid;
        } else if (LESS_THAN(key, static_search_table->elements[mid].key)) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return 0;
}


/*
void SecondOptimal(binary_search_tree_t* T, elem_t* R, double* sw, int low, int high) {
    // 由有序表R[low ... high]及其累计权值表sw(其中sw[0]等于0)递归构造次有查找树T
    int i = low;
    double min = fabs(sw[high] - sw[low]);
    double dw = sw[high] + sw[low - 1];

	int j;
    for (j = low + 1; j <= high; j++) {
        if (fabs(dw - sw[j] - sw[j - 1]) < min) {
            i = j;
            min = fabs(dw - sw[j] - sw[j - 1]);
        }
    }

    *T = (binary_search_tree_t)malloc(sizeof(binary_search_tree_node_t));
    (*T)->data = R[i];     // 生成结点
    if (i == low) {
        (*T)->left_child = NULL;
    } else {
        SecondOptimal(&(*T)->left_child, R, sw, low, i - 1);
    }

    if (i == high) {
        (*T)->right_child = NULL;
    } else {
        SecondOptimal(&(*T)->right_child, R, sw, i + 1, high);
    }
}
 */
