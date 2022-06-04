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

    seq_list->length = 0;               // 空表长度为0
    seq_list->size = LIST_INIT_SIZE;    // 初始存储容量

    return OK;
}


/*!
 * 顺序表插入
 * @param seq_list 顺序表(指针)
 * @param pos 插入位置
 * @param elem 元素
 * @return 是否成功
 */
Status SeqListInsert(seq_list_t* seq_list, int pos, ELEM_TYPE elem) {
    if (pos < 1 || pos > seq_list->length + 1) {
        return ERROR;
    }

    // 当前存储空间已满, 增加分配
    if (seq_list->length >= seq_list->size) {
        unsigned int new_size = (seq_list->size + LIST_INCREMENT) * sizeof(ELEM_TYPE);
        ELEM_TYPE* new_base = (ELEM_TYPE*)realloc(seq_list->elements, new_size);
        if (!new_base) {
            return NON_ALLOCATED; // 存储分配失败
        }

        seq_list->elements = new_base;         // 新基址
        seq_list->size += LIST_INCREMENT;      // 增加存储容量
    }

    ELEM_TYPE* insert_pos_elem = &(seq_list->elements[pos - 1]);    // q为插入位置
    for (ELEM_TYPE* cur = &(seq_list->elements[seq_list->length - 1]); cur >= insert_pos_elem; cur--) {
        *(cur + 1) = *cur; // 插入位置及之后的元素, 依次右移
    }

    *insert_pos_elem = elem;  // 插入elem
    seq_list->length++;       // 表长增1

    return OK;
}


/*!
 * 顺序表删除元素
 * @param seq_list 顺序表(指针)
 * @param pos 待删除元素所在位置
 * @param elem 保存删除元素值的变量
 * @return 是否删除成功
 * @note
 * 删除位置pos的元素, 将其值赋给elem
 */
Status SeqListDelete(seq_list_t* seq_list, int pos, ELEM_TYPE* elem) {
    if (pos < 1 || pos > seq_list->length) {
        return ERROR;
    }

    ELEM_TYPE* delete_pos_elem = &(seq_list->elements[pos - 1]);
    *elem = *delete_pos_elem;                                           // 被删除元素的值赋给elem

    ELEM_TYPE* last_elem = seq_list->elements + seq_list->length - 1;   // 表尾元素的位置
    for (ELEM_TYPE* cur = delete_pos_elem + 1; cur <= last_elem; cur++) {
        *(cur - 1) = *cur;
    }

    seq_list->length--;                              // 表长减1

    return OK;
}


/*!
 * @brief 顺序表查找函数
 * @param seq_list 顺序表(指针)
 * @param elem 元素值
 * @param compare 比较函数
 * @return 元素位置
 * @note
 * 如果没有该元素, 则返回0, 否则返回所在位置(首元素从1开始)
 */
int SeqListLocate(seq_list_t* seq_list, ELEM_TYPE elem, int (*compare)(ELEM_TYPE, ELEM_TYPE)) {
    int pos = 1;                            // pos为第1个元素的位置
    ELEM_TYPE* cur = seq_list->elements;    // cur指向第1个元素的存储位置

    while (pos <= seq_list->length && (*compare)(*cur, elem) != 0) {
        pos++;
        cur++;
    }

    if (pos <= seq_list->length) {
        return pos;
    }

    return 0;
}


/*!
 * 顺序表的合并
 * @param list_a 顺序表a(的指针)
 * @param list_b 顺序表b(的指针)
 * @param merged_list 合并后的表(的指针)
 * @return 是否合并成功
 */
Status SeqListMerge(seq_list_t* list_a, seq_list_t* list_b, seq_list_t* merged_list) {
    ELEM_TYPE* list_a_cur = list_a->elements;   // list_a_cur指针 -> 顺序表a的elements数组首地址
    ELEM_TYPE* list_b_cur = list_b->elements;   // list_b_cur指针 -> 顺序表b的elements数组首地址
    ELEM_TYPE* list_a_last = list_a->elements + list_a->length - 1; // last_a_last指针 -> 顺序表a的elements数组尾地址
    ELEM_TYPE* list_b_last = list_b->elements + list_b->length - 1; // last_b_last指针 -> 顺序表b的elements数组尾地址

    // 合并后的表
    merged_list->length = list_a->length + list_b->length;  // 长度
    merged_list->size = list_a->size + list_b->size;        // 容量
    merged_list->elements = (ELEM_TYPE*)malloc(merged_list->size * sizeof(ELEM_TYPE));  // elements数组分配内存
    if (!merged_list->elements) {
        return NON_ALLOCATED;   // 分配失败
    }

    ELEM_TYPE* merged_list_cur = merged_list->elements; // merged_list_cur指针 -> 合并后的顺序表的elements数组首地址

    // 执行合并
    while (list_a_cur <= list_a_last && list_b_cur <=list_b_last) {
        // list_a_cur和list_b_cur指向的两个元素, 选择较小的进入merged_list, 对应的cur指针向后移一位, merged_list_cur向后移一位
        if (*list_a_cur <= *list_b_cur) {
            *merged_list_cur = *list_a_cur;
            list_a_cur++;
        } else {
            *merged_list_cur = *list_b_cur;
            list_b_cur++;
        }
        merged_list_cur++;
    }

    // list_a剩余元素加到merged_list尾部(如果list_a有剩余)
    while (list_a_cur <= list_a_last) {
        *merged_list_cur = *list_a_cur;
        merged_list_cur++;
        list_a_cur++;
    }

    // list_b剩余元素加到merged_list尾部(如果list_b有剩余)
    while (list_b_cur <= list_b_last) {
        *merged_list_cur = *list_b_cur;
        merged_list_cur++;
        list_b_cur++;
    }

    return OK;
}


/*!
 * 打印顺序表
 * @param seq_list 顺序表(指针)
 */
void SeqListPrint(seq_list_t* seq_list) {
    for (int i = 0; i < seq_list->length; i++) {
        printf("%d ", seq_list->elements[i]);
    }
}
