/*!
 * @file test.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 图测试头文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */
#ifndef CYBER_DASH_GRAPH_TEST_H
#define CYBER_DASH_GRAPH_TEST_H


#include "matrix_graph.h"
#include "algorithm.h"
#include "min_priority_queue.h"


// 测试使用弧(边)数组建造无向网
void TestCreateUDNByEdgesAndVertices();

// 测试深度优先遍历
void TestDFSTraverse();

// 测试广度优先遍历
void TestBFSTraverse();

// 测试(Prim)最小生成树
void TestPrim();

// 测试克努斯卡尔(Kruskal)最小生成树
void TestKruskal();

// 测试迪杰斯特拉(Dijkstra)(单源)最短路径
void TestDijkstra();

// 测试贝尔曼福特(BellmanFord)(单源)最短路径
void TestBellmanFord();

// 测试弗洛伊德(Floyd)(多源)最短路径
void TestFloyd();


#endif // CYBER_DASH_GRAPH_TEST_H
