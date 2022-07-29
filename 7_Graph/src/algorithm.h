/*!
 * @file algorithm.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 搜索算法
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_GRAPH_ALGORITHM_H
#define CYBER_DASH_GRAPH_ALGORITHM_H


#include "matrix_graph.h"
#include <stdio.h>


#define NOT_VISITED     0
#define VISITED         1


// 结点访问函数
status_t Visit(matrix_graph_t* graph, int vertex);

// DFS遍历
status_t DFSTraverse(matrix_graph_t graph, status_t (*Visit)(matrix_graph_t* graph, int vertex_index));

// DFS遍历(索引starting_vertex_index结点为起始点)
void DFSRecursive(matrix_graph_t graph,
                  int vertex_index,
                  int* visited_vertex_index_array,
                  status_t (*Visit)(matrix_graph_t* graph, int vertex_index));

// BFS遍历
void BFSTraverse(matrix_graph_t graph, status_t (*Visit)(matrix_graph_t *G, int v));

// BFS遍历(结点(索引)v为起始点)
void BFS(matrix_graph_t G, int v, int *visited);

// Prim最小生成树
void Prim(matrix_graph_t* graph, edge_t* min_span_tree);

// 克努斯卡尔(Kruskal)最小生成树
void Kruskal(matrix_graph_t* graph, edge_t* min_span_tree);

// 打印最小生成树
void PrintMinSpanTree(MST_t min_span_tree, int size);

// 迪杰斯特拉(Dijkstra)最短路径
void Dijkstra(matrix_graph_t* graph, int v0, int (*predecessor)[MAX_VERTEX_CNT], edge_t* distance);

// 贝尔曼福特(Bellman-Ford)最短路径
int BellmanFord(matrix_graph_t* graph, int starting_vertex_index, int (*predecessor)[MAX_VERTEX_CNT], edge_t* distance);

// 弗洛伊德(Floyd)最短路径
void Floyd(matrix_graph_t* graph, int (*predecessor)[MAX_VERTEX_CNT], edge_t (*distance)[MAX_VERTEX_CNT]);

// 打印单源最短路径
void PrintSingleSourceShortestPath(matrix_graph_t *graph, int starting_vertex_index, int (*predecessor)[MAX_VERTEX_CNT], edge_t* distance);

// 打印单源最短路径(递归)
void PrintSingleSourceShortestPathRecursive(matrix_graph_t *graph, int i, int j, int (*predecessor)[MAX_VERTEX_CNT]);


void PrintMultiSourceShortestPath(matrix_graph_t *graph,
                                  edge_t (*distance)[MAX_VERTEX_CNT],
                                  int (*predecessor)[MAX_VERTEX_CNT]);


#endif // CYBER_DASH_GRAPH_ALGORITHM_H
