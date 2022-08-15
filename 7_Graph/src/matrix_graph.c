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
 * <h1>获取某图结点的第一个邻接节点的索引</h1>
 * @param graph **图**(指针)
 * @param vertex_index 结点索引
 * @return 第一个邻接节点的索引
 * @note
 */
int FirstAdjVertexIdx(matrix_graph_t* graph, int vertex_index) {
    for (int i = 0; i < graph->vertex_count; i++) {
        if (i != vertex_index && graph->adj_matrix[vertex_index][i].weight_type != NO_EDGE) {
            return i;
        }
    }

    return -1;
}


/*!
 * <h1>索引vertex_index结点, adj_vertex_index之外的下一个邻接节点索引</h1>
 * @param graph **图**(指针)
 * @param vertex_index **结点索引**
 * @param adj_vertex_index **一个邻接节点索引**
 * @return **下一个邻接结点的索引**
 * @note
 */
int NextAdjVertexIndex(matrix_graph_t* graph, int vertex_index, int adj_vertex_index) {
    /// 如果存在下一邻接节点, 返回其索引, 否则返回-1\n
    /// &emsp; **if** 当前邻接节点的索引为"结点数 - 1" : \n
    /// &emsp;&emsp; 返回-1\n
    if (adj_vertex_index == graph->vertex_count - 1) {
        return -1;
    }

    /// **for loop** 遍历所有结点 :\n
    for (int i = adj_vertex_index + 1; i < graph->vertex_count; i++) {
        /// &emsp; **if** 遍历结点索引不等于结点索引, 并且 结点与遍历结点之间存在边 : \n
        if (i != vertex_index && graph->adj_matrix[vertex_index][i].weight_type != NO_EDGE) {
            /// &emsp;&emsp; 返回遍历结点索引\n
            return i;
        }
    }

    /// 返回-1
    return -1;
}


/*!
 * @brief <h1>获取结点的第一条边</h1>
 * @param graph **图**(结点)
 * @param vertex_index **结点索引**
 * @note
 */
edge_t* FirstEdge(matrix_graph_t* graph, int vertex_index) {
    /// **for loop** 遍历图结点 : \n
    for (int i = 0; i < graph->vertex_count; i++) {
        /// &emsp; **if** 边(vertex_index --> i)存在 : \n
        if (graph->adj_matrix[vertex_index][i].weight_type != NO_EDGE)
        {
            /// &emsp;&emsp; 返回 边(vertex_index --> i) \n
            return &graph->adj_matrix[vertex_index][i];
        }
    }

    /// 返回 NULL
    return NULL;
}


/*!
 * <h1>获取结点的基于某条边的下一条边</h1>
 * @param graph **图**(指针)
 * @param vertex_index **结点索引**
 * @param edge **边**(指针)
 * @return **下一条边**(指针)
 * @note
 */
edge_t* NextEdge(matrix_graph_t* graph, int vertex_index, edge_t* edge) {

    /// **for loop** 从边终点索引的下一索引结点开始, 遍历图结点 : \n
    for (int i = edge->ending_vertex_index + 1; i < graph->vertex_count; i++) {
        /// &emsp; **if** 边(vertex_index --> i)存在 : \n
        if (graph->adj_matrix[vertex_index][i].weight_type != NO_EDGE) {
            /// &emsp;&emsp; 返回 边(vertex_index --> i) \n
            return &graph->adj_matrix[vertex_index][i];
        }
    }

    /// 返回 NULL
    return NULL;
}


/*!
 * 构造图
 * @param graph 图(指针)
 * @param edges 边信息数组
 * @param edge_count 边数量
 * @param vertex_indexes 结点索引数组
 * @param vertex_count 结点数量
 * @param graph_kind 图类型
 * @return 执行结果
 * @note
 * vertex_index_arr为图结点索引数组, 如: 结点0, 结点1, 结点2 ...
 * 实际上应该允许传各种结点类型(vertex_type), 表示 "北京", "上海", "深圳" / "女神A", "女神B", "女神C" ...
 * 由于本代码重点在实现算法, 因此不做vertex_type的灵活性工作
 *
 * 如有这方面兴趣, 请参考C++模板版本实现 https://gitee.com/cyberdash/data-structure-cpp 中的图代码
 */
status_t CreateGraphByEdgesAndVertices(matrix_graph_t* graph,
                                       edge_t* edges,
                                       int edge_count,
                                       const int* vertex_indexes,
                                       int vertex_count,
                                       GRAPH_KIND graph_kind)
{
    // 结点数或边数超过限制
    if (edge_count > MAX_EDGE_CNT || vertex_count > MAX_VERTEX_CNT) {
        return ERROR;
    }

    graph->kind = graph_kind;              //!< 图类型
    graph->vertex_count = vertex_count;    //!< 结点数量
    graph->edge_count = edge_count;        //!< 边数量
    graph->weight_type = edges->weight_type;  // 使用edge_arr第0项的weight_type, 赋给graph->weight_type

    for (int i = 0; i < graph->vertex_count; ++i) {

        // 结点信息数组各元素初始化
        graph->vertexes[i] = vertex_indexes[i];

        // 邻接矩阵每个元素初始化
        //     主对角线元素, weight_type设为DOUBLE, weight.double_value设为0
        //     非主对角线元素, weight_type设为NO_EDGE
        for (int j = 0; j < graph->vertex_count; ++j) {
            graph->adj_matrix[i][j].starting_vertex_index = i; //! 边的起点索引
            graph->adj_matrix[i][j].ending_vertex_index = j;   //! 边的终点索引

            if (i == j ) {
                graph->adj_matrix[i][j].weight_type = DOUBLE;       //! 弧(边)权值类型 todo: 可以放到参数, 有兴趣自己实现:-)
                graph->adj_matrix[i][j].weight.double_value = 0;
            } else {
                graph->adj_matrix[i][j].weight_type = NO_EDGE;      //! 弧(边)权值类型
            }
        }
    }

    //! 使用edge_array填充adj_matrix中对应的结点数据
    for (int i = 0; i < edge_count; ++i) {

        //! 边: u --> v
        int u = edges[i].starting_vertex_index;
        int v = edges[i].ending_vertex_index;

        graph->adj_matrix[u][v] = edges[i];


        // 无向图/网, 增加 边: v --> u
        if (graph->kind == UDN || graph->kind == UDG) {
            graph->adj_matrix[v][u] = edges[i];
            graph->adj_matrix[v][u].starting_vertex_index = v;
            graph->adj_matrix[v][u].ending_vertex_index = u;
        }

        // 图边信息数组赋值
        graph->edges[i] = edges[i];
    }

    return OK;
}


/*!
 * 打印图邻接矩阵
 * @param graph 图(指针)
 * @return 执行结果
 */
status_t PrintGraphMatrix(matrix_graph_t* graph) {
    for (int i = 0; i < graph->vertex_count; i++) {
        for (int j = 0; j < graph->vertex_count; j++) {
            double weight = DBL_MAX;
            if (graph->adj_matrix[i][j].weight_type == NO_EDGE) {
                weight = 0;
            } else {
                weight = graph->adj_matrix[i][j].weight.double_value;
            }

            printf("%lf ", weight);
        }
        printf("\n");
    }

    return OK;
}
