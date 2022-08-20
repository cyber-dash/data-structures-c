/*!
 * @file test.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 顺序表测试头文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_SEQ_LIST_TEST_H
#define CYBER_DASH_SEQ_LIST_TEST_H

#include "seq_list.h"


int compare(ELEM_TYPE item1, ELEM_TYPE item2);

// 测试线性表插入
void TestSeqListInsert();

// 测试线性表删除
void TestSeqListDelete();

// 测试线性表查找
void TestSeqListLocate();

// 测试线性表合并
void TestSeqListMerge();


#endif // CYBER_DASH_SEQ_LIST_TEST_H
