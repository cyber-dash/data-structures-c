/*!
 * @file algorithm.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 图算法源文件
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
#include "min_priority_queue.h"
#include "disjoint_set.h"


/*!
 * @brief <h1>图结点访问函数</h1>
 * @param graph **图**(指针)
 * @param vertex_index **图结点索引**
 * @return 执行结果
 * @note
 */
status_t Visit(matrix_graph_t* graph, int vertex_index) {
    /// 本实现只调用printf, 打印图结点索引
    printf("%d ", vertex_index);
    return OK;
}


/*!
 * <h1>图DFS遍历</h1>
 * @param graph **图**(指针)
 * @param Visit **图结点访问函数**
 * @note
 */
status_t DFSTraverse(matrix_graph_t graph, status_t (*Visit)(matrix_graph_t*, int)) {

    /// ### 1 分配结点遍历数组 ###
    /// &emsp; **if** 内存分配失败 :\n
    /// &emsp;&emsp; 返回NON_ALLOCATED\n
    int* visited_vertex_index_array = (int*)malloc(graph.vertex_count * sizeof(int));
    if (!visited_vertex_index_array) {
        return NON_ALLOCATED;
    }

    /// &emsp; 结点遍历数组每个元素, 赋值为0
    for (int i = 0; i < graph.vertex_count; i++) {
        visited_vertex_index_array[i] = NOT_VISITED;
    }

    /// ### 2 遍历图结点进行DFS ###
    /// &emsp; **for loop** 遍历图结点 :\n
    /// &emsp;&emsp; **if** 当前结点没有被访问(遍历) : \n
    /// &emsp &emsp;&emsp; 对当前结点执行DFSRecursive\n
    for (int i = 0; i < graph.vertex_count; i++) {
        if (!visited_vertex_index_array[i]) {
            DFSRecursive(graph, i, visited_vertex_index_array, Visit);
        }
    }

    return OK;
}


/*!
 * <h1>对结点深度优先遍历(递归)</h1>
 * @param graph **图**
 * @param vertex_index **图结点索引**
 * @param visited_vertex_index_array **已访问结点索引的数组**
 * @param Visit **结点访问函数**
 * @note
 */
void DFSRecursive(matrix_graph_t graph,
                  int vertex_index,
                  int* visited_vertex_index_array,
                  status_t (*Visit)(matrix_graph_t*, int))
{
    /// ### 1 访问索引vertex_index的图结点 ###
    /// &emsp; - 调用Visit函数访问结点\n
    Visit(&graph, vertex_index);
    /// &emsp; - 将索引vertex_index图结点标记为VISITED\n
    visited_vertex_index_array[vertex_index] = VISITED;

    /// ### 2 对索引vertex_index图结点的相邻结点执行递归 ###
    /// &emsp; **for loop** 依次遍历索引vertex_index图结点的相邻各结点 :\n
    for (int i = FirstAdjVertexIdx(&graph, vertex_index); i >= 0; i = NextAdjVertexIndex(&graph, vertex_index, i)) {

        /// &emsp;&emsp; **if** 当前结点已经访问过 :\n
        /// &emsp;&emsp;&emsp; continue\n
        if (visited_vertex_index_array[i] == VISITED) {
            continue;
        }

        // &emsp;&emsp; 当前结点递归执行DFSRecursive\n
        DFSRecursive(graph, i, visited_vertex_index_array, Visit);
    }
}


/*!
 * <h1>图广度优先BFS遍历</h1>
 * @param graph **图**
 * @param Visit **结点访问函数**
 * @note
 */
void BFSTraverse(matrix_graph_t graph, status_t (*Visit)(matrix_graph_t*, int)) {

    /// ### 1 构造visited数组 ###
    /// &emsp; 数组visited_vertex_indexes分配内存 \n
    int* visited_vertex_indexes = (int*)malloc(graph.vertex_count * sizeof(int));

    /// &emsp; **for loop** 遍历图结点 :\n
    for (int i = 0; i < graph.vertex_count; i++) {
        /// &emsp;&emsp; 每个结点都设置成未访问NOT_VISITED \n
        visited_vertex_indexes[i] = NOT_VISITED;
    }

    /// ### 2 初始化空队列 ###
    linked_queue_t queue;
    LinkedQueueInit(&queue);

    /// ### 3 执行BFS遍历 ###
    /// &emsp; **for loop** 遍历图结点 : \n
    for (int i = 0; i < graph.vertex_count; i++) {

        /// &emsp;&emsp; **if** 当前结点已经访问过 : \n
        if (visited_vertex_indexes[i] == VISITED) {
            /// &emsp;&emsp;&emsp; continue \n
            continue;
        }

        /// &emsp;&emsp; 访问当前结点 \n
        Visit(&graph, i);
        /// &emsp;&emsp; 将当前结点设置为已访问 \n
        visited_vertex_indexes[i] = VISITED;
        /// &emsp;&emsp; 当前结点索引入队 \n
        LinkedQueueEnQueue(&queue, i);

        /// &emsp;&emsp; **while** 队列不为空 : \n
        while (!LinkedQueueIsEmpty(&queue)) {

            /// &emsp;&emsp;&emsp; 取当前队头结点 \n
            int vertex_index;
            LinkedQueueDeQueue(&queue, &vertex_index);

            /// &emsp;&emsp;&emsp; **for loop** 遍历当前队头结点的相邻结点 : \n
            for (int neighbor_vertex_index = FirstAdjVertexIdx(&graph, vertex_index);
                 neighbor_vertex_index >= 0;
                 neighbor_vertex_index = NextAdjVertexIndex(&graph, vertex_index, neighbor_vertex_index)
                )
            {
                /// &emsp;&emsp;&emsp;&emsp; **if** 当前相邻结点已被访问 : \n
                if (visited_vertex_indexes[neighbor_vertex_index] == VISITED) {
                    /// &emsp;&emsp;&emsp;&emsp;&emsp; continue \n
                    continue;
                }

                /// &emsp;&emsp;&emsp;&emsp; 访问当前相邻结点 \n
                Visit(&graph, neighbor_vertex_index);
                /// &emsp;&emsp;&emsp;&emsp; 当前相邻结点入队 \n
                LinkedQueueEnQueue(&queue, neighbor_vertex_index);
                /// &emsp;&emsp;&emsp;&emsp; 标记当前相邻结点被访问 \n
                visited_vertex_indexes[neighbor_vertex_index] = VISITED;
            }
        }
    }
}


/*!
 * @brief <h1>Prim最小生成树算法</h1>
 * @param graph **图**(指针)
 * @param min_span_tree **最小生成树**(数组)
 * @note
 */
void Prim(matrix_graph_t* graph, edge_t* min_span_tree) {

    /// ### 1 初始化最小生成树结点索引数组 ###
    /// &emsp; 声明最小生成树结点索引数组mst_vertex_index_set \n
    int mst_vertex_index_set[MAX_VERTEX_CNT];
    /// &emsp; 索引0图结点进入mst_vertex_index_set(加入最小生成树) \n
    mst_vertex_index_set[0] = 0;
    /// &emsp; 最小生成树大小设置为1(只包含1个结点) \n
    int mst_size = 1;

    /// ### 2 初始化边的最小优先队列 ###
    min_priority_queue_t min_priority_queue;
    MinPriorityQueueInit(&min_priority_queue, graph->edge_count);

    /// ### 3 索引0图结点的相邻边全部进入最小优先队列 ###
    for (int i = 1; i < graph->vertex_count; i++) {
        if (graph->adj_matrix[0][i].weight_type == NO_EDGE) {
            continue;
        }

        MinPriorityQueuePush(&min_priority_queue, graph->adj_matrix[0][i]);
    }

    /// ### 4 贪心法构造最小生成树 ###
    /// &emsp; **while** 最小生成树结点数量 != 图结点数量 : \n
    while (mst_size != graph->vertex_count) {

        /// &emsp;&emsp; 取最小优先队列队头(以mst_vertex_index_set中某个结点为起点, 不在这些结点的某个结点为终点的, 最短的边)
        edge_t cur_mst_edge;
        MinPriorityQueuePop(&min_priority_queue, &cur_mst_edge);

        /// &emsp;&emsp; 将当前最短生成树边, 加入到min_span_tree数组 \n
        min_span_tree[mst_size - 1] = cur_mst_edge;
        /// &emsp;&emsp; 将当前最短生成树边的终点, 加入到mst_vertex_index_set \n
        mst_vertex_index_set[mst_size] = cur_mst_edge.ending_vertex_index;
        /// &emsp;&emsp; 当前最短生成树结点数量++ \n
        mst_size++;

        /// &emsp;&emsp; **for loop** 遍历图结点(将结点cur_mst_edge.ending_vertex_index为起点, 终点不在mst_vertex_index_set的边) : \n
        for (int i = 0; i < graph->vertex_count; i++) {
            int in_vertex_set = FALSE;
            for (int k = 0; k < mst_size; k++) {
                if (i == mst_vertex_index_set[k]) {
                    in_vertex_set = TRUE;
                    break;
                }
            }

            /// &emsp;&emsp;&emsp; **if** 当前结点已经在mst_vertex_index_set 或者 边(cur_mst_edge.ending_vertex_index, i)不存在 : \n
            if (in_vertex_set || graph->adj_matrix[cur_mst_edge.ending_vertex_index][i].weight_type == NO_EDGE) {
                /// &emsp;&emsp;&emsp;&emsp; continue \n
                continue;
            }

            /// &emsp;&emsp;&emsp; 将边(cur_mst_edge.ending_vertex_index, i) Push进入最小优先队列 \n
            edge_t cur_adj_edge = graph->adj_matrix[cur_mst_edge.ending_vertex_index][i];
            MinPriorityQueuePush(&min_priority_queue, cur_adj_edge);
        }
    }
}


/*!
 * <h1>Kruskal最小生成树</h1>
 * @param graph **图**(指针)
 * @param min_span_tree **最小生成树**(数组)
 * @note
 */
void Kruskal(matrix_graph_t* graph, edge_t* min_span_tree) {

    /// ### 1 初始化最小优先队列 ###
    /// &emsp; 最小有限队列min_priority_queue \n
    min_priority_queue_t min_priority_queue;
    MinPriorityQueueInit(&min_priority_queue, graph->edge_count);

    /// ### 2 初始化并查集 ###
    /// &emsp; 并查集disjoint_set \n
    disjoint_set_t disjoint_set;
    InitDisjointSet(&disjoint_set, graph->edge_count);

    /// ### 3 将所有边插入到最小优先队列 ###
    /// &emsp; **for loop** 遍历graph->edges : \n
    for (int i = 0; i < graph->edge_count; i++) {
        /// &emsp;&emsp; 将当前边Push到最小优先队列min_priority_queue \n
        MinPriorityQueuePush(&min_priority_queue, graph->edges[i]);
    }

    /// ### 4 执行Kruskal算法核心流程 ###
    /// &emsp; **for loop** 遍历 (图结点数 - 1) 次 : \n
    for (int i = 0; i < graph->vertex_count - 1;) {

        /// &emsp;&emsp; 队头(队中最短边)出队, 赋给cur_edge \n
        edge_t cur_edge;
        MinPriorityQueuePop(&min_priority_queue, &cur_edge);

        /// &emsp;&emsp; 使用并查集, 查到最短边的起点和终点对应的并查集根索引
        int cur_starting_root_index =
            DisjointSetFind(&disjoint_set, cur_edge.starting_vertex_index);
        int cur_ending_root_index =
            DisjointSetFind(&disjoint_set, cur_edge.ending_vertex_index);

        /// &emsp;&emsp; **if** 起点根索引 不等于 终点根索引 : \n
        if (cur_starting_root_index != cur_ending_root_index) {
            /// &emsp;&emsp;&emsp; 并查集合并 \n
            DisjointSetUnion(&disjoint_set, cur_starting_root_index, cur_ending_root_index);

            /// &emsp;&emsp;&emsp; 当前最小边加入到最小生成树 \n
            min_span_tree[i] = cur_edge;
            i++;
        }
    }
}


/*!
 * @brief <h1>打印最小生成树
 * @param min_span_tree **最小生成树**(数组)
 * @param size **最小生成树边数量**
 * @note
 */
void PrintMinSpanTree(MST_t min_span_tree, int size) {
    /// 遍历最小生成树min_span_tree, 打印每一条边的信息
    for (int i = 0; i < size; i++) {
        printf("起始点: %d, 终点: %d, 距离: %lf\n",
               min_span_tree[i].starting_vertex_index,
               min_span_tree[i].ending_vertex_index,
               min_span_tree[i].weight.double_value);
    }

    printf("\n");
}


/*!
 * <h1>迪杰斯特拉(Dijkstra)最短路径</h1>
 * @param graph **图**(指针)
 * @param starting_vertex_index **起点索引**
 * @param predecessor **前驱数组**
 * @param distance **最短路径数组**
 * @note
 * 参数predecessor本实现使用二维数组, 这普遍用在多源最短路径, 单源(如Dijkstra/BellmanFord)可以替换成一维数组, 有兴趣者自己替换:-)
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
            int u = graph->edges[j].starting_vertex_index;
            int v = graph->edges[j].ending_vertex_index;

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
    for (int i = 0; i < graph->edge_count; i++) {
        int cur_starting_vertex_index = graph->edges[i].starting_vertex_index;
        int cur_ending_vertex_index = graph->edges[i].ending_vertex_index;

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
 *     distance[][] is a distance matrix for n vertexes.
 *         distance[i][j] is the distance to move directly from i to j.
 *         if no direct link from i to j
 *             then initialize distance[i][j] = INFINITY
 *         the distance from a node to itself is 0(Initialize distance[i][i] = 0 for all i).
 *     predecessor[][] is a predecessor matrix. it enables you to reconstruct the shortest paths.
 *         predecessor[i][j] should be initialized to i.
 *
 * 算法执行结果:
 *     distance[i][j] contains the total cost along the shortest edge_t from i to j.
 *     predecessor[i][j] contains the predecessor of j on the shortest edge_t from i to j.
 */
void Floyd(matrix_graph_t* graph, int (*predecessor)[MAX_VERTEX_CNT], edge_t (*distance)[MAX_VERTEX_CNT]) {
    int vertex_count = graph->vertex_count;

    for (int starting_vertex_index = 0; starting_vertex_index < vertex_count; starting_vertex_index++) {
        for (int ending_vertex_index = 0; ending_vertex_index < vertex_count; ending_vertex_index++) {

            if (starting_vertex_index == ending_vertex_index) {
                distance[starting_vertex_index][ending_vertex_index].weight_type = DOUBLE;
                distance[starting_vertex_index][ending_vertex_index].weight.double_value = 0;
            } else {
                distance[starting_vertex_index][ending_vertex_index].weight_type = DOUBLE;
                if (graph->adj_matrix[starting_vertex_index][ending_vertex_index].weight.double_value != DBL_MAX) {
                    distance[starting_vertex_index][ending_vertex_index].weight.double_value =
                        graph->adj_matrix[starting_vertex_index][ending_vertex_index].weight.double_value;
                } else {
                    distance[starting_vertex_index][ending_vertex_index].weight.double_value = DBL_MAX;
                }
            }

            predecessor[starting_vertex_index][ending_vertex_index] = starting_vertex_index;
        }
    }

    for (int k = 0; k < vertex_count; k++) {
        for (int i = 0; i < vertex_count; i++) {
            for (int j = 0; j < vertex_count; j++) {
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


void PrintSingleSourceShortestPath(matrix_graph_t* graph,
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


void PrintMultiSourceShortestPath(matrix_graph_t* graph,
                                  edge_t (*distance)[MAX_VERTEX_CNT],
                                  int (*predecessor)[MAX_VERTEX_CNT])
{
    for (int starting_vertex_index = 0; starting_vertex_index < graph->vertex_count; starting_vertex_index++) {
        printf("--- 从起始点%d到其他各顶点的最短路径 ---\n", starting_vertex_index);
        for (int ending_vertex_index = 0; ending_vertex_index < graph->vertex_count; ending_vertex_index++) {
            if (starting_vertex_index == ending_vertex_index) {
                continue;
            }
            printf("起始点%d到结点%d的最短路径为:\n", starting_vertex_index, ending_vertex_index);

            PrintSingleSourceShortestPathRecursive(graph, starting_vertex_index, ending_vertex_index, predecessor);

            printf(", 最短路径长度: %.2lf\n", distance[starting_vertex_index][ending_vertex_index].weight.double_value);
        }
    }
}


/*!
 * 通用单源最短路径打印函数
 * @param graph **图**(指针)
 * @param starting_vertex_index **起点索引**
 * @param ending_vertex_index **终点索引**
 * @param predecessor **前驱数组**
 * @note
 * "多源最短路径和单源最短路径问题, 都可以使用此函数" \n
 */
void PrintSingleSourceShortestPathRecursive(matrix_graph_t* graph,
                                            int starting_vertex_index,
                                            int ending_vertex_index,
                                            int (*predecessor)[MAX_VERTEX_CNT])
{
    /// **if** 起点和终点不是同一结点 : \n
    if (starting_vertex_index != ending_vertex_index) {
        /// &emsp; 终点在本条最短路径(参数起点 --> 参数终点)的前一结点索引为
        /// predecessor[starting_vertex_index][ending_vertex_index] \n
        int predecessor_index_of_ending_vertex = predecessor[starting_vertex_index][ending_vertex_index];
        /// &emsp; 递归调用PrintSingleSourceShortestPathRecursive
        PrintSingleSourceShortestPathRecursive(graph,
                                               starting_vertex_index,
                                               predecessor_index_of_ending_vertex,
                                               predecessor);
    }

    /// 打印终点索引
    printf("%d ", ending_vertex_index);
}
