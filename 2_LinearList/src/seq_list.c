//
// Created by cyberdash@163.com on 2021/12/13.
//

#include "seq_list.h"
#include <stdlib.h>
#include <stdio.h>


/*!
 * 初始化顺序表
 * @param seq_list 顺序表(指针)
 * @return 是否成功
 */
Status SeqListInit(seq_list_t* seq_list) {
    seq_list->elements = (ELEM_TYPE*)malloc(LIST_INIT_SIZE * sizeof(ELEM_TYPE));
    if (!seq_list->elements) {
        return NON_ALLOCATED;
    }

    seq_list->length = 0;                  // 空表长度为0
    seq_list->size = LIST_INIT_SIZE;   // 初始存储容量

    return OK;
}


/*!
 *
 * @param seq_list
 * @param pos
 * @param elem
 * @return
 */
Status SeqListInsert(seq_list_t* seq_list, int pos, ELEM_TYPE elem) {
    if (pos < 1 || pos > seq_list->length + 1) {
        return ERROR;
    }

    // 当前存储空间已满, 增加分配
    if (seq_list->length >= seq_list->size) {
        ELEM_TYPE* new_base = (ELEM_TYPE*)realloc(seq_list->elements,
                                                (seq_list->size + LIST_INCREMENT) * sizeof(ELEM_TYPE));
        if (!new_base) {
            return NON_ALLOCATED; // 存储分配失败
        }

        seq_list->elements = new_base;         // 新基址
        seq_list->size += LIST_INCREMENT;      // 增加存储容量
    }

    ELEM_TYPE* insert_elem = &(seq_list->elements[pos - 1]);    // q为插入位置
    for (ELEM_TYPE* p = &(seq_list->elements[seq_list->length - 1]); p >= insert_elem; p--) {
        *(p + 1) = *p; // 插入位置及之后的元素右移
    }

    *insert_elem = elem;      // 插入elem
    seq_list->length++;       // 表长增1
    return OK;
}


Status SeqListDelete(seq_list_t* seq_list, int i, ELEM_TYPE* elem) {
    // 在顺序线性表L中删除第i个元素, 并用e返回其值
    // i的合法值为1<=i<=ListLength_Sq(seq_list_t)
    if (i < 1 || i > seq_list->length) {
        return ERROR;
    }

    ELEM_TYPE* p = &(seq_list->elements[i - 1]);          // p为被删除元素的位置
    *elem = *p;                                  // 被删除元素的值赋给e
    ELEM_TYPE* q = seq_list->elements + seq_list->length - 1;    // 表尾元素的位置
    for(++p;p<=q;++p) *(p-1)=*p;              // 被删除元素之后的元素左移
    --seq_list->length;                              // 表长减1
    return OK;
}


/*!
 * @brief 顺序表查找函数
 * @param L
 * @param e
 * @param compare
 * @return
 */
int SeqListLocate(seq_list_t *L, ELEM_TYPE e,
                  int (*compare)(ELEM_TYPE, ELEM_TYPE)) {
    // 在顺序线性表L中查找第1个值与e满足compare()的元素的位序
    // 若找到, 则返回其在L中的位序, 否则返回0
    int i = 1;             // i的初值为第1个元素的位序
    ELEM_TYPE* p = L->elements;   // p的初值为第1个元素的存储位置
    while (i <= L->length && (*compare)(*p++, e) != 0) ++i;
    if (i <= L->length) return i;
    else return 0;
} // SeqListLocate


/*
void MergeList_Sq(seq_list_t *La, seq_list_t *Lb, seq_list_t *Lc) {

}
 */


void SeqListPrint(seq_list_t *L) {
    for (int i = 0; i < L->length; i++) {
        printf("%d ", L->elements[i]);
    }
}
