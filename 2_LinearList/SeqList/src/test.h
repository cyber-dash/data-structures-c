/*!
 * @file test.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 顺序表 测试用例头文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_SEQ_LIST_TEST_H
#define CYBER_DASH_SEQ_LIST_TEST_H

#include "./seq_list.h"


int compare(ELEM_TYPE a, ELEM_TYPE b);

void TestSeqListInsert();
void TestSeqListDelete();
void TestSeqListLocate();
void TestSeqListMerge();


#endif // CYBER_DASH_SEQ_LIST_TEST_H
