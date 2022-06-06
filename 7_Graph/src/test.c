//
// Created by cyberdash@163.com on 2022/4/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "test.h"


/*!
 * 测试使用弧(边)数组创建无向网(UDN)
 * @note:
             结点0
             / \
            /   \
          0.1   0.12
          /       \
         /         \
     结点1---0.2---结点2
         \        /
          \      /
          0.14  0.05
           \  /
            \/
           结点3
 */
void TestCreateUDNByArcCellArr() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                  Test CreateUDNByArcCellArr                 \n");
    printf("                 测试使用弧(边)数组创建无向网(UDN)               \n\n\n");
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

    VERTEX_TYPE vertices[4] = {0, 1, 2, 3};

    matrix_graph_t G;
    G.vertex_count = 4;   // 结点数量
    G.edge_count = 5;   // 弧(边)数量
    G.kind = UDN;   // 类型:无向网

    // 结点信息写到G.vexs数组
    for (int i = 0; i < sizeof(vertices) / sizeof(VERTEX_TYPE); i++) {
        G.vertices[i] = vertices[i];
    }

    // 弧(边)信息, 注意没有方向
    // 0 - 1: 0.1
    // 0 - 2: 0.12
    // 1 - 2: 0.2
    // 1 - 3: 0.14
    // 2 - 3: 0.05
    int startingVertexIndexArr[5] = { 0, 0, 1, 1, 2 }; // 起点
    int endingVertexIndexArr[5] = { 1, 2, 2, 3, 3 };   // 终点
    double weightArr[5] = { 0.1, 0.12, 0.2, 0.14, 0.05 }; // 权重

    // 使用起点(索引)数组, 终点(索引)数组, 权重数组, 构造弧(边)数组
    edge_t arcCellArr[5];
    for (int i = 0; i < sizeof(arcCellArr) / sizeof(edge_t); i++) {
        arcCellArr[i].weight_type = DOUBLE;
        arcCellArr[i].edge_info = (edge_info_t*)malloc(sizeof(edge_info_t));
        arcCellArr[i].edge_info->starting_vertex_idx = startingVertexIndexArr[i];
        arcCellArr[i].edge_info->ending_vertex_idx = endingVertexIndexArr[i];
        arcCellArr[i].edge_info->value.double_value = weightArr[i];
    }

    // 建图, 如果成功则打印
    Status status = CreateUDNByArcCellArr(&G, arcCellArr, 5, vertices, 4);
    if (status == OK) {
        printf("建图成功, 打印:\n\n");
        status = PrintGraphMatrix(&G, DOUBLE);
        if (status == OK) {
            printf("打印结束\n\n");
        }
    } else {
        printf("建图失败\n\n");
    }

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}


/*!
 * 测试深度优先遍历
 * @note:
             结点0
             / \
            /   \
          0.1   0.12
          /       \
         /         \
     结点1---0.2---结点2
         \        /
          \      /
          0.14  0.05
           \  /
            \/
           结点3

   从结点0开始遍历
 */
void TestDFSTraverse() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                      Test DFS Traverse                      \n");
    printf("                        测试深度优先遍历                       \n\n\n");
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

    VERTEX_TYPE vertices[4] = {0, 1, 2, 3};

    matrix_graph_t G;
    G.weight_type = DOUBLE;
    G.vertex_count = 4;   // 结点数量
    G.edge_count = 5;   // 弧(边)数量
    G.kind = UDN;   // 类型:无向网

    // 结点信息写到G.vexs数组
    for (int i = 0; i < sizeof(vertices) / sizeof(VERTEX_TYPE); i++) {
        G.vertices[i] = vertices[i];
    }

    // 弧(边)信息, 注意没有方向
    // 0 - 1: 0.1
    // 0 - 2: 0.12
    // 1 - 2: 0.2
    // 1 - 3: 0.14
    // 2 - 3: 0.05
    int startingVertexIndexArr[5] = { 0, 0, 1, 1, 2 }; // 起点
    int endingVertexIndexArr[5] = { 1, 2, 2, 3, 3 };   // 终点
    double weightArr[5] = { 0.1, 0.12, 0.2, 0.14, 0.05 }; // 权重

    // 使用起点(索引)数组, 终点(索引)数组, 权重数组, 构造弧(边)数组
    edge_t arcCellArr[5];
    for (int i = 0; i < sizeof(arcCellArr) / sizeof(edge_t); i++) {
        arcCellArr[i].weight_type = DOUBLE;
        arcCellArr[i].edge_info = (edge_info_t*)malloc(sizeof(edge_info_t));
        arcCellArr[i].edge_info->starting_vertex_idx = startingVertexIndexArr[i];
        arcCellArr[i].edge_info->ending_vertex_idx = endingVertexIndexArr[i];
        arcCellArr[i].edge_info->value.double_value = weightArr[i];
    }

    printf("深度优先遍历:\n");

    DFSTraverse(G, Visit);

    printf("\n-------------------- 抖音: cyberdash_yuan --------------------\n");
}


/*!
 * 测试广度优先遍历
 * @note:
             结点0
             / \
            /   \
          0.1   0.12
          /       \
         /         \
     结点1---0.2---结点2
         \        /
          \      /
          0.14  0.05
           \  /
            \/
           结点3

   从结点0开始遍历
 */
void TestBFSTraverse() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                      Test BFS Traverse                      \n");
    printf("                        测试广度优先遍历                       \n\n\n");
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

    VERTEX_TYPE vertices[4] = {0, 1, 2, 3};

    matrix_graph_t G;
    G.vertex_count = 4;   // 结点数量
    G.edge_count = 5;   // 弧(边)数量
    G.kind = UDN;   // 类型:无向网

    // 结点信息写到G.vexs数组
    for (int i = 0; i < sizeof(vertices) / sizeof(VERTEX_TYPE); i++) {
        G.vertices[i] = vertices[i];
    }

    // 弧(边)信息, 注意没有方向
    // 0 - 1: 0.1
    // 0 - 2: 0.12
    // 1 - 2: 0.2
    // 1 - 3: 0.14
    // 2 - 3: 0.05
    int startingVertexIndexArr[5] = { 0, 0, 1, 1, 2 }; // 起点
    int endingVertexIndexArr[5] = { 1, 2, 2, 3, 3 };   // 终点
    double weightArr[5] = { 0.1, 0.12, 0.2, 0.14, 0.05 }; // 权重

    // 使用起点(索引)数组, 终点(索引)数组, 权重数组, 构造弧(边)数组
    edge_t arcCellArr[5];
    for (int i = 0; i < sizeof(arcCellArr) / sizeof(edge_t); i++) {
        arcCellArr[i].weight_type = DOUBLE;
        arcCellArr[i].edge_info = (edge_info_t*)malloc(sizeof(edge_info_t));
        arcCellArr[i].edge_info->starting_vertex_idx = startingVertexIndexArr[i];
        arcCellArr[i].edge_info->ending_vertex_idx = endingVertexIndexArr[i];
        arcCellArr[i].edge_info->value.double_value = weightArr[i];
    }

    printf("广度优先遍历:\n");

    BFSTraverse(G, Visit);

    printf("\n-------------------- 抖音: cyberdash_yuan --------------------\n");
}


void TestBuildHeap() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                        Test BuildHeap                       \n");
    printf("                           测试建堆                           \n\n\n");

    min_span_node_arr_t minSpanNodeArr;

    min_span_node_t minSpanNode1;
    minSpanNode1.weight_type = DOUBLE;
    minSpanNode1.weight.double_value = 0.4;
    minSpanNode1.starting_vertex_idx = 0;
    minSpanNode1.ending_vertex_idx = 1;

    min_span_node_t minSpanNode2;
    minSpanNode2.weight_type = DOUBLE;
    minSpanNode2.weight.double_value = 0.2;
    minSpanNode2.starting_vertex_idx = 0;
    minSpanNode2.ending_vertex_idx = 2;

    min_span_node_t minSpanNode3;
    minSpanNode3.weight_type = DOUBLE;
    minSpanNode3.weight.double_value = 0.5;
    minSpanNode3.starting_vertex_idx = 1;
    minSpanNode3.ending_vertex_idx = 2;

    min_span_node_t minSpanNode4;
    minSpanNode4.weight_type = DOUBLE;
    minSpanNode4.weight.double_value = 0.3;
    minSpanNode4.starting_vertex_idx = 0;
    minSpanNode4.ending_vertex_idx = 3;

    min_span_node_t minSpanNode5;
    minSpanNode5.weight_type = DOUBLE;
    minSpanNode5.weight.double_value = 0.1;
    minSpanNode5.starting_vertex_idx = 1;
    minSpanNode5.ending_vertex_idx = 3;

    minSpanNodeArr[1] =  minSpanNode1;
    minSpanNodeArr[2] =  minSpanNode2;
    minSpanNodeArr[3] =  minSpanNode3;
    minSpanNodeArr[4] =  minSpanNode4;
    minSpanNodeArr[5] =  minSpanNode5;

    printf("建堆前的最小生成树结点数组:\n");
    for (int i = 1; i <= 5; i++) {
        printf("%lf ", minSpanNodeArr[i].weight.double_value);
    }
    printf("\n");

    BuildHeap(minSpanNodeArr, 5);

    printf("建堆后的最小生成树结点数组:\n");
    for (int i = 1; i <= 5; i++) {
        printf("%lf ", minSpanNodeArr[i].weight.double_value);
    }
    printf("\n");

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}


/*!
 * 测试(Prim)最小生成树
 */
void TestPrim() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                          Test Prim                          \n");
    printf("                      测试(Prim)最小生成树                     \n\n\n");

    VERTEX_TYPE vertices[4] = {0, 1, 2, 3 };

    matrix_graph_t G;
    G.vertex_count = 4;   // 结点数量
    G.edge_count = 5;   // 弧(边)数量
    G.kind = DN;
    G.weight_type = DOUBLE;

    // 结点信息写到G.vexs数组
    for (int i = 0; i < G.vertex_count; i++) {
        G.vertices[i] = vertices[i];

        for (int j = 0; j < G.vertex_count; j++) {
            G.adj_matrix[i][j].weight_type = DOUBLE;
            G.adj_matrix[i][j].edge_info = (edge_info_t*)malloc(sizeof(edge_info_t));
            G.adj_matrix[i][j].edge_info->value.double_value = DBL_MAX;
        }
    }

    // 0 - 1: 0.1
    // 0 - 2: 0.12
    // 1 - 2: 0.01
    // 1 - 3: 0.14
    // 2 - 3: 0.05
    int startingVertexIndexArr[5] = { 0, 0, 1, 1, 2 }; // 起点
    int endingVertexIndexArr[5] = { 1, 2, 2, 3, 3 };   // 终点
    double weightArr[5] = { 0.1, 0.12, 0.01, 0.14, 0.05 }; // 权重

    // 使用起点(索引)数组, 终点(索引)数组, 权重数组, 构造弧(边)数组
    for (int i = 0; i < G.edge_count; i++) {
        int curRowIdx = startingVertexIndexArr[i];
        int curColIdx = endingVertexIndexArr[i];
        G.adj_matrix[curRowIdx][curColIdx].weight_type = DOUBLE;
        G.adj_matrix[curRowIdx][curColIdx].edge_info = (edge_info_t*)malloc(sizeof(edge_info_t));
        G.adj_matrix[curRowIdx][curColIdx].edge_info->starting_vertex_idx = startingVertexIndexArr[i];
        G.adj_matrix[curRowIdx][curColIdx].edge_info->ending_vertex_idx = endingVertexIndexArr[i];
        G.adj_matrix[curRowIdx][curColIdx].edge_info->value.double_value = weightArr[i];
    }

    min_span_node_arr_t minSpanNodeArr;
    Prim(&G, 0, minSpanNodeArr);

    printf("最小生成树: \n");
    PrintMinSpanTree(minSpanNodeArr, G.vertex_count - 1);

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}

/*!
 * 测试克努斯卡尔(Kruskal)最小生成树
 */
void TestKruskal() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                         Test Kruskal                        \n");
    printf("                  测试克努斯卡尔(Kruskal)最小生成树              \n\n\n");

    VERTEX_TYPE vertices[4] = {0, 1, 2, 3};

    matrix_graph_t G;
    G.vertex_count = 4;   // 结点数量
    G.edge_count = 5;   // 弧(边)数量
    G.kind = UDN;   // 类型:无向网
    G.weight_type = DOUBLE;

    // 结点信息写到G.vexs数组
    for (int i = 0; i < G.vertex_count; i++) {
        G.vertices[i] = vertices[i];

        for (int j = 0; j < G.vertex_count; j++) {
            G.adj_matrix[i][j].weight_type = DOUBLE;
            G.adj_matrix[i][j].edge_info = (edge_info_t*)malloc(sizeof(edge_info_t));
            G.adj_matrix[i][j].edge_info->value.double_value = DBL_MAX;
        }
    }

    // 0 - 1: 0.1
    // 0 - 2: 0.12
    // 1 - 2: 0.01
    // 1 - 3: 0.14
    // 2 - 3: 0.05
    int startingVertexIndexArr[5] = { 0, 0, 1, 1, 2 }; // 起点
    int endingVertexIndexArr[5] = { 1, 2, 2, 3, 3 };   // 终点
    double weightArr[5] = { 0.1, 0.12, 0.01, 0.14, 0.05 }; // 权重

    // 使用起点(索引)数组, 终点(索引)数组, 权重数组, 构造弧(边)数组
    for (int i = 0; i < G.edge_count; i++) {
        int curRowIdx = startingVertexIndexArr[i];
        int curColIdx = endingVertexIndexArr[i];
        G.adj_matrix[curRowIdx][curColIdx].weight_type = DOUBLE;
        G.adj_matrix[curRowIdx][curColIdx].edge_info = (edge_info_t*)malloc(sizeof(edge_info_t));
        G.adj_matrix[curRowIdx][curColIdx].edge_info->starting_vertex_idx = startingVertexIndexArr[i];
        G.adj_matrix[curRowIdx][curColIdx].edge_info->ending_vertex_idx = endingVertexIndexArr[i];
        G.adj_matrix[curRowIdx][curColIdx].edge_info->value.double_value = weightArr[i];
    }

    min_span_node_arr_t minSpanNodeArr;
    Kruskal(&G, minSpanNodeArr);

    printf("最小生成树: \n");
    PrintMinSpanTree(minSpanNodeArr, G.vertex_count - 1);

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}


/*!
 * 测试迪杰斯特拉(Dijkstra)最短路径
 * @note:
              结点0
              / \
             /   \
           0.1   0.12
           /       \
          /         \
      结点1---0.01---结点2
        / \        / \
       /   \      /   \
    0.13  0.14 0.05   0.17
     /      \  /        \
    /        \/          \
结点4--0.09--结点3--0.11--结点5

   结点0为起始节点, 求结点0到其他结点的最短路径
 */
void TestDijkstra() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                        Test Dijkstra                        \n");
    printf("                 测试迪杰斯特拉(Dijkstra)最短路径               \n\n\n");

    VERTEX_TYPE vertices[6] = {0, 1, 2, 3, 4, 5};

    matrix_graph_t G;
    G.vertex_count = 6;           // 结点数量
    G.edge_count = 9;           // 弧(边)数量
    G.kind = DN;            // 类型:有向网
    G.weight_type = DOUBLE;  // 弧(边)权值类型

    // 弧(边)信息, 注意有方向
    // 0 - 1: 0.1,   0 - 2: 0.12,  1 - 2: 0.2
    // 1 - 3: 0.14,  1 - 4: 0.13,  2 - 3: 0.05
    // 2 - 5: 0.17,  3 - 4: 0.09,  3 - 5: 0.11
    int startingVertexIndexArr[9] = { 0, 0, 1, 1, 1, 2, 2, 3, 3}; // 起点
    int endingVertexIndexArr[9] = { 1, 2, 2, 3, 4, 3, 5, 4, 5};   // 终点
    double weightArr[9] = { 0.1, 0.12, 0.01, 0.14, 0.13, 0.05, 0.17, 0.09, 0.11}; // 权重

    // 对每个[i, j]进行初始化, 默认没有弧(边), 所有的弧(边)长为最大值
    for (int i = 0; i < G.vertex_count; i++) {
        G.vertices[i] = vertices[i];
        for (int j = 0; j < G.vertex_count; j++) {
            G.adj_matrix[i][j].weight_type = DOUBLE;
            G.adj_matrix[i][j].edge_info = (edge_info_t*)malloc(sizeof(edge_info_t));
            G.adj_matrix[i][j].edge_info->starting_vertex_idx = i;
            G.adj_matrix[i][j].edge_info->ending_vertex_idx = j;
            G.adj_matrix[i][j].edge_info->value.double_value = DBL_MAX;
        }
    }

    for (int i = 0; i < G.edge_count; i++) {
        int curRowIdx = startingVertexIndexArr[i];
        int curColIdx = endingVertexIndexArr[i];
        G.adj_matrix[curRowIdx][curColIdx].edge_info->starting_vertex_idx = startingVertexIndexArr[i];
        G.adj_matrix[curRowIdx][curColIdx].edge_info->ending_vertex_idx = endingVertexIndexArr[i];
        G.adj_matrix[curRowIdx][curColIdx].edge_info->value.double_value = weightArr[i];
    }

    int P[MAX_VERTEX_CNT][MAX_VERTEX_CNT];
    edge_t D[MAX_VERTEX_CNT];
    int v0 = 0; // 从索引0结点开始(到其他结点)

    // D初始化
    for (int i = 0; i < MAX_VERTEX_CNT; i++) {
        D[i].weight_type = DOUBLE;
        D[i].edge_info = (edge_info_t*)malloc(sizeof(edge_info_t));

        D[i].edge_info->starting_vertex_idx = 0;
        D[i].edge_info->ending_vertex_idx = i;
        D[i].edge_info->value.double_value = DBL_MAX;
    }

    ShortestPath_Dijkstra(&G, v0, P, D);
    PrintSingleSourceShortestPath(&G, v0, P, D);

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}


/*!
 * 测试贝尔曼福特(BellmanFord)最短路径
 * @note:
              结点0
              / \
             /   \
           0.1   0.12
           /       \
          /         \
      结点1---0.01---结点2
        / \        / \
       /   \      /   \
    0.13  0.14 0.05   0.17
     /      \  /        \
    /        \/          \
结点4--0.09--结点3--0.11--结点5

   结点0为起始节点
 */
void TestBellmanFord() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                       Test BellmanFord                      \n");
    printf("                测试贝尔曼福特(BellmanFord)最短路径              \n\n\n");

    VERTEX_TYPE vertices[6] = {0, 1, 2, 3, 4, 5};

    matrix_graph_t G;
    G.vertex_count = 6;           // 结点数量
    G.edge_count = 9;           // 弧(边)数量
    G.kind = DN;            // 类型:有向网
    G.weight_type = DOUBLE;  // 弧(边)权值类型

    // 弧(边)信息, 注意有方向
    // 0 - 1: 0.1,   0 - 2: 0.12,  1 - 2: 0.2
    // 1 - 3: 0.14,  1 - 4: 0.13,  2 - 3: 0.05
    // 2 - 5: 0.17,  3 - 4: 0.09,  3 - 5: 0.11
    int startingVertexIndexArr[9] = { 0, 0, 1, 1, 1, 2, 2, 3, 3}; // 起点
    int endingVertexIndexArr[9] = { 1, 2, 2, 3, 4, 3, 5, 4, 5};   // 终点
    double weightArr[9] = { 0.1, 0.12, 0.01, 0.14, 0.13, 0.05, 0.17, 0.09, 0.11}; // 权重

    // 对每个[i, j]进行初始化, 默认没有弧(边), 所有的弧(边)长为最大值
    for (int i = 0; i < G.vertex_count; i++) {
        G.vertices[i] = vertices[i];
        for (int j = 0; j < G.vertex_count; j++) {
            G.adj_matrix[i][j].weight_type = DOUBLE;
            G.adj_matrix[i][j].edge_info = (edge_info_t*)malloc(sizeof(edge_info_t));
            G.adj_matrix[i][j].edge_info->starting_vertex_idx = i;
            G.adj_matrix[i][j].edge_info->ending_vertex_idx = j;
            G.adj_matrix[i][j].edge_info->value.double_value = DBL_MAX;
        }
    }

    for (int i = 0; i < G.edge_count; i++) {
        int curRowIdx = startingVertexIndexArr[i];
        int curColIdx = endingVertexIndexArr[i];
        G.adj_matrix[curRowIdx][curColIdx].edge_info->starting_vertex_idx = startingVertexIndexArr[i];
        G.adj_matrix[curRowIdx][curColIdx].edge_info->ending_vertex_idx = endingVertexIndexArr[i];
        G.adj_matrix[curRowIdx][curColIdx].edge_info->value.double_value = weightArr[i];
    }

    int predecessor[MAX_VERTEX_CNT][MAX_VERTEX_CNT];
    edge_t distance[MAX_VERTEX_CNT];
    int v0 = 0; // 从索引0结点开始(到其他结点)

    // D初始化
    for (int i = 0; i < MAX_VERTEX_CNT; i++) {
        distance[i].weight_type = DOUBLE;
        distance[i].edge_info = (edge_info_t*)malloc(sizeof(edge_info_t));

        distance[i].edge_info->starting_vertex_idx = 0;
        distance[i].edge_info->ending_vertex_idx = i;
        distance[i].edge_info->value.double_value = DBL_MAX;
    }

    ShortestPath_BellmanFord(&G, v0, predecessor, distance);

    PrintSingleSourceShortestPath(&G, v0, predecessor, distance);

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}


/*!
 * 测试弗洛伊德(Floyd-Warshall)算法
 * @note:
              结点0
              / \
             /   \
           0.1   0.12
           /       \
          /         \
      结点1---0.01---结点2
        / \        / \
       /   \      /   \
    0.13  0.14 0.05   0.17
     /      \  /        \
    /        \/          \
结点4--0.09--结点3--0.11--结点5
 */
void TestFloyd() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                      Test Floyd-Warshall                         \n");
    printf("                测试弗洛伊德(Floyd-Warshall)最短路径              \n\n\n");

    VERTEX_TYPE vertices[6] = {0, 1, 2, 3, 4, 5};

    matrix_graph_t G;
    G.vertex_count = 6;           // 结点数量
    G.edge_count = 9;           // 弧(边)数量
    G.kind = DN;            // 类型:有向网
    G.weight_type = DOUBLE;  // 弧(边)权值类型

    // 0 - 1: 0.1,   0 - 2: 0.12,  1 - 2: 0.2
    // 1 - 3: 0.14,  1 - 4: 0.13,  2 - 3: 0.05
    // 2 - 5: 0.17,  3 - 4: 0.09,  3 - 5: 0.11
    int starting_vertex_index_arr[9] = {0, 0, 1, 1, 1, 2, 2, 3, 3}; // 起点
    int ending_vertex_index_arr[9] = {1, 2, 2, 3, 4, 3, 5, 4, 5};   // 终点
    double weight_arr[9] = {0.1, 0.12, 0.01, 0.14, 0.13, 0.05, 0.17, 0.09, 0.11}; // 权重

    // 对每个[i, j]进行初始化, 默认没有弧(边), 所有的弧(边)长为最大值
    for (int i = 0; i < G.vertex_count; i++) {
        G.vertices[i] = vertices[i];
        for (int j = 0; j < G.vertex_count; j++) {
            G.adj_matrix[i][j].weight_type = DOUBLE;
            G.adj_matrix[i][j].edge_info = (edge_info_t*)malloc(sizeof(edge_info_t));
            G.adj_matrix[i][j].edge_info->starting_vertex_idx = i;
            G.adj_matrix[i][j].edge_info->ending_vertex_idx = j;
            G.adj_matrix[i][j].edge_info->value.double_value = DBL_MAX;

            G.adj_matrix[j][i].weight_type = DOUBLE;
            G.adj_matrix[j][i].edge_info = (edge_info_t*)malloc(sizeof(edge_info_t));
            G.adj_matrix[j][i].edge_info->starting_vertex_idx = j;
            G.adj_matrix[j][i].edge_info->ending_vertex_idx = i;
            G.adj_matrix[j][i].edge_info->value.double_value = DBL_MAX;
        }
    }

    for (int i = 0; i < G.edge_count; i++) {
        int row_idx = starting_vertex_index_arr[i];
        int col_idx = ending_vertex_index_arr[i];

        G.adj_matrix[row_idx][col_idx].edge_info->starting_vertex_idx = row_idx;
        G.adj_matrix[row_idx][col_idx].edge_info->ending_vertex_idx = col_idx;
        G.adj_matrix[row_idx][col_idx].edge_info->value.double_value = weight_arr[i];

        G.adj_matrix[col_idx][row_idx].edge_info->starting_vertex_idx = col_idx;
        G.adj_matrix[col_idx][row_idx].edge_info->ending_vertex_idx = row_idx;
        G.adj_matrix[col_idx][row_idx].edge_info->value.double_value = weight_arr[i];
    }

    int predecessor[MAX_VERTEX_CNT][MAX_VERTEX_CNT];
    edge_t distance[MAX_VERTEX_CNT][MAX_VERTEX_CNT];

    // D初始化
    for (int i = 0; i < MAX_VERTEX_CNT; i++) {
        for (int j = 0; j < MAX_VERTEX_CNT; j++) {
            distance[i][j].weight_type = DOUBLE;
            distance[i][j].edge_info = (edge_info_t *) malloc(sizeof(edge_info_t));
        }
    }

    Floyd(&G, predecessor, distance);
    PrintMultiSourceShortestPath(&G, distance, predecessor);

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}
