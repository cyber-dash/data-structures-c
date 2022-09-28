/*!
 * @file algorithm.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 图算法源文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "algorithm.h"
#include "queue.h"
#include "min_priority_queue.h"
#include "disjoint_set.h"


/*!
 * @brief **图结点访问函数**
 * @param graph 图
 * @param vertex_index 图结点索引
 * @return 执行结果
 * @note
 * 图结点访问函数
 * ------------
 * ------------
 *
 * ------------
 * 本实现只调用printf, 打印图结点索引
 */
status_t Visit(matrix_graph_t* graph, int vertex_index) {
    printf("%d ", vertex_index);
    return OK;
}


/*!
 * @brief **图DFS遍历**
 * @param graph 图
 * @param Visit 图结点访问函数
 * @note
 * 图DFS遍历
 * --------
 * --------
 *
 * --------
 */
status_t DFSTraverse(matrix_graph_t graph, status_t (*Visit)(matrix_graph_t*, int)) {

    /// ### 1 分配结点遍历数组 ###
    /// &emsp; **if** 内存分配失败 :\n
    /// &emsp;&emsp; 返回NON_ALLOCATED\n
    int* visited_vertex_indexes = (int*)malloc(graph.vertex_count * sizeof(int));
    if (!visited_vertex_indexes) {
        return NON_ALLOCATED;
    }

    /// &emsp; 结点遍历数组每个元素, 赋值为0
    for (int i = 0; i < graph.vertex_count; i++) {
        visited_vertex_indexes[i] = NOT_VISITED;
    }

    /// ### 2 遍历图结点进行DFS ###
    /// &emsp; **for loop** 遍历图结点 :\n
    /// &emsp;&emsp; **if** 当前结点没有被访问(遍历) : \n
    /// &emsp;&emsp;&emsp; 对当前结点执行DFSRecursive\n
    for (int i = 0; i < graph.vertex_count; i++) {
        if (!visited_vertex_indexes[i]) {
            DFSRecursive(graph, i, visited_vertex_indexes, Visit);
        }
    }

    return OK;
}


/*!
 * @brief **对结点深度优先遍历(递归)**
 * @param graph 图
 * @param vertex_index 图结点索引
 * @param visited_vertex_indexes 已访问结点索引的数组
 * @param Visit 结点访问函数
 * @note
 * 对结点深度优先遍历(递归)
 * ---------------------
 * ---------------------
 * ### 1 访问索引vertex_index的图结点 ###
 * &emsp; - 调用Visit函数访问参数结点\n
 * &emsp; - 将已访问的参数结点标记为VISITED\n
 * ### 2 对索引vertex_index图结点的相邻结点执行递归 ###
 * &emsp; **for loop** 遍历索引vertex_index图结点的相邻各结点 :\n
 * &emsp;&emsp; **if** 当前结点已经访问过 :\n
 * &emsp;&emsp;&emsp; continue\n
 * &emsp;&emsp; 当前结点递归执行DFSRecursive\n
 */
void DFSRecursive(matrix_graph_t graph,
                  int vertex_index,
                  int* visited_vertex_indexes,
                  status_t (*Visit)(matrix_graph_t*, int))
{
    // ----- 1 访问索引vertex_index的图结点 -----

    Visit(&graph, vertex_index);                        // 调用Visit函数访问参数结点
    visited_vertex_indexes[vertex_index] = VISITED;     // 将已访问的参数结点标记为VISITED

    // ----- 2 对索引vertex_index图结点的相邻结点执行递归 -----

    // 遍历索引vertex_index图结点的相邻各结点
    for (int i = FirstAdjVertexIndex(&graph, vertex_index); i >= 0; i = NextAdjVertexIndex(&graph, vertex_index, i)) {

        // if 当前结点已经访问过, continue
        if (visited_vertex_indexes[i] == VISITED) {
            continue;
        }

        // 当前结点递归执行DFSRecursive
        DFSRecursive(graph, i, visited_vertex_indexes, Visit);
    }
}


/*!
 * @brief **图广度优先BFS遍历**
 * @param graph 图
 * @param Visit 结点访问函数
 * @note
 * 图广度优先BFS遍历
 * ---------------
 * ---------------
 *
 * ---------------
 * ### 1 构造visited数组 ###
 * &emsp; 数组visited_vertex_indexes分配内存 \n
 * &emsp; **for loop** 遍历图结点 :\n
 * &emsp;&emsp; 每个结点都设置成未访问NOT_VISITED \n
 * ### 2 初始化空队列 ###
 * ### 3 执行BFS遍历 ###
 * &emsp; **for loop** 遍历图结点 : \n
 * &emsp;&emsp; **if** 当前结点已经访问过 : \n
 * &emsp;&emsp;&emsp; continue \n
 * &emsp;&emsp; 访问当前结点 \n
 * &emsp;&emsp; 将当前结点设置为已访问 \n
 * &emsp;&emsp; 当前结点索引入队 \n
 * &emsp;&emsp; **while** 队列不为空 : \n
 * &emsp;&emsp;&emsp; 取当前队头结点 \n
 * &emsp;&emsp;&emsp; **for loop** 遍历当前队头结点的相邻结点 : \n
 * &emsp;&emsp;&emsp;&emsp; **if** 当前相邻结点已被访问 : \n
 * &emsp;&emsp;&emsp;&emsp;&emsp; continue \n
 * &emsp;&emsp;&emsp;&emsp; 访问当前相邻结点 \n
 * &emsp;&emsp;&emsp;&emsp; 当前相邻结点入队 \n
 * &emsp;&emsp;&emsp;&emsp; 标记当前相邻结点被访问 \n
 */
void BFSTraverse(matrix_graph_t graph, status_t (*Visit)(matrix_graph_t*, int)) {

    // ----- 1 构造visited数组 -----
    int* visited_vertex_indexes = (int*)malloc(graph.vertex_count * sizeof(int)); // 数组visited_vertex_indexes分配内存

    for (int i = 0; i < graph.vertex_count; i++) {  // for loop 遍历图结点 :
        visited_vertex_indexes[i] = NOT_VISITED;        // 每个结点都设置成未访问NOT_VISITED
    }

    // ----- 2 初始化空队列 -----
    linked_queue_t queue;
    LinkedQueueInit(&queue);

    // ----- 3 执行BFS遍历 -----
    for (int i = 0; i < graph.vertex_count; i++) {  // for loop 遍历图结点 :

        if (visited_vertex_indexes[i] == VISITED) {     // if 当前结点已经访问过 :
            continue;
        }

        Visit(&graph, i);                       // 访问当前结点
        visited_vertex_indexes[i] = VISITED;    // 将当前结点设置为已访问
        LinkedQueueEnQueue(&queue, i);          // 当前结点索引入队

        while (!LinkedQueueIsEmpty(&queue)) {   // while 队列不为空 :

            int vertex_index;
            LinkedQueueDeQueue(&queue, &vertex_index);  // 取当前队头结点

            // for loop 遍历当前队头结点的相邻结点
            for (int neighbor_vertex_index = FirstAdjVertexIndex(&graph, vertex_index);
                 neighbor_vertex_index >= 0;
                 neighbor_vertex_index = NextAdjVertexIndex(&graph, vertex_index, neighbor_vertex_index)
                )
            {
                if (visited_vertex_indexes[neighbor_vertex_index] == VISITED) { // if 当前相邻结点已被访问
                    continue;
                }

                Visit(&graph, neighbor_vertex_index);                       // 访问当前相邻结点

                LinkedQueueEnQueue(&queue, neighbor_vertex_index);          // 当前相邻结点入队
                visited_vertex_indexes[neighbor_vertex_index] = VISITED;    // 标记当前相邻结点被访问
            }
        }
    }
}


/*!
 * @brief @brief **索引index结点是否在最小生成树中**
 * @param mst_vertex_index_set 最小生成树结点索引集合(数组)
 * @param index 结点索引
 * @param mst_vertex_count 最小生成树当前大小(结点数)
 * @return 结果(在或者不在)
 * @note
 * 索引index结点是否在最小生成树中
 * ----------------------------
 * ----------------------------
 * **for loop** 遍历最小生成树结点(用来检查是否已经在最小生成树) : \n
 * &emsp; **if** 当前最小生成树结点索引 == 当前图结点 : \n
 * &emsp;&emsp; in_mst为TRUE(在最小生成树) \n
 * &emsp; 跳出循环 \n
 * 返回in_mst \n
 */
int isInMstVertexIndexSet(const int* mst_vertex_index_set, int index, int mst_vertex_count) {
    int in_mst = FALSE; // 变量in_mst表示当前结点是否在最小生成树中, 初始化FALSE
    for (int i = 0; i < mst_vertex_count; i++) {
        if (index == mst_vertex_index_set[i]) {
            in_mst = TRUE;
            break;
        }
    }

    return in_mst;
}

/*!
 * @brief **Prim最小生成树算法**
 * @param graph 图(指针)
 * @param min_span_tree 最小生成树(数组)
 * @note
 * Prim最小生成树算法
 * ----------------
 * ----------------
 * - 初始化最小生成树结点索引数组 \n
 * &emsp; 声明最小生成树结点索引数组mst_vertex_index_set(标记哪个结点进入最小生成树) \n
 * &emsp; 索引0结点进入mst_vertex_index_set(加入最小生成树) \n
 * &emsp; 最小生成树大小设置为1(只包含索引0结点) \n
 * - 初始化边的最小优先队列 \n
 * - 索引0结点的相邻边全部进入最小优先队列 \n
 * &emsp; **for loop** 遍历所有结点: \n
 * &emsp;&emsp; **if** 边(0 --> 当前结点索引i)不存在: \n
 * &emsp;&emsp;&emsp; continue \n
 * &emsp;&emsp; 边(0 --> i)入队最小优先队列min_priority_queue \n
 * - 贪心法构造最小生成树 \n
 * &emsp; **while** 最小生成树结点数量 < 图结点数量 : \n
 * &emsp;&emsp; 取最小优先队列队头(以mst_vertex_index_set中某个结点为起点, 不在这些结点集合内的某个结点为终点的, 最短的边)
 * 并出队 \n
 * &emsp;&emsp; 将队头(最短边), 加入到min_span_tree数组 \n
 * &emsp;&emsp; 将队头(最短边)的终点, 加入到mst_vertex_index_set \n
 * &emsp;&emsp; 当前最短生成树结点数量++ \n
 * &emsp;&emsp; 将队头(最短边)的终点为起点, 终点不在mst_vertex_index_set的边, 全部入队最小优先队列 \n
 * &emsp;&emsp;&emsp; **for loop** 遍历图结点(作为终点) : \n
 * &emsp;&emsp;&emsp;&emsp; 检查当前结点是否已在最小生成树 \n
 * &emsp;&emsp;&emsp;&emsp; **if** 当前结点已经在最小生成树 or 边(cur_mst_edge.ending_vertex_index --> i)不存在 : \n
 * &emsp;&emsp;&emsp;&emsp;&emsp; continue \n
 * &emsp;&emsp;&emsp;&emsp; 将边(cur_mst_edge.ending_vertex_index --> i) 入队最小优先队列 \n
 */
void Prim(matrix_graph_t* graph, edge_t* min_span_tree) {

    // ----- 初始化最小生成树结点索引数组 -----
    int mst_vertex_index_set[MAX_VERTEX_CNT];   // 声明最小生成树结点索引数组mst_vertex_index_set
    mst_vertex_index_set[0] = 0;                // 索引0结点进入mst_vertex_index_set(加入最小生成树)
    int mst_vertex_count = 1;                           // 最小生成树大小设置为1(只包含索引0结点)

    // ----- 初始化边的最小优先队列 -----
    min_priority_queue_t min_priority_queue;
    MinPriorityQueueInit(&min_priority_queue, graph->edge_count);

    // ----- 索引0结点的邻接边, 全部进入最小优先队列 -----
    for (int i = 1; i < graph->vertex_count; i++) {
        if (graph->adj_matrix[0][i].weight_type == NO_EDGE) {
            continue;
        }

        MinPriorityQueuePush(&min_priority_queue, graph->adj_matrix[0][i]);
    }

    // ----- 贪心法构造最小生成树 -----
    while (mst_vertex_count < graph->vertex_count) {    // while 最小生成树结点数量 < 图结点数量 (最小生成树未构造完)

        // 取最小优先队列队头(以mst_vertex_index_set中某个结点为起点, 不在这些结点的某个结点为终点的, 最短的边), 并出队
        edge_t cur_mst_edge;
        MinPriorityQueuePop(&min_priority_queue, &cur_mst_edge);

        // 将当前最短边, 加入到最小生成树
        min_span_tree[mst_vertex_count - 1] = cur_mst_edge;
        // 将当前最短生成树边的终点, 加入到mst_vertex_index_set
        mst_vertex_index_set[mst_vertex_count] = cur_mst_edge.ending_vertex_index;
        // 当前最短生成树结点数量++
        mst_vertex_count++;

        // --- 将队头(最短边)的终点为起点, 终点不在mst_vertex_index_set的边, 全部入队最小优先队列 ---

        for (int i = 0; i < graph->vertex_count; i++) { // for loop 遍历图结点(作为终点)

            // 变量in_vertex_set表示当前结点是否在最小生成树中, 在TRUE, 不在FALSE
            // if 当前结点已经在mst_vertex_index_set 或者 边(cur_mst_edge.ending_vertex_index, i)不存在: continue
            int in_mst = isInMstVertexIndexSet(mst_vertex_index_set, i, mst_vertex_count);
            if (in_mst ||
                graph->adj_matrix[cur_mst_edge.ending_vertex_index][i].weight_type == NO_EDGE
            ) {
                continue;
            }

            // 将边(cur_mst_edge.ending_vertex_index --> i) 入队最小优先队列
            edge_t cur_adj_edge = graph->adj_matrix[cur_mst_edge.ending_vertex_index][i];
            MinPriorityQueuePush(&min_priority_queue, cur_adj_edge);
        }
    }
}


/*!
 * @brief **Kruskal最小生成树**
 * @param graph 图(指针)
 * @param min_span_tree 最小生成树(数组)
 * @note
 * Kruskal最小生成树
 * ----------------
 * ----------------
 *
 * ----------------
 * ### 1 初始化 ###
 * &emsp; 最小优先队列min_priority_queue初始化 \n
 * &emsp; 并查集disjoint_set初始化 \n
 * ### 2 所有边插入到最小优先队列 ###
 * &emsp; **for loop** 遍历图所有的边: \n
 * &emsp;&emsp; 将当前边Push到最小优先队列min_priority_queue \n
 * ### 3 贪心 ###
 * &emsp; **for loop** 遍历 (图结点数 - 1) 次 : \n
 * &emsp;&emsp; 最小优先队列队头(队中最短边)出队, 赋给当前最短边cur_min_dist_edge \n
 * &emsp;&emsp; 使用并查集, 查到cur_min_dist_edge的起点和终点对应的并查集根索引 \n
 * &emsp;&emsp; **if** 起点根索引 不等于 终点根索引 : \n
 * &emsp;&emsp;&emsp; 并查集合并 \n
 * &emsp;&emsp;&emsp; 当前最小边加入到最小生成树 \n
 */
void Kruskal(matrix_graph_t* graph, edge_t* min_span_tree) {

    // ----- 1 初始化 -----

    // 最小优先队列min_priority_queue初始化
    min_priority_queue_t min_priority_queue;
    MinPriorityQueueInit(&min_priority_queue, graph->edge_count);

    // 并查集disjoint_set初始化
    disjoint_set_t disjoint_set;
    InitDisjointSet(&disjoint_set, graph->edge_count);

    // ----- 2 所有边插入到最小优先队列 -----
    for (int i = 0; i < graph->edge_count; i++) {   // 遍历图所有的边
        MinPriorityQueuePush(&min_priority_queue, graph->edges[i]); // 将当前边Push到最小优先队列min_priority_queue
    }

    // ----- 3 贪心 -----
    for (int i = 0; i < graph->vertex_count - 1;) { // 遍历 (图结点数 - 1) 次

        // 最小优先队列队头(队中最短边)出队, 赋给当前最短边cur_min_dist_edge
        edge_t cur_min_dist_edge;
        MinPriorityQueuePop(&min_priority_queue, &cur_min_dist_edge);

        // 使用并查集, 查到cur_edge的起点和终点对应的并查集根索引
        int cur_starting_root_index =
            DisjointSetFind(&disjoint_set, cur_min_dist_edge.starting_vertex_index);
        int cur_ending_root_index =
            DisjointSetFind(&disjoint_set, cur_min_dist_edge.ending_vertex_index);

        if (cur_starting_root_index != cur_ending_root_index) { // if 起点根索引 不等于 终点根索引
            DisjointSetUnion(&disjoint_set, cur_starting_root_index, cur_ending_root_index);    // 并查集合并
            min_span_tree[i] = cur_min_dist_edge;    // 当前最小边加入到最小生成树
            i++;
        }
    }
}


/*!
 * @brief **打印最小生成树**
 * @param min_span_tree 最小生成树(数组)
 * @param size 最小生成树边数量
 * @note
 * 打印最小生成树
 * ------------
 * ------------
 *
 * ------------
 * 遍历最小生成树min_span_tree, 打印每一条边的信息
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
 * @brief **迪杰斯特拉(Dijkstra)最短路径**
 * @param graph 图
 * @param starting_vertex_index 起点索引
 * @param predecessor 前驱数组
 * @param distance 最短路径数组
 * @note
 * 迪杰斯特拉(Dijkstra)最短路径
 * --------------------------
 * --------------------------
 *
 * --------------------------
 *
 * 参数predecessor本实现使用二维数组, 这普遍用在多源最短路径, 单源(如Dijkstra/BellmanFord)可以替换成一维数组, 有兴趣者自己替换:-)
 *
 * --------------------------
 * ### 1 初始化 ###
 * - 结点索引数组vertex_index_set初始化\n
 * &emsp;每个结点都不在集合中 \n
 * - distance数组初始化 \n
 * &emsp; distance[起始点之外其他结点]的路径距离值为DBL_MAX(double类型最大值) \n
 * &emsp; distance[起始点]的路径距离值为0 \n
 * - 最小优先队列初始化 \n
 * &emsp; 路径(起始点 --> 起始点)入队 \n
 * ### 2 贪心 ###
 * &emsp; **while** 最小优先队列不为空 : \n
 * &emsp;&emsp; 队头出队, 保存在当前最短路径cur_min_distance \n
 * &emsp;&emsp; 当前最短路径的终点, 设置为已经处理 \n
 * &emsp;&emsp; **while** 遍历图结点 : \n
 * &emsp;&emsp;&emsp; **if** 索引i结点已处理过(不需要再处理) or 当前最短路径终点与索引i结点之间没有边(无法执行松弛) : \n
 * &emsp;&emsp;&emsp;&emsp; continue \n
 * &emsp;&emsp;&emsp; **松弛**, RELAX(当前最短路径终点, 结点i) : \n
 * &emsp;&emsp;&emsp;&emsp; **if** 路径(起点 --> 当前最短路径终点) + 边(当前最短路径终点 --> 结点i) < 路径(起点 --> 结点i) :\n
 * &emsp;&emsp;&emsp;&emsp;&emsp; 当前最短路径终点, 赋值给结点i在路径(起点 --> 结点i)的前一结点 \n
 * &emsp;&emsp;&emsp;&emsp;&emsp; 路径(起点 --> 结点i)进入最小优先队列 \n
 */
void Dijkstra(matrix_graph_t* graph, int starting_vertex_index, int(*predecessor)[MAX_VERTEX_CNT], edge_t* distance) {

    // ----- 1 初始化 -----
    // 结点索引数组vertex_index_set初始化
    int* vertex_index_set = (int*)malloc(graph->vertex_count * sizeof(int));
    // 每个结点都不在集合中
    memset(vertex_index_set, 0, graph->vertex_count * sizeof(int));

    // distance数组(distance[i]表示路径(起始点 --> 索引i结点)的距离)初始化
    // distance[起始点之外其他结点索引]的路径距离值为DBL_MAX(double类型最大值)
    for (int i = 0; i < graph->vertex_count; i++) {
        distance[i].weight_type = DOUBLE;
        distance[i].weight.double_value = DBL_MAX;
    }
    // distance[起始点索引]的路径距离值为0
    distance[starting_vertex_index].weight.double_value = 0;

    // 最小优先队列初始化
    min_priority_queue_t min_priority_queue;
    MinPriorityQueueInit(&min_priority_queue, graph->vertex_count);
    // 路径(起始点 --> 起始点)入队
    MinPriorityQueuePush(&min_priority_queue, graph->adj_matrix[starting_vertex_index][starting_vertex_index]);

    // ----- 2 贪心 -----

    while (min_priority_queue.size != 0) {  // while 最小优先队列不为空

        // 队头出队, 保存在当前最短路径cur_min_distance
        path_t cur_min_distance;
        MinPriorityQueuePop(&min_priority_queue, &cur_min_distance);

        // 当前最短路径的终点, 设置为已经处理 \n
        vertex_index_set[cur_min_distance.ending_vertex_index] = TRUE;

        for (int i = 0; i < graph->vertex_count; i++) { // 遍历图结点

            // if 索引i结点已处理过(不需要再处理) or 当前最短路径终点与索引i结点之间没有边(无法执行松弛)
            if (vertex_index_set[i] == TRUE ||
                graph->adj_matrix[cur_min_distance.ending_vertex_index][i].weight_type == NO_EDGE)
            {
                continue;
            }

            // 松弛: RELAX(当前最短路径终点, 结点i)
            // if 路径(起点 --> 当前最短路径终点) + 边(当前最短路径终点 --> 结点i) < 路径(起点 --> 结点i)
            if (distance[cur_min_distance.ending_vertex_index].weight.double_value
                +
                graph->adj_matrix[cur_min_distance.ending_vertex_index][i].weight.double_value
                <
                distance[i].weight.double_value)
            {
                // 路径(起点 --> 结点i) = 路径(起点 --> 当前最短路径终点) + 边(当前最短路径终点 --> 结点i)
                distance[i].weight.double_value =
                    distance[cur_min_distance.ending_vertex_index].weight.double_value
                    +
                    graph->adj_matrix[cur_min_distance.ending_vertex_index][i].weight.double_value;
                distance[i].ending_vertex_index = i;

                // 当前最短路径终点, 赋值给结点i在路径(起点 --> 结点i)的前一结点 \n
                predecessor[starting_vertex_index][i] = cur_min_distance.ending_vertex_index;

                // 路径(起点 --> 结点i)进入最小优先队列 \n
                MinPriorityQueuePush(&min_priority_queue, distance[i]);
            }
        }
    }
}


/*!
 * @brief **贝尔曼福特(Bellman-Ford)最短路径**
 * @param graph 图
 * @param starting_vertex_index 起点索引
 * @param predecessor 前驱数组
 * @param distance 最短路径数组
 * @return 是否含有负权环
 * @note
 * 贝尔曼福特(Bellman-Ford)最短路径
 * ------------------------------
 * ------------------------------
 * ```
 * function BellmanFord(list vertices, list edges, vertex source) is
 *
 *      // This implementation takes in a graph, represented as
 *      // lists of vertices (represented as integers [0..n-1]) and edges,
 *      // and fills two arrays (distance and predecessor) holding
 *      // the shortest path from the source to each vertex
 *
 *      distance := list of size n
 *      predecessor := list of size n
 *
 *      // Step 1: initialize graph
 *      for each vertex v in vertices do
 *          distance[v] := inf             // Initialize the distance to all vertices to infinity
 *          predecessor[v] := null         // And having a null predecessor
 *
 *      distance[source] := 0              // The distance from the source to itself is, of course, zero
 *
 *      // Step 2: relax edges repeatedly
 *      repeat |V|−1 times:
 *          for each edge (u, v) with weight w in edges do
 *              if distance[u] + w < distance[v] then
 *                  distance[v] := distance[u] + w
 *                  predecessor[v] := u
 *
 *      // Step 3: check for negative-weight cycles
 *      for each edge (u, v) with weight w in edges do
 *          if distance[u] + w < distance[v] then
 *              // Step 4: find a negative-weight cycle
 *              negativeloop := [v, u]
 *              repeat |V|−1 times:
 *                  u := negativeloop[0]
 *                  for each edge (u, v) with weight w in edges do
 *                      if distance[u] + w < distance[v] then
 *                          negativeloop := concatenate([v], negativeloop)
 *              find a cycle in negativeloop, let it be ncycle
 *              // use any cycle detection algorithm here
 *              error "Graph contains a negative-weight cycle", ncycle
 *
 *      return distance, predecessor
 * ```
 * ### 1 初始化 ###
 * &emsp;**for loop** 遍历图结点索引 : \n
 * &emsp;&emsp; **if** 索引i等于起点索引 : \n
 * &emsp;&emsp;&emsp; distance[i] = 0; \n
 * &emsp;&emsp; **else** (索引i不等于起点索引) : \n
 * &emsp;&emsp;&emsp; distance[i] = DBL_MAX;(没有路径) \n
 * &emsp;路径(起点 --> 起点), 起点的前驱结点索引设为-1
 * ### 2 动态规划 ###
 * &emsp;**for loop** 遍历 "图结点数 - 1" 次 : \n
 * &emsp;&emsp; **for loop** 遍历 "图边数" 次 : \n
 * &emsp;&emsp;&emsp; u为边graph->edges[j]的起点索引 \n
 * &emsp;&emsp;&emsp; v为边graph->edges[j]的终点索引 \n
 * &emsp;&emsp;&emsp; **松弛**, RELAX(u, v) : \n
 * &emsp;&emsp;&emsp;&emsp; **if** distance[u] + weight(u, v) < distance[v] \n
 * &emsp;&emsp;&emsp;&emsp;&emsp; distance[v] = distance[u] + weight(u, v); \n
 * ### 3 判断是否有负权环 ###
 * &emsp;**for loop** 遍历 "图结点数 - 1" 次 : \n
 * &emsp;&emsp; **for loop** 遍历 "图边数" 次 : \n
 * &emsp;&emsp;&emsp; u为边graph->edges[j]的起点索引 \n
 * &emsp;&emsp;&emsp; v为边graph->edges[j]的终点索引 \n
 * &emsp;&emsp;&emsp; **if** distance[u] + weight(u, v) < distance[v] : \n
 * &emsp;&emsp;&emsp;&emsp; 有负权环 \n
 * &emsp;返回是否有负权环 \n
 */
int BellmanFord(matrix_graph_t* graph,
                int starting_vertex_index,
                int (*predecessor)[MAX_VERTEX_CNT],
                path_t* distance)
{
    // ----- 1 初始化 -----

    for (int i = 0; i < graph->vertex_count; i++) { // for loop 遍历图结点索引
        if (i == starting_vertex_index) {   // if 索引i等于起点索引
            distance[i].weight.double_value = 0;
        } else {    // else (索引i不等于起点索引)
            distance[i].weight.double_value = DBL_MAX;  // 没有路径
        }
    }

    predecessor[starting_vertex_index][starting_vertex_index] = -1; // 路径(起点 --> 起点), 起点的前驱结点索引设为-1

    // ----- 2 动态规划 -----

    for (int i = 0; i < graph->vertex_count - 1; i++) { // for loop 遍历 "图结点数 - 1" 次
        for (int j = 0; j < graph->edge_count; j++) {   // for loop 遍历 "图边数" 次
            int u = graph->edges[j].starting_vertex_index;  // u为边graph->edges[j]的起点索引
            int v = graph->edges[j].ending_vertex_index;    // v为边graph->edges[j]的终点索引

            // 松弛, RELAX(u, v) :
            // if distance[u] + weight(u, v) < distance[v]
            if (distance[u].weight.double_value + graph->adj_matrix[u][v].weight.double_value
                < distance[v].weight.double_value)
            {
                // distance[v] = distance[u] + weight(u, v);
                distance[v].weight.double_value =
                    distance[u].weight.double_value + graph->adj_matrix[u][v].weight.double_value;
                predecessor[starting_vertex_index][v] = u;  // 路径(starting_vertex_index, v), v的前驱结点, 被赋值为u
            }
        }
    }

    // ----- 3 判断是否有负权环 -----
    int has_negative_weight_cycle = FALSE; // 默认没有负权环
    for (int i = 0; i < graph->edge_count; i++) {   // for loop 遍历图所有边
        int u = graph->edges[i].starting_vertex_index;  // u为边graph->edges[j]的起点索引
        int v = graph->edges[i].ending_vertex_index;    // v为边graph->edges[j]的终点索引

        // if distance[u] + weight(u, v) < distance[v]
        if (distance[u].weight.double_value
            +
            graph->adj_matrix[u][v].weight.double_value
            <
            distance[v].weight.double_value)
        {
            has_negative_weight_cycle = TRUE; // 有负权环
            break;  // 跳出循环
        }
    }

    return has_negative_weight_cycle;   // 返回是否有负权环
}


/*!
 * @brief **弗洛伊德(Floyd)算法**
 * @param graph 图
 * @param predecessor 前驱数组
 * @param distance 最短路径数组
 * @note
 * 弗洛伊德(Floyd)算法
 * ------------------
 * ------------------
 * ```
 * 弗洛伊德算法:
 *      distance[][] is a distance matrix for n vertexes.
 *          distance[i][j] is the distance to move directly from i to j.
 *          if no direct link from i to j
 *              then initialize distance[i][j] = INFINITY
 *          the distance from a node to itself is 0(Initialize distance[i][i] = 0 for all i).
 *      predecessor[][] is a predecessor matrix. it enables you to reconstruct the shortest paths.
 *          predecessor[i][j] should be initialized to i.
 *
 * 算法执行结果:
 *      distance[i][j] contains the total cost along the shortest edge_t from i to j.
 *      predecessor[i][j] contains the predecessor of j on the shortest edge_t from i to j.
 * ```
 * ### 1 初始化distance和predecessor ###
 * &emsp; **for loop** 遍历图结点, 作为起点 : \n
 * &emsp;&emsp; **for loop** 遍历图结点, 作为终点 : \n
 * &emsp;&emsp;&emsp; **if** 当前起点 等于 当前终点 : \n
 * &emsp;&emsp;&emsp;&emsp; 最短路径(当前起点 --> 当前终点)的值设置为0 \n
 * &emsp;&emsp;&emsp; **else** (当前起点 不等于 当前终点) : \n
 * &emsp;&emsp;&emsp;&emsp; **if** 当前起点到当前终点存在边 : \n
 * &emsp;&emsp;&emsp;&emsp;&emsp; 最短路径(当前起点 --> 当前终点)的值设置为边长 \n
 * &emsp;&emsp;&emsp;&emsp; **else** (当前起点到当前终点不存在边) : \n
 * &emsp;&emsp;&emsp;&emsp;&emsp; 最短路径(当前起点 --> 当前终点)的值设置为极大值(不存在路径) \n
 * &emsp;&emsp;&emsp; 当前终点在最短路径(当前起点 --> 当前终点)的前一结点, 被赋值为当前起点 \n
 * ### 2 动态规划求最短路径 ###
 * &emsp; **for loop** 遍历图结点, 作为中转结点intermediate :\n
 * &emsp;&emsp; **for loop** 遍历图结点, 作为起点start :\n
 * &emsp;&emsp;&emsp; **for loop** 遍历图结点, 作为终点end :\n
 * &emsp;&emsp;&emsp;&emsp; **松弛**, RELAX(intermediate, end) : \n
 * &emsp;&emsp;&emsp;&emsp;&emsp; **if** 路径(start --> intermediate) +
 * 路径(intermediate --> end) < 路径(start --> end) :\n
 * &emsp;&emsp;&emsp;&emsp;&emsp;&emsp; 路径(start --> end) <----
 * 路径(start --> intermediate) + 路径(intermediate --> end) \n
 * &emsp;&emsp;&emsp;&emsp;&emsp;&emsp; end结点在最短路径(start --> end)中的前一结点, 被赋值为intermediate \n
 */
void Floyd(matrix_graph_t* graph, int (*predecessor)[MAX_VERTEX_CNT], edge_t (*distance)[MAX_VERTEX_CNT]) {

    for (int start = 0; start < graph->vertex_count; start++) { // 遍历图结点, 作为起点
        for (int end = 0; end < graph->vertex_count; end++) {       // 遍历图结点, 作为终点

            if (start == end) {                             // if 当前起点 等于 当前终点
                distance[start][end].weight_type = DOUBLE;
                distance[start][end].weight.double_value = 0;   // 最短路径(当前起点 --> 当前终点)的值设置为0
            } else {                                        // 当前起点 不等于 当前终点
                distance[start][end].weight_type = DOUBLE;
                if (graph->adj_matrix[start][end].weight.double_value != DBL_MAX) { // if 当前起点到当前终点存在边
                    // 最短路径(当前起点 --> 当前终点)的值设置为边长
                    distance[start][end].weight.double_value = graph->adj_matrix[start][end].weight.double_value;
                } else {    // 当前起点到当前终点不存在边
                    // 最短路径(当前起点 --> 当前终点)的值设置为极大值(不存在路径)
                    distance[start][end].weight.double_value = DBL_MAX;
                }
            }

            predecessor[start][end] = start;    // 当前终点在最短路径(当前起点 --> 当前终点)的前一结点, 被赋值为当前起点
        }
    }

    // 遍历图结点, 作为中转结点intermediate
    for (int intermediate = 0; intermediate < graph->vertex_count; intermediate++) {
        for (int start = 0; start < graph->vertex_count; start++) {     // 遍历图结点, 作为起点start
            for (int end = 0; end < graph->vertex_count; end++) {           // 遍历图结点, 作为终点end

                // 松弛: RELAX(intermediate, end)
                // if 路径(start --> intermediate) + 路径(intermediate --> end) < 路径(start --> end) :
                if (distance[start][intermediate].weight.double_value
                    +
                    distance[intermediate][end].weight.double_value
                    <
                    distance[start][end].weight.double_value
                ) {
                    // 路径(start --> end) = 路径(start --> intermediate) + 路径(intermediate --> end)
                    distance[start][end].weight.double_value =
                        distance[start][intermediate].weight.double_value
                        +
                        distance[intermediate][end].weight.double_value;

                    // end结点在最短路径(start --> end)中的前一结点, 被赋值为intermediate
                    predecessor[start][end] = predecessor[intermediate][end];
                }

            }
        }
    }
}


/*!
 * @brief **通用单源最短路径打印函数**
 * @param graph 图
 * @param start 起点索引
 * @param predecessor 前驱数组
 * @param distance 最短路径数组
 * @note
 * 通用单源最短路径打印函数
 * ---------------------
 * ---------------------
 * **for loop** 遍历图结点(作为终点) : \n
 * &emsp; **if** 当前终点为起点本身 : \n
 * &emsp;&emsp; 不做处理, continue \n
 * &emsp; 调用PrintSingleSourceShortestPathRecursive打印(起点-->当前终点)的单源最短路径 \n
 * &emsp; 打印(起点-->当前终点)的单源最短路径的长度 \n
 */
void PrintSingleSourceShortestPath(matrix_graph_t* graph,
                                   int start,
                                   int (*predecessor)[MAX_VERTEX_CNT],
                                   edge_t* distance)
{
    for (int end = 0; end < graph->vertex_count; end++) {   // 遍历图结点(作为终点)
        if (end == start) { // if 当前终点为起点本身
            continue;           // 不做处理, continue
        }

        // 调用PrintSingleSourceShortestPathRecursive打印(起点-->当前终点)的单源最短路径 \n
        printf("起始点%d到结点%d的最短路径为:\n", start, end);
        PrintSingleSourceShortestPathRecursive(graph, start, end, predecessor);

        // 显示(起点-->当前终点)的单源最短路径的长度
        printf(", ");
        printf("最短路径长度为: %.2lf\n", distance[end].weight.double_value);
    }
}


/*!
 * @brief **多源最短路径打印函数**
 * @param graph 图
 * @param distance 最短路径数组
 * @param predecessor 前驱数组
 * @note
 * 多源最短路径打印函数
 * ------------------
 * ------------------
 * **for loop** 遍历图结点(作为起点start) : \n
 * &emsp; **for loop** 遍历图结点(作为终点end) : \n
 * &emsp;&emsp; **if** start和end相同 : \n
 * &emsp;&emsp;&emsp; 不作处理continue \n
 * &emsp;&emsp; 调用PrintSingleSourceShortestPathRecursive打印单源最短路径 \n
 * &emsp;&emsp; 打印(start-->end)最短路径长度 \n
 */
void PrintMultiSourceShortestPath(matrix_graph_t* graph,
                                  edge_t (*distance)[MAX_VERTEX_CNT],
                                  int (*predecessor)[MAX_VERTEX_CNT])
{
    for (int start = 0; start < graph->vertex_count; start++) { // 遍历图结点(作为起点start)
        printf("--- 从起始点%d到其他各顶点的最短路径 ---\n", start);
        for (int end = 0; end < graph->vertex_count; end++) {       // 遍历图结点(作为终点end)

            if (start == end) { // if start和end相同
                continue;           // 不作处理continue
            }

            // 调用PrintSingleSourceShortestPathRecursive打印单源最短路径
            printf("起始点%d到结点%d的最短路径为: ", start, end);
            PrintSingleSourceShortestPathRecursive(graph, start, end, predecessor);

            // 打印最短路径长度
            printf(", 最短路径长度: %.2lf\n", distance[start][end].weight.double_value);
        }
        printf("\n");
    }
}


/*!
 * @brief **通用单源最短路径打印函数(递归)**
 * @param graph 图
 * @param start 起点索引
 * @param end 终点索引
 * @param predecessor 前驱数组
 * @note
 * 通用单源最短路径打印函数(递归)
 * ---------------------------
 * ---------------------------
 *
 * "多源最短路径和单源最短路径问题, 都可以使用此函数"
 *
 * ---------------------------
 * **if** 起点和终点不是同一结点 : \n
 * &emsp; 终点在本条最短路径(参数起点 --> 参数终点)的前一结点索引为predecessor[start][end] \n
 * &emsp; 递归调用PrintSingleSourceShortestPathRecursive\n
 * 打印终点索引\n
 */
void PrintSingleSourceShortestPathRecursive(matrix_graph_t* graph,
                                            int start,
                                            int end,
                                            int (*predecessor)[MAX_VERTEX_CNT])
{
    if (start != end) { // if 起点和终点不是同一结点

        // 终点在本条最短路径(参数起点 --> 参数终点)的前一结点索引为predecessor[start][end]
        int predecessor_of_end = predecessor[start][end];

        // 递归调用PrintSingleSourceShortestPathRecursive
        PrintSingleSourceShortestPathRecursive(graph, start, predecessor_of_end, predecessor);
    }

    printf("%d ", end); // 打印终点索引
}
