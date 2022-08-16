/*!
 * @file seq_list.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 顺序表头文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_SEQ_LIST_H
#define CYBER_DASH_SEQ_LIST_H

#include "common.h"


/*! @brief 线性表 */
typedef struct {
    ELEM_TYPE* elements;    //!< 元素数组
    int length;             //!< 长度
    int capacity;           //!< 容量
} seq_list_t;


status_t SeqListInit(seq_list_t* seq_list);

status_t SeqListInsert(seq_list_t* seq_list, int pos, ELEM_TYPE elem);

status_t SeqListDelete(seq_list_t* seq_list, int pos, ELEM_TYPE* elem);

int SeqListLocate(seq_list_t* seq_list, ELEM_TYPE elem, int (*compare)(ELEM_TYPE, ELEM_TYPE));

status_t SeqListMerge(seq_list_t* list_a, seq_list_t* list_b, seq_list_t* merged_list);

void SeqListPrint(seq_list_t* seq_list);


#endif // CYBER_DASH_SEQ_LIST_H
