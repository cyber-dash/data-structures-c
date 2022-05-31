//
// Created by cyberdash@163.com on 2022/4/19.
//

#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include "algorithm.h"
#include "queue.h"
#include "heap.h"
#include "disjoint_set.h"


Status Visit(MGraph *graph, int vertex) {
    int index;
    Status status = LocateVex(*graph, vertex, &index);
    if (status == OK) {
        printf("%d ", index);
    }

    return status;
}


/*!
 * DFS遍历
 * @param G 图
 * @param Visit 结点访问函数
 * @note
 * 严书中的实现方式, 其实并不需要传此参数
 */
void DFSTraverse(MGraph G, Status (*Visit)(int v)) {

    // 构造visited数组
    int* visited = (int*)malloc(G.vexnum * sizeof(int));
    /* error handler */

    for (int i = 0; i < G.vexnum; i++) {
        visited[i] = 0;
    }

    for (int v = 0; v < G.vexnum; ++v) {
        if (!visited[v]) {
            DFS(G, 0, visited);
        }
    }
}


void DFS(MGraph G, int v, int* visited) {
    visited[v] = 1;
    Visit(&G, v);   // 访问第v个顶点

    for (int w = FirstAdjVex(&G, v); w >= 0; w = NextAdjVex(&G, v, w)) {
        if (!visited[w]) {
            DFS(G, w, visited);
        }
    }
}


/*!
 * BFS遍历
 * @param G
 * @param Visit
 */
void BFSTraverse(MGraph G, Status (*Visit)(MGraph *G, int v)) {

    // 构造visited数组
    int* visited = (int*)malloc(G.vexnum * sizeof(int));
    /* error handler */

    for (int i = 0; i < G.vexnum; i++) {
        visited[i] = 0;
    }

    LinkQueue Q;
    InitQueue(&Q);

    for (int v = 0; v < G.vexnum; ++v) {
        if (!visited[v]) {
            visited[v] = 1;
            Visit(&G, v);

            EnQueue(&Q, v);

            while (!QueueEmpty(&Q)) {
                int u;
                DeQueue(&Q, &u);
                for (int w = FirstAdjVex(&G, u); w >= 0; w = NextAdjVex(&G, u, w)) {
                    if (!visited[w]) {
                        visited[w] = 1;
                        Visit(&G, w);
                        EnQueue(&Q, w);
                    }
                }
            }
        }
    }
}


/*!
 *
 * @param graph
 * @param v0
 * @param min_span_tree
 */
void Prim(MGraph* graph, VRType v0, MinSpanNode* min_span_tree) {
    int vertex_cnt = graph->vexnum;

    // warning: 此处使用数组, 如果可以, 使用set来实现vertex_set,
    // 如果你觉得用c语言做set比较麻烦, 请移步C++, C++更适合做算法
    int vertex_set[MAX_VERTEX_CNT];
    vertex_set[v0] = TRUE;
    int in_vertex_set_cnt = 1;

    do {
        MinSpanNodeArr minSpanNodeArr;      // 小顶堆
        int cur_heap_idx = 1;

        for (int i = 0; i < vertex_cnt; i++) {

            // 如果i不在vertex_set, continue
            if (vertex_set[i] == FALSE) {
                continue;
            }
            for (int j = 0; j < vertex_cnt; j++) {
                // 如果j在vertex_set 或者 边(i, j)不存在, continue
                if (vertex_set[j] == TRUE || graph->arcs[i][j].info->value.double_value == DBL_MAX) {
                    continue;
                }

                MinSpanNode cur_min_span_node;
                cur_min_span_node.starting_vertex_idx = graph->arcs[i][j].info->startingVertexIndex;
                cur_min_span_node.ending_vertex_idx = graph->arcs[i][j].info->endingVertexIndex;
                cur_min_span_node.weight_type = graph->arcs[i][j].adj;
                cur_min_span_node.weight.double_value = graph->arcs[i][j].info->value.double_value;

                minSpanNodeArr[cur_heap_idx] = cur_min_span_node;

                cur_heap_idx++;
            }
        }

        BuildHeap(minSpanNodeArr, cur_heap_idx - 1);
        min_span_tree[in_vertex_set_cnt - 1] = minSpanNodeArr[1];  // 取堆顶

        int idx = minSpanNodeArr[1].ending_vertex_idx;
        vertex_set[idx] = TRUE;

        in_vertex_set_cnt++;

    } while (in_vertex_set_cnt < vertex_cnt);
}


void Kruskal(MGraph* graph, MinSpanNode* min_span_tree) {

    int vertex_num = graph->vexnum;     // 结点数量
    int edge_num = graph->arcnum;       // 边数量

    MinSpanNodeArr minSpanNodeArr;      // 小顶堆
    DisjointSet disjointSet;            // 并查集
    InitDisjointSet(&disjointSet, vertex_num);

    int arcCount = 1;
    for (int i = 0; i < graph->vexnum; i++) {
        for (int j = 0; j < graph->vexnum; j++) {
            if (graph->arcs[i][j].info->value.double_value == DBL_MAX) {
                continue;
            }

            ArcCell curArcCell = graph->arcs[i][j];

            MinSpanNode minSpanNode;
            minSpanNode.starting_vertex_idx = curArcCell.info->startingVertexIndex;
            minSpanNode.ending_vertex_idx = curArcCell.info->endingVertexIndex;
            minSpanNode.weight_type = curArcCell.adj;
            minSpanNode.weight.double_value = curArcCell.info->value.double_value;

            minSpanNodeArr[arcCount] = minSpanNode;

            arcCount++;
        }
    }

    BuildHeap(minSpanNodeArr, edge_num);

    // 此时, 所有的边都已经进入小顶堆, 执行Kruskal算法核心流程

    int count = 1;
    int idx = 0;
    while (count < vertex_num) {    // 执行n - 1次
        MinSpanNode cur_min_span_node = minSpanNodeArr[1];  // 取堆顶

        minSpanNodeArr[1] = minSpanNodeArr[arcCount];
        arcCount--;
        BuildHeap(minSpanNodeArr, arcCount);    // 重新调整堆

        int curStartingRootIdx = Find(&disjointSet, cur_min_span_node.starting_vertex_idx);
        int curEndingRootIdx = Find(&disjointSet, cur_min_span_node.ending_vertex_idx);

        if (curStartingRootIdx != curEndingRootIdx) {
            DisjointSetUnion(&disjointSet, curStartingRootIdx, curEndingRootIdx);

            min_span_tree[idx] = cur_min_span_node;
            idx++;
        }

        count++;
    }
}


// 打印最小生成树
void PrintMinSpanTree(MinSpanNodeArr minSpanTree, int size) {

    for (int i = 0; i < size; i++) {
        MinSpanNode cur = minSpanTree[i];

        printf("起始点: %d, 终点: %d, 距离: %lf\n",
               cur.starting_vertex_idx,
               cur.ending_vertex_idx,
               cur.weight.double_value);
    }
}


/*!
 * 迪杰斯特拉(Dijkstra)最短路径
 * @param graph
 * @param v0
 * @param predecessor
 * @param distance
 * @note
 * predecessor目前是二维数组, 用于多源最短路径, 单源可以替换成一维数组
 */
void ShortestPath_Dijkstra(MGraph* graph, int v0, int (*predecessor)[MAX_VERTEX_CNT], ArcCell* distance ) {

    // 用Dijkstra算法求有向网G的v0顶点到其余顶点v的最短路径P[v]及其带权长度D[v]
    int vertex_cnt = graph->vexnum;
    int* final = (int*)malloc(vertex_cnt * sizeof(int));
    // VRType type = graph->arcs[0][0].adj;

    for (int v = 0; v < graph->vexnum; v++) {
        final[v] = FALSE;

        for (int w = 0; w < graph->vexnum; w++) {
            predecessor[v][w] = -1;
        }

        distance[v].info->value.double_value = graph->arcs[v0][v].info->value.double_value;
        predecessor[v0][v] = v0;    // v0是从v0到v的最短路径, v的前一结点
    }

    // 初始化, v0到v0的距离为0
    distance[v0].info->value.double_value = 0;

    // 初始化, v0顶点属于S集
    final[v0] = TRUE;

    // 开始主循环, 每次求得v0到某个v顶点的最短路径, 并加v到S集
    for (int i = 1; i < vertex_cnt; i++) {
        double doubleMin = DBL_MAX;    // 最大的double型数值, float.h文件

        int v;
        for (int w = 0; w < vertex_cnt; w++) {
            if (!final[w]) {
                if (distance[w].info->value.double_value < doubleMin) {
                    v = w;
                    doubleMin = distance[w].info->value.double_value;
                }
            }
        }

        final[v] = TRUE;    // 离v0最近的v, 加入到S集合

        for (int w = 0; w < vertex_cnt; w++) {
            if (!final[w] &&
                doubleMin + graph->arcs[v][w].info->value.double_value < distance[w].info->value.double_value)
            {
                distance[w].info->value.double_value = doubleMin + graph->arcs[v][w].info->value.double_value;
                predecessor[v0][w] = v;
            }
        }
    }
}


/*!
 * 贝尔曼福特(Bellman-Ford)最短路径
 * @param graph
 * @param v0
 * @param predecessor
 * @param distance
 * @return
 * @note
 *
 * BellmanFord算法:
 *
 *     --- 初始化 ---
 *
 *     for 图中的每个结点v:
 *         如果(starting_vertex, v)没有边:
 *             distance[v] <-- INFINITY(不存在路径)
 *         否则:
 *             如果 v 是starting_vertex(起始点):
 *                 distance[v] = 0
 *                 predecessor[v] <-- -1(没有前一结点)
 *             否则:
 *                 distance[v] = 边(starting_vertex, v)的长度(权值)
 *                 predecessor[v] <-- starting_vertex_index(结点starting_vertex的索引) // v的前一结点是starting_vertex
 *
 *
 *     --- 动态规划 ---
 *
 *     for循环(图结点总数 - 1)次:
 *         for 图的每一条边edge (u, v):
 *             // 松弛
 *             如果 distance[u] + 边(u, v)权重 < distance[v]:
 *                 distance[v] <-- distance[u] + 边(u, v)权重
 *                 predecessor[v] <-- u
 *
 *
 *     --- 检查是否有负权重的回路 ---
 *
 *     for 每一条边edge (u, v):
 *         如果 distance[u] + 边(u, v)权重 < distance[v]:
 *             error "图包含负回路"
 */
int ShortestPath_BellmanFord(MGraph* graph, int v0, int (*predecessor)[MAX_VERTEX_CNT], ArcCell* distance) {

    int vertex_cnt = graph->vexnum;
    for (int i = 0; i < vertex_cnt; i++) {
        distance[i].adj = DOUBLE;
        distance[i].info->value.double_value = graph->arcs[v0][i].info->value.double_value;
        predecessor[v0][i] = v0;
    }

    for (int i = 0; i < vertex_cnt - 1; i++) {
        // todo: 此处可以优化
        for (int u = 0; u < vertex_cnt; u++) {
            for (int v = 0; v < vertex_cnt; v++) {
                if (graph->arcs[u][v].info->value.double_value == DBL_MAX) {
                    continue;
                }

                // 松弛
                if (distance[u].info->value.double_value + graph->arcs[u][v].info->value.double_value
                    < distance[v].info->value.double_value)
                {
                    distance[v].info->value.double_value =
                        distance[u].info->value.double_value + graph->arcs[u][v].info->value.double_value;
                    predecessor[v0][v] = u;
                }
            }
        }
    }

    int has_negative_weight_cycle = FALSE; // 默认没有负权环
    for (int u = 0; u < vertex_cnt; u++) {
        for (int v = 0; v < vertex_cnt; v++) {
            if (graph->arcs[u][v].info->value.double_value == DBL_MAX) {
                continue;
            }

            if (distance[u].info->value.double_value + graph->arcs[u][v].info->value.double_value
                < distance[v].info->value.double_value)
            {
                has_negative_weight_cycle = TRUE; // 有负权环
                break;
            }
        }
    }

    return has_negative_weight_cycle;
}


/*!
 *
 * @param graph
 * @param predecessor
 * @param distance
 * @note
 *
 * 弗洛伊德算法:
 *     distance[][] is a distance matrix for n vertices.
 *         distance[i][j] is the distance to move directly from i to j.
 *         if no direct link from i to j
 *             then initialize distance[i][j] = INFINITY
 *         the distance from a node to itself is 0(Initialize distance[i][i] = 0 for all i).
 *     predecessor[][] is a predecessor matrix. it enables you to reconstruct the shortest paths.
 *         predecessor[i][j] should be initialized to i.
 *
 * 算法执行结果:
 *     distance[i][j] contains the total cost along the shortest path from i to j.
 *     predecessor[i][j] contains the predecessor of j on the shortest path from i to j.
 */
void Floyd(MGraph* graph, int (*predecessor)[MAX_VERTEX_CNT], ArcCell (*distance)[MAX_VERTEX_CNT]) {
    int vertex_cnt = graph->vexnum;

    for (int i = 0; i < vertex_cnt; i++) {
        for (int j = 0; j < vertex_cnt; j++) {

            if (i == j) {
                if (graph->weight_type == INT) {
                    distance[i][j].adj = INT;
                    distance[i][j].info->value.int_value = 0;
                } else if (graph->weight_type == DOUBLE) {
                    distance[i][j].adj = DOUBLE;
                    distance[i][j].info->value.double_value = 0;
                }
            } else {
                if (graph->weight_type == INT) {
                    distance[i][j].adj = INT;
                    if (graph->arcs[i][j].info->value.int_value != INT_MAX) {
                        distance[i][j].info->value.int_value = graph->arcs[i][j].info->value.int_value;
                    } else {
                        distance[i][j].info->value.int_value = INT_MAX;
                    }
                } else if (graph->weight_type == DOUBLE) {
                    distance[i][j].adj = DOUBLE;
                    if (graph->arcs[i][j].info->value.double_value != DBL_MAX) {
                        distance[i][j].info->value.double_value = graph->arcs[i][j].info->value.double_value;
                    } else {
                        distance[i][j].info->value.double_value = DBL_MAX;
                    }
                }
            }

            predecessor[i][j] = i;
        }
    }

    for (int k = 0; k < vertex_cnt; k++) {
        for (int i = 0; i < vertex_cnt; i++) {
            for (int j = 0; j < vertex_cnt; j++) {
                if (graph->weight_type == INT) {
                    if (distance[i][k].info->value.int_value + distance[k][j].info->value.int_value
                            < distance[i][j].info->value.int_value)
                    {
                        distance[i][j].info->value.int_value =
                            distance[i][k].info->value.int_value + distance[k][j].info->value.int_value;
                        predecessor[i][j] = predecessor[k][j];
                    }
                } else if (graph->weight_type == DOUBLE) {
                    if (distance[i][k].info->value.double_value + distance[k][j].info->value.double_value
                        < distance[i][j].info->value.double_value)
                    {
                        distance[i][j].info->value.double_value =
                            distance[i][k].info->value.double_value + distance[k][j].info->value.double_value;
                        predecessor[i][j] = predecessor[k][j];
                    }
                }
            }
        }
    }
}


/*
void PrintSingleSourceShortestPath(MGraph *graph, int v0, ArcCell* distance, int (*predecessor)[MAX_VERTEX_CNT]) {

    int vertex_cnt = graph->vexnum;
    int* cur_predecessor = (int*) malloc(vertex_cnt * sizeof(int));

    for (int i = 0; i < vertex_cnt; i++) {

        // 不处理v0到v0自己本身的最短路径
        if (i == v0) {
            continue;
        }

        // 构造"以索引v0结点为起点, 索引i结点为终点"的最短路径
        int pre_vertex_index = i;
        int idx = 0;
        while (pre_vertex_index != v0) {
            cur_predecessor[idx] = pre_vertex_index;
            pre_vertex_index = predecessor[pre_vertex_index];
            idx++;
        }

        printf("起始点%d到结点%d的最短路径为:\n", v0, i);
        printf("%d ", v0);

        while (idx > 0) {
            idx--;
            printf(" idx ");
        }

        printf(", ");
        if (distance[i].adj == INT) {
            printf("最短路径长度为: %d\n", distance[i].info->value.int_value);
        } else if (distance[i].adj == DOUBLE) {
            printf("最短路径长度为: %.2lf\n", distance[i].info->value.double_value);
        }
    }
}
 */


void PrintSingleSourceShortestPath(MGraph *graph, int v0, int (*predecessor)[MAX_VERTEX_CNT], ArcCell* distance) {

    int vertex_cnt = graph->vexnum;
    for (int i = 0; i < vertex_cnt; i++) {
        // 不处理v0到v0自己本身的最短路径
        if (i == v0) {
            continue;
        }

        printf("起始点%d到结点%d的最短路径为:\n", v0, i);
        PrintSingleSourceShortestPathRecursive(graph, v0, i, predecessor);

        printf(", ");
        if (distance[i].adj == INT) {
            printf("最短路径长度为: %d\n", distance[i].info->value.int_value);
        } else if (distance[i].adj == DOUBLE) {
            printf("最短路径长度为: %.2lf\n", distance[i].info->value.double_value);
        }
    }
}


void PrintMultiSourceShortestPath(MGraph *graph,
                                  ArcCell (*distance)[MAX_VERTEX_CNT],
                                  int (*predecessor)[MAX_VERTEX_CNT])
{
    int vertex_cnt = graph->vexnum;
    for (int i = 0; i < vertex_cnt; i++) {
        printf("--- 从起始点%d到其他各顶点的最短路径 ---\n", i);
        for (int j = 0; j < vertex_cnt; j++) {
            if (i == j) {
                continue;
            }
            printf("起始点%d到结点%d的最短路径为:\n", i, j);

            PrintSingleSourceShortestPathRecursive(graph, i, j, predecessor);

            printf(", 最短路径长度为: %.2lf\n", distance[i][j].info->value.double_value);
        }
    }
}


/*!
 * 通用单源最短路径打印函数
 * @param graph
 * @param i
 * @param j
 * @param predecessor
 * @note
 * 多源最短路径和单源最短路径问题, 都可以使用此函数
 */
void PrintSingleSourceShortestPathRecursive(MGraph *graph, int i, int j, int (*predecessor)[MAX_VERTEX_CNT]) {
    if (i != j) {
        int predecessor_of_j = predecessor[i][j];
        PrintSingleSourceShortestPathRecursive(graph, i, predecessor_of_j, predecessor);
    }

    printf("%d ", j);
}
