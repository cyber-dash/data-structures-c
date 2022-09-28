/*!
 * @file test.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 图测试源文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdio.h>
#include "test.h"
#include "matrix_graph.h"
#include "algorithm.h"


/*!
 * @brief **测试使用结点数组和边数组创建无向网**
 * @note
 * 测试使用结点数组和边数组创建无向网
 * -----------------------------
 * -----------------------------
 * ```
 *           结点0
 *           / \
 *          /   \
 *        0.1   0.12
 *        /       \
 *       /         \
 *   结点1---0.2---结点2
 *       \        /
 *        \      /
 *        0.14  0.05
 *         \  /
 *          \/
 *         结点3
 * ```
 *
 * - 声明并构造 **结点索引数组** 和 **边数组**  \n
 * &emsp; 声明 **结点索引数组** \n
 * &emsp; 构造 **边数组** \n
 * - 建图 \n
 * &emsp; 声明 **邻接矩阵图** 并设置类型 \n
 * &emsp; 调用 **CreateGraphByEdgesAndVertices** 建图 \n
 * - 打印图的邻接矩阵 \n
 *
 */
void TestCreateUDNByEdgesAndVertices() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("               Test CreateGraphByEdgesAndVertices            \n");
    printf("              测试使用边(弧)数组结点数组创建无向网(UDN)           \n\n\n");
    printf("         结点0\n");
    printf("         / \\\n");
    printf("        /   \\\n");
    printf("      0.1   0.12\n");
    printf("      /       \\\n");
    printf("     /         \\\n");
    printf(" 结点1---0.2---结点2\n");
    printf("     \\        /\n");
    printf("      \\      /\n");
    printf("      0.14  0.05\n");
    printf("        \\  /\n");
    printf("         \\/\n");
    printf("       结点3\n");

    /// - 声明并构造结点数组和边数组
    VERTEX_TYPE vertices[4] = { 0, 1, 2, 3 };

    // 无向边信息, 0 - 1: 0.1,  0 - 2: 0.12,  1 - 2: 0.2,  1 - 3: 0.14,  2 - 3: 0.05
    int starting_vertex_indexes[5] = { 0, 0, 1, 1, 2 }; // 起点索引数组
    int ending_vertex_indexes[5] = { 1, 2, 2, 3, 3 };   // 终点索引数组
    double weights[5] = { 0.1, 0.12, 0.2, 0.14, 0.05 }; // 边权重索引数组

    // 使用起点索引数组, 终点索引数组, 边权重数组, 构造边数组
    edge_t edges[5];
    for (int i = 0; i < sizeof(edges) / sizeof(edge_t); i++) {
        edges[i].weight_type = DOUBLE;
        edges[i].starting_vertex_index = starting_vertex_indexes[i];
        edges[i].ending_vertex_index = ending_vertex_indexes[i];
        edges[i].weight.double_value = weights[i];
    }

    // - 声明邻接矩阵图并设置类型
    matrix_graph_t graph;
    graph.kind = UDN;       // 类型:无向网

    // - 建图
    status_t status = CreateGraphByEdgesAndVertices(&graph, edges, 5, vertices, 4, UDN);
    if (status == OK) {
        printf("建图成功, 打印:\n\n");
        status = PrintGraphMatrix(&graph);  // 打印邻接矩阵
        if (status == OK) {
            printf("打印结束\n\n");
        }
    } else {
        printf("建图失败\n\n");
    }

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}


/*!
 * @brief **测试深度优先遍历**
 * @note
 * 测试深度优先遍历
 * --------------
 * --------------
 *
 * ```
 *               结点0
 *               / \
 *              /   \
 *            0.1   0.12
 *            /       \
 *           /         \
 *       结点1---0.01---结点2
 *         / \         / \
 *        /   \       /   \
 *     0.13  0.14 0.05   0.17
 *      /      \  /        \
 *     /        \/          \
 * 结点4--0.09--结点3--0.11--结点5
 * ```
 *
 * - 声明并构造 **结点索引数组** 和 **边数组**  \n
 * &emsp; 声明 **结点索引数组** \n
 * &emsp; 构造 **边数组** \n
 * - 建图 \n
 * &emsp; 声明 **邻接矩阵图** 并设置类型 \n
 * &emsp; 调用 **CreateGraphByEdgesAndVertices** 建图 \n
 * - 测试深度有限遍历(DFS)(从结点0开始遍历) \n
 */
void TestDFSTraverse() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                     Test DFSRecursive Traverse            |\n");
    printf("|                       测试深度优先遍历                      |\n\n\n");
    printf("|                                                           |\n");
    printf("|                         结点0                              |\n");
    printf("|                         / \\                               |\n");
    printf("|                        /   \\                              |\n");
    printf("|                      0.1   0.12                           |\n");
    printf("|                      /       \\                            |\n");
    printf("|                     /         \\                           |\n");
    printf("|                 结点1---0.01---结点2                       |\n");
    printf("|                   / \\         / \\                         |\n");
    printf("|                  /   \\       /   \\                        |\n");
    printf("|               0.13  0.14   0.05   0.17                      |\n");
    printf("|                /       \\   /       \\                      |\n");
    printf("|               /         \\ /         \\                     |\n");
    printf("|            结点4--0.09--结点3--0.11--结点5                   |\n");
    printf("\n");

    int vertex_count = 6;   // 结点数量
    int edge_count = 9;     // 弧(边)数量

    // 声明结点索引数组
    int vertex_indexes[6] = { 0, 1, 2, 3, 4, 5 };

    // 边信息
    // 0 - 1: 0.1,   0 - 2: 0.12,  1 - 2: 0.2
    // 1 - 3: 0.14,  1 - 4: 0.13,  2 - 3: 0.05
    // 2 - 5: 0.17,  3 - 4: 0.09,  3 - 5: 0.11
    int starting_vertex_indexes[9] = { 0, 0, 1, 1, 1, 2, 2, 3, 3 };                 // 起点索引数组
    int ending_vertex_indexes[9] = { 1, 2, 2, 3, 4, 3, 5, 4, 5 };                   // 终点索引数组
    double weights[9] = { 0.1, 0.12, 0.01, 0.14, 0.13, 0.05, 0.17, 0.09, 0.11 };    // 边权重数组

    // 构造边数组
    edge_t edges[9];
    for (int i = 0; i < edge_count; i++) {
        edges[i].weight_type = DOUBLE;
        edges[i].starting_vertex_index = starting_vertex_indexes[i];
        edges[i].ending_vertex_index = ending_vertex_indexes[i];
        edges[i].weight.double_value = weights[i];
    }

    // 建图
    // 声明邻接矩阵图并设置类型
    matrix_graph_t graph;
    GRAPH_KIND graph_kind = UDN;            // 类型:有向网

    // 调用CreateGraphByEdgesAndVertices建图
    CreateGraphByEdgesAndVertices(&graph, edges, edge_count, vertex_indexes, vertex_count, graph_kind);

    printf("深度优先遍历:\n");

    DFSTraverse(graph, Visit);

    printf("\n-------------------- 抖音: cyberdash_yuan --------------------\n");
}


/*!
 * @brief **测试广度优先遍历**
 * @note
 * 测试广度优先遍历
 * --------------
 * --------------
 *
 * ```
 *               结点0
 *               / \
 *              /   \
 *            0.1   0.12
 *            /       \
 *           /         \
 *       结点1---0.01---结点2
 *         / \         / \
 *        /   \       /   \
 *     0.13  0.14 0.05   0.17
 *      /      \  /        \
 *     /        \/          \
 * 结点4--0.09--结点3--0.11--结点5
 * ```
 *
 * - 声明并构造 **结点索引数组** 和 **边数组**  \n
 * &emsp; 声明 **结点索引数组** \n
 * &emsp; 构造 **边数组** \n
 * - 建图 \n
 * &emsp; 声明 **邻接矩阵图** 并设置类型 \n
 * &emsp; 调用 **CreateGraphByEdgesAndVertices** 建图 \n
 * - 测试广度有限遍历(BFS)(从结点0开始遍历) \n
 *
 */
void TestBFSTraverse() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                     Test BFS Traverse                     |\n");
    printf("|                       测试广度优先遍历                      |\n\n\n");
    printf("|                                                           |\n");
    printf("|                         结点0                              |\n");
    printf("|                         / \\                               |\n");
    printf("|                        /   \\                              |\n");
    printf("|                      0.1   0.12                           |\n");
    printf("|                      /       \\                            |\n");
    printf("|                     /         \\                           |\n");
    printf("|                 结点1---0.01---结点2                       |\n");
    printf("|                   / \\         / \\                         |\n");
    printf("|                  /   \\       /   \\                        |\n");
    printf("|               0.13  0.14   0.05   0.17                      |\n");
    printf("|                /       \\   /       \\                      |\n");
    printf("|               /         \\ /         \\                     |\n");
    printf("|            结点4--0.09--结点3--0.11--结点5                   |\n");
    printf("\n");

    int vertex_count = 6;   // 结点数量
    int edge_count = 9;     // 弧(边)数量

    // 声明结点索引数组
    int vertex_indexes[6] = { 0, 1, 2, 3, 4, 5 };

    // 边信息
    // 0 - 1: 0.1,   0 - 2: 0.12,  1 - 2: 0.2
    // 1 - 3: 0.14,  1 - 4: 0.13,  2 - 3: 0.05
    // 2 - 5: 0.17,  3 - 4: 0.09,  3 - 5: 0.11
    int starting_vertex_indexes[9] = { 0, 0, 1, 1, 1, 2, 2, 3, 3 };                 // 起点索引数组
    int ending_vertex_indexes[9] = { 1, 2, 2, 3, 4, 3, 5, 4, 5 };                   // 终点索引数组
    double weights[9] = { 0.1, 0.12, 0.01, 0.14, 0.13, 0.05, 0.17, 0.09, 0.11 };    // 边权重数组

    // 构造边数组
    edge_t edges[9];
    for (int i = 0; i < edge_count; i++) {
        edges[i].weight_type = DOUBLE;
        edges[i].starting_vertex_index = starting_vertex_indexes[i];
        edges[i].ending_vertex_index = ending_vertex_indexes[i];
        edges[i].weight.double_value = weights[i];
    }

    // 建图
    // 声明邻接矩阵图并设置类型
    matrix_graph_t graph;
    GRAPH_KIND graph_kind = UDN;            // 类型:有向网

    // 调用CreateGraphByEdgesAndVertices建图
    CreateGraphByEdgesAndVertices(&graph, edges, edge_count, vertex_indexes, vertex_count, graph_kind);

    printf("广度优先遍历:\n");

    BFSTraverse(graph, Visit);

    printf("\n-------------------- 抖音: cyberdash_yuan --------------------\n");
}


/*!
 * @brief **测试(Prim)最小生成树**
 * @note
 * 测试(Prim)最小生成树
 * ------------------
 * ------------------
 *
 * ```
 *               结点0
 *               / \
 *              /   \
 *            0.1   0.12
 *            /       \
 *           /         \
 *       结点1---0.01---结点2
 *         / \         / \
 *        /   \       /   \
 *     0.13  0.14 0.05   0.17
 *      /      \  /        \
 *     /        \/          \
 * 结点4--0.09--结点3--0.11--结点5
 * ```
 *
 * - 声明并构造 **结点索引数组** 和 **边数组**  \n
 * &emsp; 声明 **结点索引数组** \n
 * &emsp; 构造 **边数组** \n
 * - 建图 \n
 * &emsp; 声明 **邻接矩阵图** 并设置类型 \n
 * &emsp; 调用 **CreateGraphByEdgesAndVertices** 建图 \n
 * - 测试Prim算法 \n
 * &emsp; 调用 **Prim** \n
 * &emsp; 打印最小生成树 \n
 *
 */
void TestPrim() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                         Test Prim                         |\n");
    printf("|                     测试(Prim)最小生成树                    |\n\n\n");
    printf("|                                                           |\n");
    printf("|                         结点0                              |\n");
    printf("|                         / \\                               |\n");
    printf("|                        /   \\                              |\n");
    printf("|                      0.1   0.12                           |\n");
    printf("|                      /       \\                            |\n");
    printf("|                     /         \\                           |\n");
    printf("|                 结点1---0.01---结点2                       |\n");
    printf("|                   / \\         / \\                         |\n");
    printf("|                  /   \\       /   \\                        |\n");
    printf("|               0.13  0.14   0.05   0.17                      |\n");
    printf("|                /       \\   /       \\                      |\n");
    printf("|               /         \\ /         \\                     |\n");
    printf("|            结点4--0.09--结点3--0.11--结点5                   |\n");
    printf("\n");

    int vertex_count = 6;   // 结点数量
    int edge_count = 9;     // 弧(边)数量

    // 声明结点索引数组
    int vertex_indexes[6] = { 0, 1, 2, 3, 4, 5 };

    // 边信息
    // 0 - 1: 0.1,   0 - 2: 0.12,  1 - 2: 0.2
    // 1 - 3: 0.14,  1 - 4: 0.13,  2 - 3: 0.05
    // 2 - 5: 0.17,  3 - 4: 0.09,  3 - 5: 0.11
    int starting_vertex_indexes[9] = { 0, 0, 1, 1, 1, 2, 2, 3, 3 };                 // 起点索引数组
    int ending_vertex_indexes[9] = { 1, 2, 2, 3, 4, 3, 5, 4, 5 };                   // 终点索引数组
    double weights[9] = { 0.1, 0.12, 0.01, 0.14, 0.13, 0.05, 0.17, 0.09, 0.11 };    // 边权重数组

    // 构造边数组
    edge_t edges[9];
    for (int i = 0; i < edge_count; i++) {
        edges[i].weight_type = DOUBLE;
        edges[i].starting_vertex_index = starting_vertex_indexes[i];
        edges[i].ending_vertex_index = ending_vertex_indexes[i];
        edges[i].weight.double_value = weights[i];
    }

    // 建图
    // 声明邻接矩阵图并设置类型
    matrix_graph_t graph;
    GRAPH_KIND graph_kind = UDN;            // 类型:有向网

    // 调用CreateGraphByEdgesAndVertices建图
    CreateGraphByEdgesAndVertices(&graph, edges, edge_count, vertex_indexes, vertex_count, graph_kind);

    MST_t min_span_node_arr;
    Prim(&graph, min_span_node_arr);

    printf("最小生成树: \n");
    PrintMinSpanTree(min_span_node_arr, graph.vertex_count - 1);

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}


/*!
 * @brief **测试克努斯卡尔(Kruskal)最小生成树**
 * @note
 * 测试克努斯卡尔(Kruskal)最小生成树
 * -----------------------------
 * -----------------------------
 *
 * ```
 *               结点0
 *               / \
 *              /   \
 *            0.1   0.12
 *            /       \
 *           /         \
 *       结点1---0.01---结点2
 *         / \         / \
 *        /   \       /   \
 *     0.13  0.14 0.05   0.17
 *      /      \  /        \
 *     /        \/          \
 * 结点4--0.09--结点3--0.11--结点5
 * ```
 *
 * - 声明并构造结点索引数组和边数组 \n
 * &emsp; 声明结点索引数组 \n
 * &emsp; 构造边数组 \n
 * - 建图 \n
 * &emsp; 声明邻接矩阵图并设置类型 \n
 * &emsp; 调用CreateGraphByEdgesAndVertices建图 \n
 * - 测试克努斯卡尔算法 \n
 * &emsp; 调用Kruskal \n
 * &emsp; 打印最小生成树 \n
 */
void TestKruskal() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                         Test Kruskal                        \n");
    printf("                  测试克努斯卡尔(Kruskal)最小生成树              \n\n\n");
    printf("|                                                           |\n");
    printf("|                         结点0                              |\n");
    printf("|                         / \\                               |\n");
    printf("|                        /   \\                              |\n");
    printf("|                      0.1   0.12                           |\n");
    printf("|                      /       \\                            |\n");
    printf("|                     /         \\                           |\n");
    printf("|                 结点1---0.01---结点2                       |\n");
    printf("|                   / \\         / \\                         |\n");
    printf("|                  /   \\       /   \\                        |\n");
    printf("|               0.13  0.14 0.05   0.17                      |\n");
    printf("|                /       \\  /        \\                      |\n");
    printf("|               /         \\/          \\                     |\n");
    printf("|           结点4--0.09--结点3--0.11--结点5                   |\n");
    printf("\n");

    int vertex_count = 6;           // 结点数量
    int edge_count = 9;           // 弧(边)数量


    // 声明并构造结点索引数组和边数组

    // 声明结点索引数组
    int vertex_indexes[6] = { 0, 1, 2, 3, 4, 5 };

    // 边信息
    // 0 - 1: 0.1,   0 - 2: 0.12,  1 - 2: 0.2
    // 1 - 3: 0.14,  1 - 4: 0.13,  2 - 3: 0.05
    // 2 - 5: 0.17,  3 - 4: 0.09,  3 - 5: 0.11
    int starting_vertex_indexes[9] = {0, 0, 1, 1, 1, 2, 2, 3, 3 };               // 起点索引数组
    int ending_vertex_indexes[9] = {1, 2, 2, 3, 4, 3, 5, 4, 5 };                 // 终点索引数组
    double weights[9] = {0.1, 0.12, 0.01, 0.14, 0.13, 0.05, 0.17, 0.09, 0.11 }; // 边权重数组

    // 构造边数组
    edge_t edges[9];
    for (int i = 0; i < edge_count; i++) {
        edges[i].weight_type = DOUBLE;
        edges[i].starting_vertex_index = starting_vertex_indexes[i];
        edges[i].ending_vertex_index = ending_vertex_indexes[i];
        edges[i].weight.double_value = weights[i];
    }

    // 建图

    // 声明邻接矩阵图并设置类型
    matrix_graph_t graph;
    GRAPH_KIND graph_kind = UDN;            // 类型:有向网

    // 调用CreateGraphByEdgesAndVertices建图
    CreateGraphByEdgesAndVertices(&graph, edges, edge_count, vertex_indexes, vertex_count, graph_kind);

    // 测试克努斯卡尔算法
    // 调用Kruskal
    MST_t min_span_tree;
    Kruskal(&graph, min_span_tree);

    // 打印最小生成树
    printf("最小生成树: \n");
    PrintMinSpanTree(min_span_tree, graph.vertex_count - 1);

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}


/*!
 * @brief **测试迪杰斯特拉(Dijkstra)最短路径**
 * @note
 * 测试迪杰斯特拉(Dijkstra)最短路径
 * -----------------------------
 * -----------------------------
 *
 * ```
 *               结点0
 *               / \
 *              /   \
 *            0.1   0.12
 *            /       \
 *           /         \
 *       结点1---0.01---结点2
 *         / \         / \
 *        /   \       /   \
 *     0.13  0.14 0.05   0.17
 *      /      \  /        \
 *     /        \/          \
 * 结点4--0.09--结点3--0.11--结点5
 * ```
 *
 * 结点0为起始节点, 求结点0到其他结点的最短路径
 *
 * - 声明并构造结点索引数组和边数组 \n
 * &emsp; 声明结点索引数组 \n
 * &emsp; 构造边数组 \n
 * - 建图 \n
 * &emsp; 声明邻接矩阵图并设置类型 \n
 * &emsp; 调用CreateGraphByEdgesAndVertices建图 \n
 * - 测试迪杰斯特拉算法 \n
 * &emsp; 声明predecessor和distance数组 \n
 * &emsp; 调用Dijkstra \n
 * &emsp; 打印单源最短路径 \n
 */
void TestDijkstra() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                        Test Dijkstra                        \n");
    printf("                 测试迪杰斯特拉(Dijkstra)最短路径               \n\n\n");
    printf("|                                                           |\n");
    printf("|                         结点0                              |\n");
    printf("|                         / \\                               |\n");
    printf("|                        /   \\                              |\n");
    printf("|                      0.1   0.12                           |\n");
    printf("|                      /       \\                            |\n");
    printf("|                     /         \\                           |\n");
    printf("|                 结点1---0.01---结点2                       |\n");
    printf("|                   / \\         / \\                         |\n");
    printf("|                  /   \\       /   \\                        |\n");
    printf("|               0.13  0.14 0.05   0.17                      |\n");
    printf("|                /       \\  /        \\                      |\n");
    printf("|               /         \\/          \\                     |\n");
    printf("|           结点4--0.09--结点3--0.11--结点5                   |\n");
    printf("\n");

    int vertex_count = 6;           // 结点数量
    int edge_count = 9;           // 弧(边)数量

    // 声明并构造结点索引数组和边数组

    // 声明结点索引数组
    int vertex_indexes[6] = { 0, 1, 2, 3, 4, 5 };

    // 边信息
    // 0 - 1: 0.1,   0 - 2: 0.12,  1 - 2: 0.2
    // 1 - 3: 0.14,  1 - 4: 0.13,  2 - 3: 0.05
    // 2 - 5: 0.17,  3 - 4: 0.09,  3 - 5: 0.11
    int starting_vertex_indexes[9] = {0, 0, 1, 1, 1, 2, 2, 3, 3 };               // 起点索引数组
    int ending_vertex_indexes[9] = {1, 2, 2, 3, 4, 3, 5, 4, 5 };                 // 终点索引数组
    double weights[9] = {0.1, 0.12, 0.01, 0.14, 0.13, 0.05, 0.17, 0.09, 0.11 }; // 边权重数组

    // 构造边数组
    edge_t edges[9];
    for (int i = 0; i < edge_count; i++) {
        edges[i].weight_type = DOUBLE;
        edges[i].starting_vertex_index = starting_vertex_indexes[i];
        edges[i].ending_vertex_index = ending_vertex_indexes[i];
        edges[i].weight.double_value = weights[i];
    }

    // 建图
    // 声明邻接矩阵图并设置类型
    matrix_graph_t graph;
    GRAPH_KIND graph_kind = UDN;            // 类型:有向网

    // 调用CreateGraphByEdgesAndVertices建图
    CreateGraphByEdgesAndVertices(&graph, edges, edge_count, vertex_indexes, vertex_count, graph_kind);

    // 迪杰斯特拉算法
    // 声明predecessor和distance数组
    int predecessor[MAX_VERTEX_CNT][MAX_VERTEX_CNT];
    path_t distance[MAX_VERTEX_CNT];
    int starting_vertex_index = 0; // 从索引0结点开始(到其他结点)

    // 调用Dijkstra
    Dijkstra(&graph, starting_vertex_index, predecessor, distance);
    // 打印单源最短路径
    PrintSingleSourceShortestPath(&graph, starting_vertex_index, predecessor, distance);

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}


/*!
 * @brief **测试贝尔曼福特(BellmanFord)最短路径**
 * @note
 * 测试贝尔曼福特(BellmanFord)最短路径
 * --------------------------------
 * --------------------------------
 *
 * ```
 *               结点0
 *               / \
 *              /   \
 *            0.1   0.12
 *            /       \
 *           /         \
 *       结点1---0.01---结点2
 *         / \         / \
 *        /   \       /   \
 *     0.13  0.14 0.05   0.17
 *      /      \  /        \
 *     /        \/          \
 * 结点4--0.09--结点3--0.11--结点5
 * ```
 *
 * 结点0为起始节点, 求结点0到其他结点的最短路径
 *
 * - 声明并构造结点索引数组和边数组 \n
 * &emsp; 声明结点索引数组 \n
 * &emsp; 构造边数组 \n
 * - 建图 \n
 * &emsp; 声明邻接矩阵图并设置类型 \n
 * &emsp; 调用CreateGraphByEdgesAndVertices建图 \n
 * - 测试贝尔曼福特(Bellman-Ford)算法 \n
 * &emsp; 声明predecessor和distance数组 \n
 * &emsp; 调用BellmanFord \n
 * &emsp; 打印单源最短路径 \n
 */
void TestBellmanFord() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                       Test BellmanFord                      \n");
    printf("                测试贝尔曼福特(BellmanFord)最短路径              \n\n\n");
    printf("|                                                           |\n");
    printf("|                         结点0                              |\n");
    printf("|                         / \\                               |\n");
    printf("|                        /   \\                              |\n");
    printf("|                      0.1   0.12                           |\n");
    printf("|                      /       \\                            |\n");
    printf("|                     /         \\                           |\n");
    printf("|                 结点1---0.01---结点2                       |\n");
    printf("|                   / \\         / \\                         |\n");
    printf("|                  /   \\       /   \\                        |\n");
    printf("|               0.13  0.14 0.05   0.17                      |\n");
    printf("|                /       \\  /        \\                      |\n");
    printf("|               /         \\/          \\                     |\n");
    printf("|           结点4--0.09--结点3--0.11--结点5                   |\n");
    printf("\n");

    int vertex_count = 6;   // 结点数量
    int edge_count = 9;     // 弧(边)数量

    // 结点索引信息
    int vertexes[6] = {0, 1, 2, 3, 4, 5 };

    // 边信息
    // 0 - 1: 0.1,   0 - 2: 0.12,  1 - 2: 0.2
    // 1 - 3: 0.14,  1 - 4: 0.13,  2 - 3: 0.05
    // 2 - 5: 0.17,  3 - 4: 0.09,  3 - 5: 0.11
    int starting_vertex_indexes[9] = {0, 0, 1, 1, 1, 2, 2, 3, 3};               // 起点索引数组
    int ending_vertex_indexes[9] = {1, 2, 2, 3, 4, 3, 5, 4, 5};                 // 终点索引数组
    double weights[9] = {0.1, 0.12, 0.01, 0.14, 0.13, 0.05, 0.17, 0.09, 0.11}; // 边权重数组

    // 构造边数组
    edge_t edges[9];
    for (int i = 0; i < edge_count; i++) {
        edges[i].weight_type = DOUBLE;
        edges[i].starting_vertex_index = starting_vertex_indexes[i];
        edges[i].ending_vertex_index = ending_vertex_indexes[i];
        edges[i].weight.double_value = weights[i];
    }

    matrix_graph_t graph;   // 邻接矩阵图
    GRAPH_KIND graph_kind = UDN;  // 类型: 无向网

    // 建图
    CreateGraphByEdgesAndVertices(&graph, edges, edge_count, vertexes, vertex_count, graph_kind);

    int predecessor[MAX_VERTEX_CNT][MAX_VERTEX_CNT];    // 前驱结点索引数组
    path_t distance[MAX_VERTEX_CNT];                    // 最短路径数组

    int starting_vertex_index = 0; // 起点索引

    BellmanFord(&graph, starting_vertex_index, predecessor, distance);  // 执行BellmanFord算法

    PrintSingleSourceShortestPath(&graph, starting_vertex_index, predecessor, distance);    // 打印

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}


/*!
 * @brief **测试弗洛伊德(Floyd-Warshall)算法**
 * @note
 * 测试弗洛伊德(Floyd-Warshall)算法
 * ------------------------------
 * ------------------------------
 *
 * ```
 *               结点0
 *               / \
 *              /   \
 *            0.1   0.12
 *            /       \
 *           /         \
 *       结点1---0.01---结点2
 *         / \         / \
 *        /   \       /   \
 *     0.13  0.14 0.05   0.17
 *      /      \  /        \
 *     /        \/          \
 * 结点4--0.09--结点3--0.11--结点5
 * ```
 *
 * - 声明并构造结点索引数组和边数组 \n
 * &emsp; 声明结点索引数组 \n
 * &emsp; 构造边数组 \n
 * - 建图 \n
 * &emsp; 声明邻接矩阵图并设置类型 \n
 * &emsp; 调用CreateGraphByEdgesAndVertices建图 \n
 * - 测试迪杰斯特拉算法 \n
 * &emsp; 声明predecessor和distance数组 \n
 * &emsp; 调用Floyd \n
 * &emsp; 打印多源最短路径 \n
 */
void TestFloyd() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                     Test Floyd-Warshall                   |\n");
    printf("|               测试弗洛伊德(Floyd-Warshall)最短路径           |\n");
    printf("|                                                           |\n");
    printf("|                         结点0                              |\n");
    printf("|                         / \\                               |\n");
    printf("|                        /   \\                              |\n");
    printf("|                      0.1   0.12                           |\n");
    printf("|                      /       \\                            |\n");
    printf("|                     /         \\                           |\n");
    printf("|                 结点1---0.01---结点2                       |\n");
    printf("|                   / \\         / \\                         |\n");
    printf("|                  /   \\       /   \\                        |\n");
    printf("|               0.13  0.14 0.05   0.17                      |\n");
    printf("|                /       \\  /        \\                      |\n");
    printf("|               /         \\/          \\                     |\n");
    printf("|           结点4--0.09--结点3--0.11--结点5                   |\n");
    printf("\n");

    int vertex_count = 6;   // 结点数量
    int edge_count = 9;     // 弧(边)数量

    // 结点索引信息
    int vertexes[6] = {0, 1, 2, 3, 4, 5 };

    // 边信息
    // 0 - 1: 0.1,   0 - 2: 0.12,  1 - 2: 0.2
    // 1 - 3: 0.14,  1 - 4: 0.13,  2 - 3: 0.05
    // 2 - 5: 0.17,  3 - 4: 0.09,  3 - 5: 0.11
    int starting_vertex_indexes[9] = {0, 0, 1, 1, 1, 2, 2, 3, 3};               // 起点索引数组
    int ending_vertex_indexes[9] = {1, 2, 2, 3, 4, 3, 5, 4, 5};                 // 终点索引数组
    double weights[9] = {0.1, 0.12, 0.01, 0.14, 0.13, 0.05, 0.17, 0.09, 0.11}; // 边权重数组

    // 构造边数组
    edge_t edges[9];
    for (int i = 0; i < edge_count; i++) {
        edges[i].weight_type = DOUBLE;
        edges[i].starting_vertex_index = starting_vertex_indexes[i];
        edges[i].ending_vertex_index = ending_vertex_indexes[i];
        edges[i].weight.double_value = weights[i];
    }

    matrix_graph_t graph;   // 邻接矩阵图
    GRAPH_KIND graph_kind = UDN;  // 类型: 无向网

    // 建图
    CreateGraphByEdgesAndVertices(&graph, edges, edge_count, vertexes, vertex_count, graph_kind);

    int predecessor[MAX_VERTEX_CNT][MAX_VERTEX_CNT];
    edge_t distance[MAX_VERTEX_CNT][MAX_VERTEX_CNT];

    for (int i = 0; i < MAX_VERTEX_CNT; i++) {
        for (int j = 0; j < MAX_VERTEX_CNT; j++) {
            distance[i][j].weight_type = DOUBLE;
        }
    }

    Floyd(&graph, predecessor, distance);
    PrintMultiSourceShortestPath(&graph, distance, predecessor);

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}
