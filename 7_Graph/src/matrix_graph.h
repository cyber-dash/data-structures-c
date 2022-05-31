//
// Created by cyberdash@163.com(抖音: cyberdash_yuan) on 2022/3/24.
//

#include "graph.h"


// Status CreateGraph(MGraph *G, VertexType *V, ArcCell *VR);
Status CreateGraph(MGraph *G);

// 使用弧信息数组构造图
Status CreateGraphByArcCellArr(MGraph *G, ArcCell *arcCellArr, int vertexNum, int arcNum);

// 构造有向图
Status CreateDG(MGraph *G);

// 构造有向网
Status CreateDN(MGraph *G);

// 构造无向图
Status CreateUDG(MGraph *G);

// 结点(索引)v在图G中的第一个(索引)邻接节点
int FirstAdjVex(MGraph *G, int v);

// 结点(索引)v在图G中的, 结点(索引)w之外第一个(索引)邻接节点
int NextAdjVex(MGraph *G, int v, int w);

// 构造无向网
Status CreateUDNByArcCellArr(MGraph *G, ArcCell *arcCellArr, int arcCount, VertexType *vertexArr, int vertexCount);

Status DestroyGraph(MGraph *G);

Status LocateVex(MGraph G, VertexType u, int *idx);

// 获取结点的第一条弧(边)
ArcCell* GetFirstArc(MGraph *G, int vertexIdx);

// 获取结点的基于某条弧(边)的下一条弧(边)
ArcCell* GetNextArc(MGraph *G, int vertexIdx, ArcCell* arc);

// 打印图的邻接矩阵
Status PrintGraphMatrix(MGraph* G, VRType valueType);

// Status PutVex(MGraph *G, VertexType v, );