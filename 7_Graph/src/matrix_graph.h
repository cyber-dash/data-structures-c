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


// 构造图(使用边和结点)
status_t CreateGraphByEdgesAndVertices(matrix_graph_t* graph,
                                       edge_t* edges,
                                       int edge_cnt,
                                       const int* vertex_indexes,
                                       int vertex_cnt,
                                       GRAPH_KIND graph_kind);

// 获取某结点的第一个邻接节点的索引
int FirstAdjVertexIndex(matrix_graph_t* graph, int vertex_index);

// 获取索引vertex_index结点, adj_vertex_index之外的下一个邻接节点索引
int NextAdjVertexIndex(matrix_graph_t* graph, int vertex_index, int adj_vertex_index);

// status_t DestroyGraph(matrix_graph_t* graph);

// status_t LocateVertex(matrix_graph_t graph, VERTEX_TYPE vertex, int* vertex_index);

// 获取结点的第一条边
edge_t* FirstEdge(matrix_graph_t* graph, int vertex_index);

// 获取结点的某条邻接边之外的下一条邻接边
edge_t* NextEdge(matrix_graph_t* graph, int vertex_index, edge_t* edge);

// 打印图的邻接矩阵
status_t PrintGraphMatrix(matrix_graph_t* graph);
