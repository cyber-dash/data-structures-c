//
// Created by cyberdash@163.com(抖音: cyberdash_yuan) on 2022/3/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "matrix_graph.h"


/*!
 * 获取结点vertex的索引
 * @param graph 图
 * @param vertex 结点
 * @param vertex_idx 索引(int指针)
 * @return 是否成功
 * @note
 */
Status LocateVertex(matrix_graph_t graph, VERTEX_TYPE vertex, int* vertex_idx) {
    for (int cur_vertex_idx = 0; cur_vertex_idx < graph.vertex_count; cur_vertex_idx++) {
        if (graph.vertex_array[cur_vertex_idx] == vertex) {
            *vertex_idx = cur_vertex_idx;
            return OK;
        }
    }

    return ERROR;
}


/*!
 * 获取某结点在图G中的第一个邻接节点的索引
 * @param graph 图(指针)
 * @param vertex_idx 结点索引
 * @return 第一个邻接节点的索引
 * @note
 *  成功: 返回索引值
 *  失败: 返回 -1
 */
int FirstAdjVertexIdx(matrix_graph_t* graph, int vertex_idx) {
    for (int cur_vertex_idx = 0; cur_vertex_idx < graph->vertex_count; cur_vertex_idx++) {
        if (cur_vertex_idx != vertex_idx &&
            graph->adj_matrix[vertex_idx][cur_vertex_idx].weight_type != NO_EDGE)
        {
            return cur_vertex_idx;
        }
    }

    return -1;
}


/*!
 * 结点(索引)v在图G中的, 结点(索引)w之外第一个(索引)邻接节点
 * @param graph 图指针
 * @param vertex_idx 节点索引v
 * @param first_adj_vertex_idx 节点索引v的一个邻接节点索引w
 * @return 下一个邻接结点的索引
 * @note
 *  成功: 返回索引值
 *  失败: 返回 -1
 */
int NextAdjVertexIdx(matrix_graph_t* graph, int vertex_idx, int first_adj_vertex_idx) {
    if (first_adj_vertex_idx == graph->vertex_count - 1) {
        return -1;
    }

    for (int cur_vertex_idx = first_adj_vertex_idx + 1;
         cur_vertex_idx < graph->vertex_count;
         cur_vertex_idx++)
    {
        if (cur_vertex_idx != vertex_idx &&
            graph->adj_matrix[vertex_idx][cur_vertex_idx].weight_type != NO_EDGE)
        {
            return cur_vertex_idx;
        }
    }

    return -1;
}


// 获取结点的第一条弧(边)
edge_t* FirstEdge(matrix_graph_t* graph, int vertex_idx) {
    for (int i = 0; i < graph->vertex_count; i++) {
        if (graph->weight_type != NO_EDGE /*&& graph->adj_matrix[vertex_idx][i].weight.double_value != DBL_MAX*/) {
            return &graph->adj_matrix[vertex_idx][i];
        }
    }

    return NULL;
}


/*!
 * 获取结点的基于某条弧(边)的下一条弧(边)
 * @param graph 图(指针)
 * @param vertex_idx 结点索引
 * @param edge 弧(边)(指针)
 * @return 下一条弧(边)的指针
 */
edge_t* NextEdge(matrix_graph_t* graph, int vertex_idx, edge_t* edge) {

    for (int i = edge->ending_vertex_idx + 1; i < graph->vertex_count; i++) {
        if (graph->weight_type == NO_EDGE /*&& graph->adj_matrix[vertex_idx][i].weight.double_value != DBL_MAX */) {
            return &graph->adj_matrix[vertex_idx][i];
        }
    }

    return NULL;
}


/*!
 * 构造图
 * @param graph 图(指针)
 * @param edge_arr 边信息数组
 * @param edge_cnt 边数量
 * @param vertex_index_arr 结点索引数组
 * @param vertex_cnt 结点数量
 * @param graph_kind 图类型
 * @return 执行结果
 * @note
 * vertex_index_arr为图结点索引数组, 如: 结点0, 结点1, 结点2 ...
 * 实际上应该允许传各种结点类型(vertex_type), 表示 "北京", "上海", "深圳" / "女神A", "女神B", "女神C" ...
 * 由于本代码重点在实现算法, 因此不做vertex_type的灵活性工作
 *
 * 如有这方面兴趣, 请参考C++模板版本实现 https://gitee.com/cyberdash/data-structure-cpp 中的图代码
 */
Status CreateGraphByEdgesAndVertices(matrix_graph_t* graph,
                                     edge_t* edge_arr,
                                     int edge_cnt,
                                     const int* vertex_index_arr,
                                     int vertex_cnt,
                                     GRAPH_KIND graph_kind)
{
    graph->kind = graph_kind;           //!< 图类型
    graph->vertex_count = vertex_cnt;   //!< 结点数量
    graph->edge_count = edge_cnt;       //!< 边数量

    graph->weight_type = edge_arr->weight_type;  // 使用edge_arr第0项的weight_type, 赋给graph->weight_type

    for (int i = 0; i < graph->vertex_count; ++i) {

        // 结点信息数组
        graph->vertex_array[i] = vertex_index_arr[i];

        // 矩阵元素初始化NO_EDGE
        for (int j = 0; j < graph->vertex_count; ++j) {
            graph->adj_matrix[i][j].starting_vertex_idx = i; //! 弧(边)的起始结点索引
            graph->adj_matrix[i][j].ending_vertex_idx = j;   //! 弧(边)的终点结点索引

            if (i == j ) {
                graph->adj_matrix[i][j].weight_type = DOUBLE;    //! 弧(边)权值类型
                graph->adj_matrix[i][j].weight.double_value = 0;
            } else {
                graph->adj_matrix[i][j].weight_type = NO_EDGE;    //! 弧(边)权值类型
                // graph->adj_matrix[i][j].weight.double_value = DBL_MAX;
            }
        }
    }

    //! 使用edge_arr填充adj_matrix中对应的结点数据
    for (int i = 0; i < edge_cnt; ++i) {

        int u = edge_arr[i].starting_vertex_idx;
        int v = edge_arr[i].ending_vertex_idx;

        //! 边: u --> v
        graph->adj_matrix[u][v] = edge_arr[i];


        // 无向图/网增加如下操作
        if (graph->kind == UDN || graph->kind == UDG) {
            //! 边: v --> u
            graph->adj_matrix[v][u] = edge_arr[i];
            graph->adj_matrix[v][u].starting_vertex_idx = edge_arr[i].ending_vertex_idx;
            graph->adj_matrix[v][u].ending_vertex_idx = edge_arr[i].starting_vertex_idx;
        }

        // 图边信息数组赋值
        graph->edge_array[i] = edge_arr[i];
    }

    return OK;
}


/*
// 使用弧信息数组构造无向网
Status CreateGraphByEdgesAndVertices(matrix_graph_t *graph, edge_t *arcCellArr, int vertexNum, int arcNum) {

}
 */


Status PrintGraphMatrix(matrix_graph_t* graph) {
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
