/*!
 * @file main.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief main源文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "test.h"


/*!
 * @brief main函数
 * @note
 */
int main() {

    /// - 测试静态搜索表顺序搜索
    TestStaticSearchTableSeqSearch();

    /// - 测试静态搜索表二分搜索
    TestStaticSearchTableBinarySearch();

    return 0;
}
