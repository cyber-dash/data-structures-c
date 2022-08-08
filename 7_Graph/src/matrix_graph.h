/*!
 * @file matrix_graph.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 邻接矩阵图头文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "graph.h"


// 构造图
status_t CreateGraphByEdgesAndVertices(matrix_graph_t* graph,
                                       edge_t* edge_arr,
                                       int edge_cnt,
                                       const VERTEX_TYPE* vertex_indexes,
                                       int vertex_cnt,
                                       GRAPH_KIND graph_kind);

// 结点(索引)v在图G中的第一个(索引)邻接节点
int FirstAdjVertexIdx(matrix_graph_t* graph, int vertex_index);

// 结点(索引)v在图G中的, 结点(索引)w之外第一个(索引)邻接节点
int NextAdjVertexIndex(matrix_graph_t* graph, int vertex_index, int adj_vertex_index);

status_t DestroyGraph(matrix_graph_t* graph);

status_t LocateVertex(matrix_graph_t graph, VERTEX_TYPE vertex, int* vertex_index);

// 获取结点的第一条弧(边)
edge_t* FirstEdge(matrix_graph_t* graph, int vertex_index);

// 获取结点的基于某条弧(边)的下一条弧(边)
edge_t* NextEdge(matrix_graph_t* graph, int vertex_index, edge_t* edge);

// 打印图的邻接矩阵
status_t PrintGraphMatrix(matrix_graph_t* graph);
