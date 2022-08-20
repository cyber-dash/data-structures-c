/*!
 * @file main.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief main源文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "test.h"


/*!
 * @brief main函数
 * @return 0
 * - 测试线性表插入 \n
 * - 测试线性表删除 \n
 * - 测试线性表查找 \n
 * - 测试线性表合并 \n
 */
int main() {

    TestSeqListInsert();

    TestSeqListDelete();

    TestSeqListLocate();

    TestSeqListMerge();

    return 0;
}
