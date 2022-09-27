/*!
 * @file matrix_graph.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 邻接矩阵图源文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdio.h>
#include <float.h>
#include "matrix_graph.h"


/*
此函数未使用
status_t LocateVertex(matrix_graph_t graph, VERTEX_TYPE vertex, int* vertex_index) {
    for (int i = 0; i < graph.vertex_count; i++) {
        if (graph.vertexes[i] == vertex) {
            *vertex_index = i;
            return OK;
        }
    }

    return ERROR;
}
 */


/*!
 * @brief **获取某结点的第一个邻接节点的索引**
 * @param graph 图(指针)
 * @param vertex_index 结点索引
 * @return 第一个邻接节点的索引
 * @note
 * 获取某结点的第一个邻接节点的索引
 * ----------------------------
 * ----------------------------
 *
 * ----------------------------
 * **for loop** 遍历图结点 : \n
 * &emsp; **if** i不等于vertex_index 并且 边(vertex_index --> i)存在 : \n
 * &emsp;&emsp; 返回i \n
 * 返回-1 \n
 */
int FirstAdjVertexIndex(matrix_graph_t* graph, int vertex_index) {
    for (int i = 0; i < graph->vertex_count; i++) { // for loop 遍历图结点
        // if i不等于vertex_index 并且 边(vertex_index --> i)存在
        if (i != vertex_index && graph->adj_matrix[vertex_index][i].weight_type != NO_EDGE) {
            return i;   // 返回i
        }
    }

    return -1;    // 返回-1
}


/*!
 * @brief **获取索引vertex_index结点, adj_vertex_index之外的下一个邻接节点索引**
 * @param graph 图(指针)
 * @param vertex_index 结点索引
 * @param adj_vertex_index 一个邻接节点索引
 * @return 下一个邻接结点的索引
 * @note
 * 获取索引vertex_index结点, adj_vertex_index之外的下一个邻接节点索引
 * -------------------------------------------------------------
 * -------------------------------------------------------------
 *
 * -------------------------------------------------------------
 *
 * 如果存在下一邻接节点, 返回其索引, 否则返回-1
 *
 * -------------------------------------------------------------
 * &emsp; **if** 当前邻接节点的索引为"结点数 - 1" : \n
 * &emsp;&emsp; 返回-1\n
 * &emsp; **for loop** 遍历所有结点 :\n
 * &emsp;&emsp; **if** 遍历结点索引不等于结点索引 and 结点与遍历结点之间存在边 : \n
 * &emsp;&emsp;&emsp; 返回遍历结点索引\n
 * &emsp; 返回-1
 */
int NextAdjVertexIndex(matrix_graph_t* graph, int vertex_index, int adj_vertex_index) {
    if (adj_vertex_index == graph->vertex_count - 1) {  // if 当前邻接节点的索引为"结点数 - 1"
        return -1;  // 返回-1
    }

    for (int i = adj_vertex_index + 1; i < graph->vertex_count; i++) {  // for loop 遍历所有结点
        // if 遍历结点索引不等于结点索引 and 结点与遍历结点之间存在边
        if (i != vertex_index && graph->adj_matrix[vertex_index][i].weight_type != NO_EDGE) {
            return i;   // 返回遍历结点索引
        }
    }

    return -1;  // 返回-1
}


/*!
 * @brief **获取结点的第一条边**
 * @param graph 图(结点)
 * @param vertex_index 结点索引
 * @note
 * 获取结点的第一条边
 * ---------------
 * ---------------
 *
 * ---------------
 * **for loop** 遍历图结点 : \n
 * &emsp; **if** 边(vertex_index --> i)存在 : \n
 * &emsp;&emsp; 返回 边(vertex_index --> i) \n
 * 返回 NULL
 */
edge_t* FirstEdge(matrix_graph_t* graph, int vertex_index) {
    for (int i = 0; i < graph->vertex_count; i++) {     // for loop 遍历图结点
        if (graph->adj_matrix[vertex_index][i].weight_type != NO_EDGE) {    // if 边(vertex_index --> i)存在
            return &graph->adj_matrix[vertex_index][i];     // 返回 边(vertex_index --> i)
        }
    }

    return NULL;    // 返回 NULL
}


/*!
 * @brief **获取结点的某条邻接边之外的下一条邻接边**
 * @param graph 图(指针)
 * @param vertex_index 结点索引
 * @param edge 边(指针)
 * @return 下一条边(指针)
 * @note
 * 获取结点的某条邻接边之外的下一条邻接边
 * ---------------------------------
 * ---------------------------------
 *
 * ---------------------------------
 * **for loop** 从边终点索引的下一索引结点开始, 遍历图结点 : \n
 * &emsp; **if** 边(vertex_index --> i)存在 : \n
 * &emsp;&emsp; 返回 边(vertex_index --> i) \n
 * 返回 NULL
 */
edge_t* NextEdge(matrix_graph_t* graph, int vertex_index, edge_t* edge) {

    // for loop 从边终点索引的下一索引结点开始, 遍历图结点
    for (int i = edge->ending_vertex_index + 1; i < graph->vertex_count; i++) {
        if (graph->adj_matrix[vertex_index][i].weight_type != NO_EDGE) {    // if 边(vertex_index --> i)存在
            return &graph->adj_matrix[vertex_index][i]; // 返回 边(vertex_index --> i)
        }
    }

    return NULL;    // 返回 NULL
}


/*!
 * @brief **构造图(使用边数组和结点索引数组)**
 * @param graph 图(指针)
 * @param edges 边数组
 * @param edge_count 边数量
 * @param vertex_indexes 结点索引数组
 * @param vertex_count 结点数量
 * @param graph_kind 图类型
 * @return 执行结果
 * @note
 * 构造图(使用边数组和结点索引数组)
 * ----------------------------
 * ----------------------------
 *
 * ----------------------------
 *
 * vertex_index_arr为图结点索引数组, 如: 结点0, 结点1, 结点2 ... \n
 * 实际上应该允许传各种结点类型(vertex_type), 表示 "北京", "上海", "深圳" / "女神A", "女神B", "女神C" ... \n
 * 由于本代码重点在实现算法, 因此不做vertex_type的灵活性工作 \n
 *
 * 如有这方面兴趣, 请参考C++模板版本实现 https://gitee.com/cyberdash/data-structure-cpp 中的图代码
 *
 * ----------------------------
 *
 * - 边界条件检查 \n
 * &emsp; **if** 边和结点的数量大过限制 : \n
 * &emsp;&emsp; 返回OVERFLOW \n
 * - 设置图属性 \n
 * - 初始化图的领接矩阵并设置图的结点数组 \n
 * &emsp; **for loop** 遍历参数结点数组, 初始化图的邻接矩阵和图结点数组 : \n
 * &emsp;&emsp; 当前参数结点数组值, 赋给图结点数组 \n
 * &emsp;&emsp; **for loop** 遍历图结点数组 : \n
 * &emsp;&emsp;&emsp; 设置邻接矩阵元素adj_matrix[i][j]的starting_vertex_index和ending_vertex_index \n
 * &emsp;&emsp;&emsp; 主对角线元素设置权值类型, 权值设为0 \n
 * &emsp;&emsp;&emsp; 非主对角线元素, 权值类型设为NO_EDGE, 权值设为极大值 \n
 * - 使用参数边数组进一步设置图的领接矩阵和图的边数组 \n
 * &emsp; **for loop** 遍历参数边数组 : \n
 * &emsp;&emsp; 将 当前边(start --> end) 赋给邻接矩阵相应元素 \n
 * &emsp;&emsp; **if** 无向图/网 : \n
 * &emsp;&emsp;&emsp; 增加 邻接矩阵元素(end --> start) \n
 */
status_t CreateGraphByEdgesAndVertices(matrix_graph_t* graph,
                                       edge_t* edges,
                                       int edge_count,
                                       const int* vertex_indexes,
                                       int vertex_count,
                                       GRAPH_KIND graph_kind)
{

    // if 边和结点的数量大过限制
    if (edge_count > MAX_EDGE_CNT || vertex_count > MAX_VERTEX_CNT) {
        return OVERFLOW; // 返回OVERFLOW
    }

    // 设置图属性
    graph->kind = graph_kind;              // 图类型
    graph->vertex_count = vertex_count;    // 结点数量
    graph->edge_count = edge_count;        // 边数量
    graph->weight_type = edges->weight_type;  // 使用edge_arr第0项的weight_type, 赋给graph->weight_type

    // 初始化图的领接矩阵并设置图的结点数组

    // for loop 遍历参数结点数组, 初始化图的邻接矩阵和图结点数组
    for (int i = 0; i < vertex_count; ++i) {

        // 当前参数结点数组值, 赋给图结点数组
        graph->vertexes[i] = vertex_indexes[i];

        // for loop 遍历图结点数组
        for (int j = 0; j < vertex_count; j++) {
            // 设置邻接矩阵元素adj_matrix[i][j]的starting_vertex_index和ending_vertex_index
            graph->adj_matrix[i][j].starting_vertex_index = i;
            graph->adj_matrix[i][j].ending_vertex_index = j;

            // 主对角线元素设置权值类型, 权值设为0
            if (i == j ) {
                graph->adj_matrix[i][j].weight_type = graph->weight_type;
                if (graph->weight_type == DOUBLE) {
                    graph->adj_matrix[i][j].weight.double_value = 0;
                }
            } else { // 非主对角线元素, 权值类型设为NO_EDGE, 权值设为极大值
                graph->adj_matrix[i][j].weight_type = NO_EDGE;
                if (graph->weight_type == DOUBLE) {
                    graph->adj_matrix[i][j].weight.double_value = DBL_MAX;
                }
            }
        }
    }

    // 使用参数边数组进一步设置图的领接矩阵和图的边数组

    // for loop 遍历参数边数组
    for (int i = 0; i < edge_count; ++i) {

        graph->edges[i] = edges[i];

        int start = edges[i].starting_vertex_index;
        int end = edges[i].ending_vertex_index;

        // 将 当前边(start --> end) 赋给邻接矩阵相应元素
        graph->adj_matrix[start][end] = edges[i];

        // if 无向图/网
        if (graph->kind == UDN || graph->kind == UDG) {
            // 增加 边(end --> start)
            graph->adj_matrix[end][start].weight_type = graph->weight_type;
            graph->adj_matrix[end][start] = edges[i];
        }
    }

    return OK;
}


/*!
 * @brief **打印图邻接矩阵**
 * @param graph **图**(指针)
 * @return **执行结果**
 * @note
 * 打印图邻接矩阵
 * ------------
 * ------------
 *
 * ------------
 * **for loop** 遍历图结点(作为起点) : \n
 * &emsp; **for loop** 遍历图结点(作为终点) : \n
 * &emsp;&emsp; **if** 邻接矩阵元素adj_matrix[start][end] 没有边 : \n
 * &emsp;&emsp;&emsp; 边权值设为0 \n
 * &emsp;&emsp; **else** (邻接矩阵元素(起点 --> 终点) 有边) : \n
 * &emsp;&emsp;&emsp; 边权值为adj_matrix[start][end].weight.double_value \n
 * &emsp;&emsp; 打印权值 \n
 * &emsp; 换行 \n
 */
status_t PrintGraphMatrix(matrix_graph_t* graph) {
    for (int start = 0; start < graph->vertex_count; start++) { // for loop 遍历图结点(作为起点)
        for (int end = 0; end < graph->vertex_count; end++) {       // for loop 遍历图结点(作为终点)
            double weight = DBL_MAX;
            if (graph->adj_matrix[start][end].weight_type == NO_EDGE) { // if 邻接矩阵元素adj_matrix[start][end] 没有边
                weight = 0; // 边权值设为0
            } else { // else (邻接矩阵元素(起点 --> 终点) 有边)
                weight = graph->adj_matrix[start][end].weight.double_value; // 边权值为adj_matrix[start][end]的权值
            }

            printf("%lf ", weight); // 打印权值
        }
        printf("\n");
    }

    return OK;
}
