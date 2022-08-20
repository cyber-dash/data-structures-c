/*!
 * @file seq_list.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 顺序表源文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdlib.h>
#include <stdio.h>
#include "seq_list.h"


/*!
 * <h1>顺序表初始化</h1>
 * @param seq_list **顺序表**(指针)
 * @return **是否成功**
 * @note
 */
status_t SeqListInit(seq_list_t* seq_list) {

    /// - 分配elements数组内存 \n
    /// &emsp; **if** 内存分配失败 : \n
    /// &emsp;&emsp; 返回NON_ALLOCATED \n
    seq_list->elements = (ELEM_TYPE*)malloc(LIST_INIT_CAPACITY * sizeof(ELEM_TYPE));
    if (!seq_list->elements) {
        return NON_ALLOCATED;
    }

    /// - 设置length和capacity \n
    /// &emsp; length初始化为0 \n
    /// &emsp; capacity初始化为0 \n
    seq_list->length = 0;               // 空表长度为0
    seq_list->capacity = LIST_INIT_CAPACITY;    // 初始存储容量

    return OK;
}


/*!
 * <h1>顺序表插入</h1>
 * @param seq_list **顺序表**(指针)
 * @param pos **插入位置(前)**
 * @param elem **待插入元素**
 * @return **执行结果**
 * @note
 * 本顺序表实现, 索引从1开始, 区别于数组的从0开始; \n
 * 插入到参数pos的前一位置 \n
 */
status_t SeqListInsert(seq_list_t* seq_list, int pos, ELEM_TYPE elem) {

    /// - 插入位置合法性判断 \n
    /// &emsp; **if** 插入位置 < 1 或者 插入位置 > 长度 + 1 : \n
    /// &emsp;&emsp; 返回OVERFLOW \n
    if (pos < 1 || pos > seq_list->length + 1) {
        return OVERFLOW;
    }

    /// - 满容量处理 \n
    /// &emsp; **if** 线性表的容量已满(不扩容无法插入) : \n
    if (seq_list->length >= seq_list->capacity) {
        /// &emsp;&emsp; 使用增量LIST_INCREMENT计算新的容量, 并分配新的elements数组内存 \n
        unsigned int new_capacity = (seq_list->capacity + LIST_INCREMENT) * sizeof(ELEM_TYPE);
        ELEM_TYPE* new_elements = (ELEM_TYPE*)realloc(seq_list->elements, new_capacity);
        /// &emsp;&emsp; **if** 内存分配失败 : \n
        if (!new_elements) {
            /// &emsp;&emsp;&emsp; 返回NON_ALLOCATED \n
            return NON_ALLOCATED; // 存储分配失败
        }

        /// &emsp;&emsp; 顺序表elements指针指向新数组 \n
        seq_list->elements = new_elements;         // 新基址
        /// &emsp;&emsp; 顺序表capacity增加容量数值 \n
        seq_list->capacity += LIST_INCREMENT;      // 增加存储容量
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
 * @brief 顺序表删除元素
 * @param seq_list **顺序表**(指针)
 * @param pos **被删除结点所在位置**
 * @param elem **被删除结点的保存变量**
 * @return **执行结果**
 * @note
 * 顺序表删除元素
 * ------------
 * ------------
 *
 * - 删除节点位置正确性检查 \n
 * &emsp;**if** pos < 1 或者 pos > 线性表长度 : \n
 * &emsp;&emsp; 返回OVERFLOW \n
 * - 被删除结点的值赋给保存变量 \n
 * - 被删除结点后面的所有结点向前移动补位 \n
 * &emsp; **for loop** 被删除节点后侧所有所有结点 : \n
 * &emsp;&emsp; 当前结点值赋给前一节点 \n
 */
status_t SeqListDelete(seq_list_t* seq_list, int pos, ELEM_TYPE* elem) {
    if (pos < 1 || pos > seq_list->length) {
        return OVERFLOW;
    }

    // 待删除节点值赋给保存变量
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
status_t SeqListMerge(seq_list_t* list_a, seq_list_t* list_b, seq_list_t* merged_list) {
    ELEM_TYPE* list_a_cur = list_a->elements;   // list_a_cur指针 -> 顺序表a的elements数组首地址
    ELEM_TYPE* list_b_cur = list_b->elements;   // list_b_cur指针 -> 顺序表b的elements数组首地址
    ELEM_TYPE* list_a_last = list_a->elements + list_a->length - 1; // last_a_last指针 -> 顺序表a的elements数组尾地址
    ELEM_TYPE* list_b_last = list_b->elements + list_b->length - 1; // last_b_last指针 -> 顺序表b的elements数组尾地址

    // 合并后的表
    merged_list->length = list_a->length + list_b->length;  // 长度
    merged_list->capacity = list_a->capacity + list_b->capacity;        // 容量
    merged_list->elements = (ELEM_TYPE*)malloc(merged_list->capacity * sizeof(ELEM_TYPE));  // elements数组分配内存
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
