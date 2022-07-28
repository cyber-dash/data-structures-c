/*!
 * @file algorithm.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 搜索算法
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "algorithm.h"
#include "queue.h"
#include "heap.h"
#include "disjoint_set.h"


status_t Visit(matrix_graph_t *graph, int vertex_index) {
    printf("%d ", vertex_index);
    return OK;
}


/*!
 * DFS遍历
 * @param graph 图
 * @param Visit 结点访问函数
 * @note
 */
void DFSTraverse(matrix_graph_t graph, status_t (*Visit)(matrix_graph_t* graph, int vertex_index)) {

    int* visited_vertex_index_array = (int*)malloc(graph.vertex_count * sizeof(int));

    for (int i = 0; i < graph.vertex_count; i++) {
        visited_vertex_index_array[i] = 0;
    }

    for (int i = 0; i < graph.vertex_count; i++) {
        if (!visited_vertex_index_array[i]) {
            DFSRecursive(graph, i, visited_vertex_index_array, Visit);
        }
    }
}


/*!
 *
 * @param graph 图
 * @param vertex_index 图结点索引
 * @param visited_vertex_index_array 已访问结点索引的数组
 * @param Visit 访问函数
 */
void DFSRecursive(matrix_graph_t graph,
                  int vertex_index,
                  int* visited_vertex_index_array,
                  status_t (*Visit)(matrix_graph_t*, int))
{
    Visit(&graph, vertex_index);                    // 访问索引vertex_index结点
    visited_vertex_index_array[vertex_index] = 1;   // 标记索引vertex_index结点已经被访问过

    // 遍历vertex_index结点的所有相邻结点
    for (int i = FirstAdjVertexIdx(&graph, vertex_index); i >= 0; i = NextAdjVertexIdx(&graph, vertex_index, i)) {

        // 如果当前结点(索引i结点)已经访问过, continue
        if (visited_vertex_index_array[i]) {
            continue;
        }

        // 递归调用, 对当前结点执行DFSRecursive
        DFSRecursive(graph, i, visited_vertex_index_array, Visit);
    }
}


/*!
 * BFS遍历
 * @param graph
 * @param Visit
 */
void BFSTraverse(matrix_graph_t graph, status_t (*Visit)(matrix_graph_t*, int)) {

    // 构造visited数组
    int* visited_vertex_index_array = (int*)malloc(graph.vertex_count * sizeof(int));

    for (int i = 0; i < graph.vertex_count; i++) {
        visited_vertex_index_array[i] = 0;
    }

    linked_queue_t queue;
    LinkedQueueInit(&queue);

    for (int i = 0; i < graph.vertex_count; i++) {
        if (!visited_vertex_index_array[i]) {
            visited_vertex_index_array[i] = 1;
            Visit(&graph, i);

            LinkedQueueEnQueue(&queue, i);

            while (!LinkedQueueIsEmpty(&queue)) {

                // 取队头
                int vertex_index;
                LinkedQueueDeQueue(&queue, &vertex_index);

                // 遍历队头的未遍历的邻结点
                for (int neighbor_vertex_index = FirstAdjVertexIdx(&graph, vertex_index);
                     neighbor_vertex_index >= 0;
                     neighbor_vertex_index = NextAdjVertexIdx(&graph, vertex_index, neighbor_vertex_index)
                    )
                {
                    // 如果: 当前邻结点未被访问
                    if (!visited_vertex_index_array[neighbor_vertex_index]) {

                        // 访问当前邻结点
                        Visit(&graph, neighbor_vertex_index);

                        // 当前邻结点入队
                        LinkedQueueEnQueue(&queue, neighbor_vertex_index);

                        // 标记当前邻结点被访问
                        visited_vertex_index_array[neighbor_vertex_index] = 1;
                    }
                }
            }
        }
    }
}


/*!
 * Prim最小生成树算法
 * @param graph 图(指针)
 * @param min_span_tree 最小生成树(数组)
 */
void Prim(matrix_graph_t* graph, edge_t* min_span_tree) {
    int vertex_count = graph->vertex_count;

    // note: 此处使用数组, 如果可以, 使用set来实现vertex_set,
    // 如果你觉得用c语言做set比较麻烦, 请移步C++, C++更适合做算法
    int vertex_set[MAX_VERTEX_CNT];
    vertex_set[0] = 0;       // 从索引0结点开始
    int in_vertex_set_cnt = 1;  // 在vertex_set中的结点数量

    while (in_vertex_set_cnt < vertex_count) {

        min_priority_queue_t min_priority_queue;
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
                if (cur_starting_vertex_idx == j ||
                    graph->adj_matrix[cur_starting_vertex_idx][j].weight_type == NO_EDGE)
                {
                    continue;
                }

                edge_t cur_adj_edge = graph->adj_matrix[cur_starting_vertex_idx][j];
                MinPriorityQueuePush(&min_priority_queue, cur_adj_edge);
            }
        }

        edge_t cur_mst_edge;
        MinPriorityQueuePop(&min_priority_queue, &cur_mst_edge);

        min_span_tree[in_vertex_set_cnt - 1] = cur_mst_edge;

        vertex_set[in_vertex_set_cnt] = cur_mst_edge.ending_vertex_index;
        in_vertex_set_cnt++;
    }
}


/*!
 * Kruskal最小生成树
 * @param graph 图(指针)
 * @param min_span_tree 最小生成树(数组)
 */
void Kruskal(matrix_graph_t* graph, edge_t* min_span_tree) {

    // 初始化最小优先队列, 容量 = 图边数
    min_priority_queue_t min_priority_queue;
    MinPriorityQueueInit(&min_priority_queue, graph->edge_count);

    // 初始化并查集, 容量 = 图边数
    DisjointSet disjoint_set;
    InitDisjointSet(&disjoint_set, graph->edge_count);

    // 将所有边插入到最小优先队列
    for (int i = 0; i < graph->vertex_count; i++) {
        for (int j = i + 1; j < graph->vertex_count; j++) {
            if (graph->adj_matrix[i][j].weight_type == NO_EDGE) {
                continue;
            }

            MinPriorityQueuePush(&min_priority_queue, graph->adj_matrix[i][j]);
        }
    }

    // --- 此时, 所有的边都已经进入小顶堆, 执行Kruskal算法核心流程 ---

    for (int index = 0; index < graph->vertex_count - 1;) {

        // 拿到最小优先队列队头(最小堆堆顶)
        edge_t cur_mst_item;
        MinPriorityQueuePop(&min_priority_queue, &cur_mst_item);

        // 队头对应的最短边起点/终点对应的并查集根索引
        int cur_starting_root_index =
            DisjointSetFind(&disjoint_set, cur_mst_item.starting_vertex_index);
        int cur_ending_root_index =
            DisjointSetFind(&disjoint_set, cur_mst_item.ending_vertex_index);

        // 如果: 起点根索引 不等于 终点根索引
        if (cur_starting_root_index != cur_ending_root_index) {
            // 并查集合并
            DisjointSetUnion(&disjoint_set, cur_starting_root_index, cur_ending_root_index);

            // min_span_tree增加元素
            min_span_tree[index] = cur_mst_item;
            index++;
        }
    }
}


/*!
 * 打印最小生成树
 * @param min_span_tree 最小生成树(数组)
 * @param size 边数量
 */
void PrintMinSpanTree(MST_t min_span_tree, int size) {
    for (int i = 0; i < size; i++) {
        printf("起始点: %d, 终点: %d, 距离: %lf\n",
               min_span_tree[i].starting_vertex_index,
               min_span_tree[i].ending_vertex_index,
               min_span_tree[i].weight.double_value);
    }

    printf("\n");
}



/*!
 * 迪杰斯特拉(Dijkstra)最短路径
 * @param graph 图(指针)
 * @param starting_vertex_index 起点索引
 * @param predecessor 前驱数组
 * @param distance 最短路径数组
 * @note
 * predecessor本实现使用二维数组, 这普遍用在多源最短路径, 单源可以替换成一维数组
 */
void Dijkstra(matrix_graph_t* graph, int starting_vertex_index, int(*predecessor)[MAX_VERTEX_CNT], edge_t* distance) {

    /// --- 初始化 ---

    // 结点集合初始化, 每个结点都不在集合中
    int* vertex_index_set = (int*)malloc(graph->vertex_count * sizeof(int));
    memset(vertex_index_set, 0, graph->vertex_count * sizeof(int));

    // distance数组初始化, distance[起始点]的路径距离值为0, distance[起始点之外其他结点]的路径距离值为DBL_MAX(double类型最大值)
    for (int i = 0; i < graph->vertex_count; i++) {
        distance[i].weight_type = DOUBLE;
        distance[i].weight.double_value = DBL_MAX;
    }
    distance[starting_vertex_index].weight.double_value = 0;

    // 初始化最小优先队列, 路径 起始点->起始点 的信息(从临界数组中获取)入队
    min_priority_queue_t min_priority_queue;
    MinPriorityQueueInit(&min_priority_queue, graph->vertex_count);
    MinPriorityQueuePush(&min_priority_queue, graph->adj_matrix[starting_vertex_index][starting_vertex_index]);

    /// --- 贪心 ---

    while (min_priority_queue.size != 0) {

        // 最小优先队列pop出当前最短路径cur_min_distance
        path_t cur_min_distance;
        MinPriorityQueuePop(&min_priority_queue, &cur_min_distance);

        // 取当前最短路径终点索引cur_ending_vertex_index, 进入集合vertex_index_set
        int cur_ending_vertex_index = cur_min_distance.ending_vertex_index;
        vertex_index_set[cur_ending_vertex_index] = TRUE;

        // --- 松弛 starting_vertex_index --> i(使用cur_ending_vertex_index) ---

        for (int i = 0; i < graph->vertex_count; i++) {

            // 索引i结点已经在集合vertex_set 或者 cur_ending_vertex_index与i之间没有边, continue
            if (vertex_index_set[i] == TRUE || graph->adj_matrix[cur_ending_vertex_index][i].weight_type == NO_EDGE) {
                continue;
            }

            // 如果
            //   边 (starting_vertex_index --> cur_ending_vertex_index)         的weight
            //    +
            //   边                           (cur_ending_vertex_index  -->  i) 的weight
            //    <
            //   边 (starting_vertex_index ------------------------------->  i) 的weight
            // 则
            //   更新distance[j]和predecessor[starting_vertex_index][j]
            //   distance[i]进入最小优先队列
            if (distance[cur_ending_vertex_index].weight.double_value
                +
                graph->adj_matrix[cur_min_distance.ending_vertex_index][i].weight.double_value
                <
                distance[i].weight.double_value)
            {
                distance[i].weight.double_value = distance[cur_ending_vertex_index].weight.double_value +
                    graph->adj_matrix[cur_min_distance.ending_vertex_index][i].weight.double_value;
                distance[i].ending_vertex_index = i;

                predecessor[starting_vertex_index][i] = cur_min_distance.ending_vertex_index;

                MinPriorityQueuePush(&min_priority_queue, distance[i]);
            }
        }
    }
}



/*!
 * 贝尔曼福特(Bellman-Ford)最短路径
 * @param graph
 * @param starting_vertex_index
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
int BellmanFord(matrix_graph_t* graph,
                int starting_vertex_index,
                int (*predecessor)[MAX_VERTEX_CNT],
                path_t* distance)
{
    for (int i = 0; i < graph->vertex_count; i++) {
        distance[i].weight.double_value = DBL_MAX;
    }
    distance[starting_vertex_index].weight.double_value = 0;
    predecessor[starting_vertex_index][starting_vertex_index] = -1;

    // 遍历 "图结点数 - 1" 次
    for (int i = 0; i < graph->vertex_count - 1; i++) {
        // 遍历 "图边数" 次
        for (int j = 0; j < graph->edge_count; j++) {
            int u = graph->edge_array[j].starting_vertex_index;
            int v = graph->edge_array[j].ending_vertex_index;

            // 松弛
            if (distance[u].weight.double_value + graph->adj_matrix[u][v].weight.double_value
                < distance[v].weight.double_value)
            {
                distance[v].weight.double_value =
                    distance[u].weight.double_value + graph->adj_matrix[u][v].weight.double_value;
                predecessor[starting_vertex_index][v] = u;
            }
        }
    }

    int has_negative_weight_cycle = FALSE; // 默认没有负权环

    /*
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
     */

    for (int i = 0; i < graph->edge_count; i++) {
        int cur_starting_vertex_index = graph->edge_array[i].starting_vertex_index;
        int cur_ending_vertex_index = graph->edge_array[i].ending_vertex_index;

        if (distance[cur_starting_vertex_index].weight.double_value
            +
            graph->adj_matrix[cur_starting_vertex_index][cur_ending_vertex_index].weight.double_value
            <
            distance[cur_ending_vertex_index].weight.double_value)
        {
            has_negative_weight_cycle = TRUE; // 有负权环
            break;
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
 *     distance[][] is a distance matrix for n vertex_array.
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
