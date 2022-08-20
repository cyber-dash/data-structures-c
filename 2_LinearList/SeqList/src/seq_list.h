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


/*!
 * @brief **线性表**
 * @note
 * <h1>线性表</h1>
 */
typedef struct {
    ELEM_TYPE* elements;    //!< 元素数组
    int length;             //!< 长度
    int capacity;           //!< 容量
} seq_list_t;


// 顺序表初始化
status_t SeqListInit(seq_list_t* seq_list);

// 顺序表插入
status_t SeqListInsert(seq_list_t* seq_list, int pos, ELEM_TYPE elem);

// 顺序表删除元素
status_t SeqListDelete(seq_list_t* seq_list, int pos, ELEM_TYPE* elem);

// 顺序表查找
int SeqListLocate(seq_list_t* seq_list, ELEM_TYPE elem, int (*compare)(ELEM_TYPE, ELEM_TYPE));

// 顺序表的合并
status_t SeqListMerge(seq_list_t* list_a, seq_list_t* list_b, seq_list_t* merged_list);

// 顺序表打印
void SeqListPrint(seq_list_t* seq_list);


#endif // CYBER_DASH_SEQ_LIST_H
