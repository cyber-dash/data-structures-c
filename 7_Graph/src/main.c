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

    /// - 测试使用边和结点创建无向网
    TestCreateUDNByEdgesAndVertices();

    /// - 测试深度优先遍历(DFS)
    TestDFSTraverse();

    /// - 测试广度优先遍历(BFS)
    TestBFSTraverse();

    /// - 测试Prim算法
    TestPrim();

    /// - 测试克努斯卡尔(Kruskal)算法
    TestKruskal();

    /// - 测试迪杰斯特拉(Dijkstra)算法
    TestDijkstra();

    /// - 测试贝尔曼福特(Bellman-Ford)算法
    TestBellmanFord();

    /// - 测试弗洛伊德(Floyd)算法
    TestFloyd();

    return 0;
}
