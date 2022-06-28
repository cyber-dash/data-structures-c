//
// Created by cyberdash@163.com(抖音: cyberdash_yuan) on 2022/3/24.
//

#include "graph.h"


// 构造图
Status CreateGraphByEdgesAndVertices(matrix_graph_t* graph,
                                     edge_t* edge_arr,
                                     int edge_cnt,
                                     const VERTEX_TYPE* vertex_index_arr,
                                     int vertex_cnt, GRAPH_KIND graph_kind);

// 结点(索引)v在图G中的第一个(索引)邻接节点
int FirstAdjVertexIdx(matrix_graph_t *graph, int vertex_index);

// 结点(索引)v在图G中的, 结点(索引)w之外第一个(索引)邻接节点
int NextAdjVertexIdx(matrix_graph_t* graph, int vertex_index, int first_adj_vertex_idx);

Status DestroyGraph(matrix_graph_t* graph);

Status LocateVertex(matrix_graph_t graph, VERTEX_TYPE vertex, int* vertex_index);

// 获取结点的第一条弧(边)
edge_t* FirstEdge(matrix_graph_t* graph, int vertex_idx);

// 获取结点的基于某条弧(边)的下一条弧(边)
edge_t* NextEdge(matrix_graph_t* graph, int vertex_idx, edge_t* edge);

// 打印图的邻接矩阵
Status PrintGraphMatrix(matrix_graph_t* graph);
