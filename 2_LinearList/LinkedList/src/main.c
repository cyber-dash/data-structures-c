/*!
 * @file main.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief main源文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "./test.h"


/*!
 * @brief main函数
 * @note
 * - 测试链表创建
 * - 测试链表获取结点元素
 * - 测试链表删除结点
 * - 测试链表插入结点
 * - 测试有序链表合并
 */
int main() {

    // 测试链表创建
    TestLinkedListCreate();

    // 测试链表获取结点元素
    TestLinkedListGetElem();

    // 测试链表删除结点
    TestLinkedListDelete();

    // 测试链表插入结点
    TestLinkedListInsert();

    // 测试有序链表合并
    TestLinkedListMerge();

    return 0;
}
