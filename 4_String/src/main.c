/*!
 * @file main.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 字符串main文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "test.h"

int main() {

    // 测试字符串复制
    TestStringCopy();

    // 测试字符串比较
    TestStringCompare();

    // 测试字符串拼接
    TestStringConcat();

    // 测试字符串子串
	TestStringSubStr();

    // 测试字符串插入
    TestStringInsert();

    // 测试字符串匹配(BF和KMP)
    TestStringSearch();

    return 0;
}
