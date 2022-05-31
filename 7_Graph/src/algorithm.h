//
// Created by cyberdash@163.com on 2022/4/19.
//

#ifndef CYBER_DASH_GRAPH_ALGORITHM_H
#define CYBER_DASH_GRAPH_ALGORITHM_H


#include "matrix_graph.h"
#include <stdio.h>


// 结点访问函数
Status Visit(MGraph *graph, int vertex);

// DFS遍历
void DFSTraverse(MGraph G, Status (*Visit)(int v));

// DFS遍历(结点(索引)v为起始点)
void DFS(MGraph G, int v, int *visited);

// BFS遍历
void BFSTraverse(MGraph G, Status (*Visit)(MGraph *G, int v));

// BFS遍历(结点(索引)v为起始点)
void BFS(MGraph G, int v, int *visited);

// Prim最小生成树
void Prim(MGraph* graph, VRType v0, MinSpanNode* min_span_tree);

// 克努斯卡尔(Kruskal)最小生成树
void Kruskal(MGraph* graph, MinSpanNode* min_span_tree);

// 打印最小生成树
void PrintMinSpanTree(MinSpanNodeArr minSpanTree, int size);

// 迪杰斯特拉(Dijkstra)最短路径
void ShortestPath_Dijkstra(MGraph* graph, int v0, int (*predecessor)[MAX_VERTEX_CNT], ArcCell* distance);

// 贝尔曼福特(Bellman-Ford)最短路径
int ShortestPath_BellmanFord(MGraph* graph, int v0, int (*predecessor)[MAX_VERTEX_CNT], ArcCell* distance);

// 弗洛伊德(Floyd)最短路径
void Floyd(MGraph* graph, int (*predecessor)[MAX_VERTEX_CNT], ArcCell (*distance)[MAX_VERTEX_CNT]);

// 打印单源最短路径
void PrintSingleSourceShortestPath(MGraph *graph, int v0, int (*predecessor)[MAX_VERTEX_CNT], ArcCell* distance);

// 打印单源最短路径(递归)
void PrintSingleSourceShortestPathRecursive(MGraph *graph, int i, int j, int (*predecessor)[MAX_VERTEX_CNT]);


void PrintMultiSourceShortestPath(MGraph *graph,
                                  ArcCell (*distance)[MAX_VERTEX_CNT],
                                  int (*predecessor)[MAX_VERTEX_CNT]);


#endif // CYBER_DASH_GRAPH_ALGORITHM_H
