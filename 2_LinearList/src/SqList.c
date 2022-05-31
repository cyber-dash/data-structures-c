//
// Created by cyberdash@163.com on 2021/12/13.
//

#include "SqList.h"
#include <stdlib.h>
#include <stdio.h>


Status InitList_Sq(SqList *L) {
    L->elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L->elem) exit(NON_ALLOCATED);   // 存储分配失败
    L->length = 0;                  // 空表长度为0
    L->listsize = LIST_INIT_SIZE;   // 初始存储容量
    return OK;
}// InitList_Sq


Status ListInsert_Sq(SqList *L, int i, ElemType e) {
    // 在顺序表L中第i个位置之前插入新的元素e,
    // i的合法值为1<=i<=ListLength_Sq(L) + 1
    if(i < 1 || i > L->length + 1) return ERROR; // i值不合法
    if(L->length >= L->listsize) { // 当前存储空间已满, 增加分配
        ElemType* newbase = (ElemType*)realloc(L->elem,
                                 (L->listsize + LISTINCRMENT)*sizeof(ElemType));
        if (!newbase) exit(NON_ALLOCATED); // 存储分配失败
        L->elem = newbase;            // 新基址
        L->listsize += LISTINCRMENT;  // 增加存储容量
    }
    // ElemType* p = NULL;
    ElemType* q = &(L->elem[i-1]);    // q为插入位置
    for (ElemType* p = &(L->elem[L->length - 1]); p >= q; p--) {
        *(p + 1) = *p; // 插入位置及之后的元素右移
    }

    *q = e;      // 插入e
    L->length++; // 表长增1
    return OK;
} // ListInsert_Sq


Status ListDelete_Sq(SqList *L, int i, ElemType *e) {
    // 在顺序线性表L中删除第i个元素, 并用e返回其值
    // i的合法值为1<=i<=ListLength_Sq(L)
    if ((i < 1) || (i > L->length))
        return ERROR;
    ElemType* p = &(L->elem[i - 1]);          // p为被删除元素的位置
    *e = *p;                                  // 被删除元素的值赋给e
    ElemType* q = L->elem + L->length - 1;    // 表尾元素的位置
    for(++p;p<=q;++p) *(p-1)=*p;              // 被删除元素之后的元素左移
    --L->length;                              // 表长减1
    return OK;
} // ListDelete_Sq


/*!
 * @brief 顺序表查找函数
 * @param L
 * @param e
 * @param compare
 * @return
 */
int LocateElem_Sq(SqList *L, ElemType e,
                  int (*compare)(ElemType, ElemType)) {
    // 在顺序线性表L中查找第1个值与e满足compare()的元素的位序
    // 若找到, 则返回其在L中的位序, 否则返回0
    int i = 1;             // i的初值为第1个元素的位序
    ElemType* p = L->elem;   // p的初值为第1个元素的存储位置
    while (i <= L->length && (*compare)(*p++, e) != 0) ++i;
    if (i <= L->length) return i;
    else return 0;
} // LocateElem_Sq


/*
void MergeList_Sq(SqList *La, SqList *Lb, SqList *Lc) {

}
 */


void PrintList_Sq(SqList *L) {
    for (int i = 0; i < L->length; i++) {
        printf("%d ", L->elem[i]);
    }
}
