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
 * @brief **main函数**
 * @return 0
 * @note
 */
int main() {

    // - 测试循环队列入队/出队
    TestCircularQueueEnQueueAndDeQueue();

    // - 测试链式队列入队/出队
    TestLinkQueueEnQueueAndDeQueue();

    return 0;
}
