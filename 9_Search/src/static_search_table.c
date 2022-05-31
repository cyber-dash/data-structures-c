//
// Created by cyberdash@163.com on 2022/5/12.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "static_search_table.h"


Status Init_Seq(SSTable* ssTable, ElemType* elem_array, int array_length) {
    if (ssTable == NULL) {
        return STATUS_ERROR;
    }

    ssTable->elem = (ElemType*)malloc(sizeof(ElemType) * (array_length + 1));
    ssTable->length = array_length;

	int i;
    for (i = 1; i <= array_length; i++) {
        ssTable->elem[i] = elem_array[i - 1];
    }

    return STATUS_OK;
}


void Print_Seq(SSTable* ssTable) {
    if (ssTable == NULL || ssTable->length == 0) {
        printf("空顺序表");
    }

	int i;
    for (i = 1; i <= ssTable->length; i++) {
        printf("key:%d/value:%.1lf ", ssTable->elem[i].key, ssTable->elem[i].value);
    }

    printf("\n");
}


int Search_Seq(SSTable* ssTable, KeyType key) {
    int i = 0;
    ssTable->elem[i].key = key; // 哨兵
    for (i = ssTable->length; !EQ(ssTable->elem[i].key, key); --i);

    return i;
}


int Search_Bin(SSTable* ssTable, KeyType key) {
    int low = 1;
    int high = ssTable->length;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (EQ(key, ssTable->elem[mid].key)) {
            return mid;
        } else if (LT(key, ssTable->elem[mid].key)) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return 0;
}


/*!
 *
 * @param T
 * @param R
 * @param sw
 * @param low
 * @param high
 */
void SecondOptimal(BiTree* T, ElemType* R, double* sw, int low, int high) {
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

    *T = (BiTree)malloc(sizeof(BiTNode));
    (*T)->data = R[i];     // 生成结点
    if (i == low) {
        (*T)->lchild = NULL;
    } else {
        SecondOptimal(&(*T)->lchild, R, sw, low, i - 1);
    }

    if (i == high) {
        (*T)->rchild = NULL;
    } else {
        SecondOptimal(&(*T)->rchild, R, sw, i + 1, high);
    }
}
