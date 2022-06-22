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


Status Visit(matrix_graph_t *graph, int vertex) {
    int index;
    Status status = LocateVertex(*graph, vertex, &index);
    if (status == OK) {
        printf("%d ", index);
    }

    return status;
}


/*!
 * DFS遍历
 * @param graph 图
 * @param Visit 结点访问函数
 * @note
 */
void DFSTraverse(matrix_graph_t graph, Status (*Visit)(int v)) {

    // 构造visited数组
    int* visited = (int*)malloc(graph.vertex_count * sizeof(int));

    for (int i = 0; i < graph.vertex_count; i++) {
        visited[i] = 0;
    }

    for (int v = 0; v < graph.vertex_count; ++v) {
        if (!visited[v]) {
            DFSRecursive(graph, 0, visited);
        }
    }
}


// todo: Visit函数写到参数
void DFSRecursive(matrix_graph_t graph, int starting_vertex_idx, int* visited) {
    visited[starting_vertex_idx] = 1;
    Visit(&graph, starting_vertex_idx);   // 访问索引starting_vertex_idx的顶点

    for (int vertex_idx = FirstAdjVertexIdx(&graph, starting_vertex_idx);
         vertex_idx >= 0;
         vertex_idx = NextAdjVertexIdx(&graph, starting_vertex_idx, vertex_idx))
    {
        if (!visited[vertex_idx]) {
            DFSRecursive(graph, vertex_idx, visited);
        }
    }
}


/*!
 * BFS遍历
 * @param graph
 * @param Visit
 */
void BFSTraverse(matrix_graph_t graph, Status (*Visit)(matrix_graph_t*, int)) {

    // 构造visited数组
    int* visited = (int*)malloc(graph.vertex_count * sizeof(int));
    /* error handler */

    for (int i = 0; i < graph.vertex_count; i++) {
        visited[i] = 0;
    }

    linked_queue_node_t queue;
    InitQueue(&queue);

    for (int v = 0; v < graph.vertex_count; ++v) {
        if (!visited[v]) {
            visited[v] = 1;
            Visit(&graph, v);

            EnQueue(&queue, v);

            while (!QueueEmpty(&queue)) {
                int u;
                DeQueue(&queue, &u);
                for (int w = FirstAdjVertexIdx(&graph, u); w >= 0; w = NextAdjVertexIdx(&graph, u, w)) {
                    if (!visited[w]) {
                        visited[w] = 1;
                        Visit(&graph, w);
                        EnQueue(&queue, w);
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
void Prim(matrix_graph_t* graph, edge_t* min_span_tree) {
    int vertex_count = graph->vertex_count;

    // note: 此处使用数组, 如果可以, 使用set来实现vertex_set,
    // 如果你觉得用c语言做set比较麻烦, 请移步C++, C++更适合做算法
    int vertex_set[MAX_VERTEX_CNT];
    vertex_set[0] = 0;       // 从索引0结点开始
    int in_vertex_set_cnt = 1;  // 在vertex_set中的结点数量

    while (in_vertex_set_cnt < vertex_count) {

        MinPriorityQueue min_priority_queue;
        MinPriorityQueueInit(&min_priority_queue, vertex_count * vertex_count);

        for (int i = 0; i < in_vertex_set_cnt; i++) {
            int cur_starting_vertex_idx = vertex_set[i];
            for (int j = 0; j < vertex_count; j++) {

                // 检查索引j结点是否在vertex_set中
                int in_vertex_set = FALSE;
                for (int k = 0; k < in_vertex_set_cnt; k++) {
                    if (j == vertex_set[k]) {
                        in_vertex_set = TRUE;
                        break;
                    }
                }

                // 如果索引j结点在vertex_set中, continue
                if (in_vertex_set) {
                    continue;
                }

                // 如果cur_starting_vertex_idx == j, 或者边(cur_starting_vertex_idx == j, j)不存在, continue
                if (cur_starting_vertex_idx == j || graph->adj_matrix[cur_starting_vertex_idx][j].weight_type == NO_EDGE) {
                    continue;
                }

                edge_t cur_adj_edge = graph->adj_matrix[cur_starting_vertex_idx][j];
                MinPriorityQueueEnqueue(&min_priority_queue, cur_adj_edge);
            }
        }

        edge_t cur_mst_edge;
        MinPriorityQueueDequeue(&min_priority_queue, &cur_mst_edge);
        min_span_tree[in_vertex_set_cnt - 1] = cur_mst_edge;

        vertex_set[in_vertex_set_cnt] = cur_mst_edge.ending_vertex_idx;

        in_vertex_set_cnt++;
    }
}


void Kruskal(matrix_graph_t* graph, edge_t* min_span_tree) {

    int vertex_count = graph->vertex_count;     // 结点数量

    MinPriorityQueue min_priority_queue;
    MinPriorityQueueInit(&min_priority_queue, vertex_count * vertex_count);

    DisjointSet disjoint_set;            // 并查集
    InitDisjointSet(&disjoint_set, vertex_count);

    int edge_count = 1;
    for (int i = 0; i < graph->vertex_count; i++) {
        for (int j = 0; j < graph->vertex_count; j++) {
            // if (graph->adj_matrix[i][j].weight.double_value == DBL_MAX) {
            if (graph->adj_matrix[i][j].weight_type == NO_EDGE) {
                continue;
            }

            edge_t cur_edge = graph->adj_matrix[i][j];

            edge_t mst_node;
            mst_node.starting_vertex_idx = cur_edge.starting_vertex_idx;
            mst_node.ending_vertex_idx = cur_edge.ending_vertex_idx;
            mst_node.weight_type = cur_edge.weight_type;
            mst_node.weight.double_value = cur_edge.weight.double_value;

            MinPriorityQueueEnqueue(&min_priority_queue, mst_node);

            edge_count++;
        }
    }

    // 此时, 所有的边都已经进入小顶堆, 执行Kruskal算法核心流程

    int count = 1;
    int idx = 0;
    while (count < vertex_count) {    // 执行n - 1次
        edge_t cur_min_span_node;
        MinPriorityQueueDequeue(&min_priority_queue, &cur_min_span_node);

        int curStartingRootIdx = DisjointSetFindRecursive(&disjoint_set, cur_min_span_node.starting_vertex_idx);
        int curEndingRootIdx = DisjointSetFindRecursive(&disjoint_set, cur_min_span_node.ending_vertex_idx);

        if (curStartingRootIdx != curEndingRootIdx) {
            DisjointSetUnion(&disjoint_set, curStartingRootIdx, curEndingRootIdx);

            min_span_tree[idx] = cur_min_span_node;
            idx++;
        }

        count++;
    }
}


// 打印最小生成树
void PrintMinSpanTree(MST_t min_span_tree, int size) {

    for (int i = 0; i < size; i++) {
        edge_t cur = min_span_tree[i];

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
void ShortestPath_Dijkstra(matrix_graph_t* graph, int v0, int (*predecessor)[MAX_VERTEX_CNT], edge_t* distance ) {

    // 用Dijkstra算法求有向网G的v0顶点到其余顶点v的最短路径P[v]及其带权长度D[v]
    int vertex_cnt = graph->vertex_count;
    int* final = (int*)malloc(vertex_cnt * sizeof(int));

    for (int v = 0; v < graph->vertex_count; v++) {
        final[v] = FALSE;

        for (int w = 0; w < graph->vertex_count; w++) {
            predecessor[v][w] = -1;
        }

        distance[v].weight.double_value = graph->adj_matrix[v0][v].weight.double_value;
        predecessor[v0][v] = v0;    // v0是从v0到v的最短路径, v的前一结点
    }

    // 初始化, v0到v0的距离为0
    distance[v0].weight.double_value = 0;

    // 初始化, v0顶点属于S集
    final[v0] = TRUE;

    // 开始主循环, 每次求得v0到某个v顶点的最短路径, 并加v到S集
    for (int i = 1; i < vertex_cnt; i++) {
        double doubleMin = DBL_MAX;    // 最大的double型数值, float.h文件

        int v;
        for (int w = 0; w < vertex_cnt; w++) {
            if (!final[w]) {
                if (distance[w].weight.double_value < doubleMin) {
                    v = w;
                    doubleMin = distance[w].weight.double_value;
                }
            }
        }

        final[v] = TRUE;    // 离v0最近的v, 加入到S集合

        for (int w = 0; w < vertex_cnt; w++) {
            if (!final[w] &&
                doubleMin + graph->adj_matrix[v][w].weight.double_value < distance[w].weight.double_value)
            {
                distance[w].weight.double_value = doubleMin + graph->adj_matrix[v][w].weight.double_value;
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
int ShortestPath_BellmanFord(matrix_graph_t* graph, int v0, int (*predecessor)[MAX_VERTEX_CNT], edge_t* distance) {

    int vertex_cnt = graph->vertex_count;

    for (int i = 0; i < graph->vertex_count; i++) {
        distance[i].weight.double_value = DBL_MAX;
    }
    distance[v0].weight.double_value = 0;
    predecessor[v0][v0] = -1;

    // 遍历 "图结点数 - 1" 次
    for (int i = 0; i < vertex_cnt - 1; i++) {
        // 遍历 "图边数" 次
        for (int j = 0; j < graph->edge_count; j++) {
            int u = graph->edges[j].starting_vertex_idx;
            int v = graph->edges[j].ending_vertex_idx;

            // 松弛
            if (distance[u].weight.double_value + graph->adj_matrix[u][v].weight.double_value
                < distance[v].weight.double_value)
            {
                distance[v].weight.double_value =
                    distance[u].weight.double_value + graph->adj_matrix[u][v].weight.double_value;
                predecessor[v0][v] = u;
            }
        }
    }

    int has_negative_weight_cycle = FALSE; // 默认没有负权环
    for (int u = 0; u < vertex_cnt; u++) {
        for (int v = 0; v < vertex_cnt; v++) {
            if (graph->adj_matrix[u][v].weight_type == NO_EDGE) {
                continue;
            }

            if (distance[u].weight.double_value + graph->adj_matrix[u][v].weight.double_value
                < distance[v].weight.double_value)
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
void Floyd(matrix_graph_t* graph, int (*predecessor)[MAX_VERTEX_CNT], edge_t (*distance)[MAX_VERTEX_CNT]) {
    int vertex_cnt = graph->vertex_count;

    for (int i = 0; i < vertex_cnt; i++) {
        for (int j = 0; j < vertex_cnt; j++) {

            if (i == j) {
                distance[i][j].weight_type = DOUBLE;
                distance[i][j].weight.double_value = 0;
            } else {
                distance[i][j].weight_type = DOUBLE;
                if (graph->adj_matrix[i][j].weight.double_value != DBL_MAX) {
                    distance[i][j].weight.double_value = graph->adj_matrix[i][j].weight.double_value;
                } else {
                    distance[i][j].weight.double_value = DBL_MAX;
                }
            }

            predecessor[i][j] = i;
        }
    }

    for (int k = 0; k < vertex_cnt; k++) {
        for (int i = 0; i < vertex_cnt; i++) {
            for (int j = 0; j < vertex_cnt; j++) {
                if (distance[i][k].weight.double_value + distance[k][j].weight.double_value
                    < distance[i][j].weight.double_value)
                {
                    distance[i][j].weight.double_value =
                        distance[i][k].weight.double_value + distance[k][j].weight.double_value;
                    predecessor[i][j] = predecessor[k][j];
                }
            }
        }
    }
}


void PrintSingleSourceShortestPath(matrix_graph_t *graph,
                                   int starting_vertex_index,
                                   int (*predecessor)[MAX_VERTEX_CNT],
                                   edge_t* distance)
{
    int vertex_cnt = graph->vertex_count;
    for (int i = 0; i < vertex_cnt; i++) {
        // 不处理v0到v0自己本身的最短路径
        if (i == starting_vertex_index) {
            continue;
        }

        printf("起始点%d到结点%d的最短路径为:\n", starting_vertex_index, i);
        PrintSingleSourceShortestPathRecursive(graph, starting_vertex_index, i, predecessor);

        printf(", ");
        printf("最短路径长度为: %.2lf\n", distance[i].weight.double_value);
    }
}


void PrintMultiSourceShortestPath(matrix_graph_t *graph,
                                  edge_t (*distance)[MAX_VERTEX_CNT],
                                  int (*predecessor)[MAX_VERTEX_CNT])
{
    int vertex_cnt = graph->vertex_count;
    for (int i = 0; i < vertex_cnt; i++) {
        printf("--- 从起始点%d到其他各顶点的最短路径 ---\n", i);
        for (int j = 0; j < vertex_cnt; j++) {
            if (i == j) {
                continue;
            }
            printf("起始点%d到结点%d的最短路径为:\n", i, j);

            PrintSingleSourceShortestPathRecursive(graph, i, j, predecessor);

            printf(", 最短路径长度为: %.2lf\n", distance[i][j].weight.double_value);
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
void PrintSingleSourceShortestPathRecursive(matrix_graph_t *graph, int i, int j, int (*predecessor)[MAX_VERTEX_CNT]) {
    if (i != j) {
        int predecessor_of_j = predecessor[i][j];
        PrintSingleSourceShortestPathRecursive(graph, i, predecessor_of_j, predecessor);
    }

    printf("%d ", j);
}
