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


/*! @brief main函数 */
int main() {

    /*
    /// - 测试使用边和结点创建无向网
    TestCreateUDNByEdgesAndVertices();

    /// - 测试深度优先遍历
    TestDFSTraverse();

    /// - 测试广度有限遍历
    TestBFSTraverse();
     */

    /// - 测试Prim算法
    TestPrim();

    /*
    /// - 测试克努斯卡尔算法
    TestKruskal();

    /// - 测试迪杰斯特拉算法
    TestDijkstra();

    /// - 测试贝尔曼福特算法
    TestBellmanFord();

    /// - 测试弗洛伊德算法
    TestFloyd();
     */

    return 0;
}
