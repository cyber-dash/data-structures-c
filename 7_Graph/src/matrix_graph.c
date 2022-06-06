//
// Created by cyberdash@163.com(抖音: cyberdash_yuan) on 2022/3/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "matrix_graph.h"


/*
Status CreateGraph(matrix_graph_t *G) {
    scanf(&G->kind);
    switch (G->kind) {
        case DG:
            return CreateDG(G);
        case DN:
            return CreateDN(G);
        case UDG:
            return CreateUDG(G);
        case UDN:
            return CreateUDNByArcCellArr(G);
        default:
            return ERROR;
    }
}
 */


/*!
 * 获取结点u的索引
 * @param G 图
 * @param u 结点u
 * @param idx 索引(指针)
 * @return 是否成功
 * @note
 */
Status LocateVertex(matrix_graph_t G, VERTEX_TYPE u, int* idx) {
    for (int i = 0; i < G.vertex_count; i++) {
        if (G.vertices[i] == u) {
            *idx = i;
            return OK;
        }
    }

    return ERROR;
}

/*!
 * 结点(索引)v在图G中的第一个(索引)邻接节点
 * @param graph 图(指针)
 * @param vertex_idx 结点索引
 * @return 第一个邻接节点的索引
 * @note
 *  成功: 返回索引值
 *  失败: 返回 -1
 */
int FirstAdjVertex(matrix_graph_t* graph, int vertex_idx) {
    for (int i = 0; i < graph->vertex_count; i++) {
        if (graph->adj_matrix[vertex_idx][i].weight_type != graph->weight_type) {
            return i;
        }
    }

    return -1;
}


/*!
 * 结点(索引)v在图G中的, 结点(索引)w之外第一个(索引)邻接节点
 * @param G 图指针
 * @param v 节点索引v
 * @param w 节点索引v的一个邻接节点索引w
 * @return 下一个邻接结点的索引
 * @note
 *  成功: 返回索引值
 *  失败: 返回 -1
 */
int NextAdjVex(matrix_graph_t *G, int v, int w) {
    if (w == G->vertex_count - 1) {
        return -1;
    }

    for (int i = w + 1; i < G->vertex_count; i++) {
        if (G->adj_matrix[v][i].weight_type != G->weight_type) {
            return i;
        }
    }

    return -1;
}


// 获取结点的第一条弧(边)
edge_t* GetFirstArc(matrix_graph_t *G, int vertexIdx) {
    for (int i = 0; i < G->vertex_count; i++) {
        if (G->weight_type == DOUBLE && G->adj_matrix[vertexIdx][i].edge_info->value.double_value != DBL_MAX) {
            return &G->adj_matrix[vertexIdx][i];
        } else if (G->weight_type == INT && G->adj_matrix[vertexIdx][i].edge_info->value.int_value != INT_MAX) {
            return &G->adj_matrix[vertexIdx][i];
        }
    }

    return NULL;
}


/*!
 * 获取结点的基于某条弧(边)的下一条弧(边)
 * @param G 图(指针)
 * @param vertexIdx 结点索引
 * @param arc 弧(边)(指针)
 * @return 下一条弧(边)的指针
 */
edge_t* GetNextArc(matrix_graph_t *G, int vertexIdx, edge_t* arc) {
    int endingVertexIdx = arc->edge_info->ending_vertex_idx;

    for (int i = endingVertexIdx + 1; i < G->vertex_count; i++) {
        if (G->weight_type == DOUBLE && G->adj_matrix[vertexIdx][i].edge_info->value.double_value != DBL_MAX) {
            return &G->adj_matrix[vertexIdx][i];
        } else if (G->weight_type == INT && G->adj_matrix[vertexIdx][i].edge_info->value.int_value != INT_MAX) {
            return &G->adj_matrix[vertexIdx][i];
        }
    }

    return NULL;
}


// 使用弧信息数组构造图
Status CreateGraphByArcCellArr(matrix_graph_t *G, edge_t *arcCellArr, int vertexNum, int arcNum) {

    return OK;
}


/*!
 * 构造无向网
 * @param graph
 * @param edge_arr
 * @param edge_cnt
 * @param vertex_arr
 * @param vertex_cnt
 * @return 是否成功
 * @note
 * vertexArr为图结点数组, 本代码将VertexType设置为int, 表示 结点0, 结点1, 结点2...
 * 实际上VertexType也可以设置为char, 表示 结点a, 结点b, 结点c ...
 * 由于本代码重点在实现算法, 因此不做VertexType的灵活性工作
 *
 * 如有这方面兴趣, 请参考C++版本实现 https://gitee.com/cyberdash/data-structure-cpp
 */
Status CreateUDNByArcCellArr(matrix_graph_t* graph,
                             edge_t* edge_arr,
                             int edge_cnt,
                             VERTEX_TYPE* vertex_arr,
                             int vertex_cnt)
{

    graph->vertex_count = vertex_cnt;
    graph->edge_count = edge_cnt;

    graph->weight_type = edge_arr->weight_type;  // 读arcCellArr第0项的adj

    //! 对G->arcs进行初始化
    for (int i = 0; i < graph->vertex_count; ++i) {
        graph->vertices[i] = vertex_arr[i];
        for (int j = 0; j < graph->vertex_count; ++j) {

            graph->adj_matrix[i][j].weight_type = graph->weight_type;    //! 弧(边)权值类型

            graph->adj_matrix[i][j].edge_info = (edge_info_t*)malloc(sizeof(edge_info_t));
            /* error handler */
            graph->adj_matrix[i][j].edge_info->starting_vertex_idx = i; //! 弧(边)的起始结点索引
            graph->adj_matrix[i][j].edge_info->ending_vertex_idx = j;   //! 弧(边)的终点结点索引

            if (graph->weight_type == DOUBLE) {
                graph->adj_matrix[i][j].edge_info->value.double_value = DBL_MAX;   //! 如果是DOUBLE类型, 则将double_value设置成最大值
            } else if (graph->weight_type == INT) {
                graph->adj_matrix[i][j].edge_info->value.int_value = INT_MAX;      //! 如果是INT类型, 则将int_value设置成最大值
            }
        }
    }

    //! 使用arcCellArr填充G->arcs中对应的结点数据
    for (int k = 0; k < edge_cnt; ++k) {

        int i = edge_arr[k].edge_info->starting_vertex_idx;    //! 起始结点索引
        int j = edge_arr[k].edge_info->ending_vertex_idx;      //! 终点结点索引

        //! 弧(边): i --> j
        graph->adj_matrix[i][j].edge_info->starting_vertex_idx = edge_arr[k].edge_info->starting_vertex_idx;
        graph->adj_matrix[i][j].edge_info->ending_vertex_idx = edge_arr[k].edge_info->ending_vertex_idx;
        graph->adj_matrix[i][j].edge_info->value = edge_arr[k].edge_info->value;

        //! 弧(边): j --> i
        graph->adj_matrix[j][i].edge_info->starting_vertex_idx = edge_arr[k].edge_info->ending_vertex_idx;
        graph->adj_matrix[j][i].edge_info->ending_vertex_idx = edge_arr[k].edge_info->starting_vertex_idx;
        graph->adj_matrix[j][i].edge_info->value = edge_arr[k].edge_info->value;
    }

    return OK;
}


/*
// 使用弧信息数组构造无向网
Status CreateUDNByArcCellArr(matrix_graph_t *G, edge_t *arcCellArr, int vertexNum, int arcNum) {

}
 */


Status PrintGraphMatrix(matrix_graph_t* G, WEIGHT_TYPE valueType) {
    valueType = G->weight_type;

    for (int i = 0; i < G->vertex_count; i++) {
        for (int j = 0; j < G->vertex_count; j++) {

            if (valueType == DOUBLE) {
                double weight = G->adj_matrix[i][j].edge_info->value.double_value == DBL_MAX ? 0
                                                                                             : G->adj_matrix[i][j].edge_info->value.double_value;

                printf("%lf ", weight);
            } else if (valueType == INT) {
                int weight = G->adj_matrix[i][j].edge_info->value.int_value == INT_MAX ? 0
                                                                                       : G->adj_matrix[i][j].edge_info->value.int_value;

                printf("%d ", weight);
            } else {
                int hasWeight = G->adj_matrix[i][j].edge_info->value.int_value;

                printf("%d ", hasWeight);
            }

        }
        printf("\n");
    }

    return OK;
}
