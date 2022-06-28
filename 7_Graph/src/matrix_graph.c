//
// Created by cyberdash@163.com(抖音: cyberdash_yuan) on 2022/3/24.
//

#include <stdio.h>
#include <float.h>
#include "matrix_graph.h"


/*!
 * 获取结点vertex的索引
 * @param graph 图
 * @param vertex 结点
 * @param vertex_index 索引(int指针)
 * @return 是否成功
 * @note
 */
Status LocateVertex(matrix_graph_t graph, VERTEX_TYPE vertex, int* vertex_index) {
    for (int i = 0; i < graph.vertex_count; i++) {
        if (graph.vertex_array[i] == vertex) {
            *vertex_index = i;
            return OK;
        }
    }

    return ERROR;
}


/*!
 * 获取某结点在图G中的第一个邻接节点的索引
 * @param graph 图(指针)
 * @param vertex_index 结点索引
 * @return 第一个邻接节点的索引
 * @note
 *  成功: 返回索引值
 *  失败: 返回 -1
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
 * 结点(索引)v在图G中的, 结点(索引)w之外第一个(索引)邻接节点
 * @param graph 图指针
 * @param vertex_index 节点索引v
 * @param first_adj_vertex_idx 节点索引v的一个邻接节点索引w
 * @return 下一个邻接结点的索引
 * @note
 *  成功: 返回索引值
 *  失败: 返回 -1
 */
int NextAdjVertexIdx(matrix_graph_t* graph, int vertex_index, int first_adj_vertex_idx) {
    if (first_adj_vertex_idx == graph->vertex_count - 1) {
        return -1;
    }

    for (int i = first_adj_vertex_idx + 1; i < graph->vertex_count; i++) {
        if (i != vertex_index && graph->adj_matrix[vertex_index][i].weight_type != NO_EDGE) {
            return i;
        }
    }

    return -1;
}


// 获取结点的第一条弧(边)
edge_t* FirstEdge(matrix_graph_t* graph, int vertex_idx) {
    for (int i = 0; i < graph->vertex_count; i++) {
        if (graph->weight_type != NO_EDGE) {
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

    for (int i = edge->ending_vertex_index + 1; i < graph->vertex_count; i++) {
        if (graph->weight_type == NO_EDGE) {
            return &graph->adj_matrix[vertex_idx][i];
        }
    }

    return NULL;
}


/*!
 * 构造图
 * @param graph 图(指针)
 * @param edge_array 边信息数组
 * @param edge_count 边数量
 * @param vertex_index_array 结点索引数组
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
Status CreateGraphByEdgesAndVertices(matrix_graph_t* graph,
                                     edge_t* edge_array,
                                     int edge_count,
                                     const int* vertex_index_array,
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
    graph->weight_type = edge_array->weight_type;  // 使用edge_arr第0项的weight_type, 赋给graph->weight_type

    for (int i = 0; i < graph->vertex_count; ++i) {

        // 结点信息数组各元素初始化
        graph->vertex_array[i] = vertex_index_array[i];

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
        int u = edge_array[i].starting_vertex_index;
        int v = edge_array[i].ending_vertex_index;

        graph->adj_matrix[u][v] = edge_array[i];


        // 无向图/网, 增加 边: v --> u
        if (graph->kind == UDN || graph->kind == UDG) {
            graph->adj_matrix[v][u] = edge_array[i];
            graph->adj_matrix[v][u].starting_vertex_index = v;
            graph->adj_matrix[v][u].ending_vertex_index = u;
        }

        // 图边信息数组赋值
        graph->edge_array[i] = edge_array[i];
    }

    return OK;
}


/*!
 * 打印图邻接矩阵
 * @param graph 图(指针)
 * @return 执行结果
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
