//
// Created by cyberdash@163.com(抖音: cyberdash_yuan) on 2022/3/24.
//

#include "matrix_graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>


/*
Status CreateGraph(MGraph *G) {
	// 采用数组(邻接矩阵)表示法, 构造图G
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
Status LocateVex(MGraph G, VertexType u, int *idx) {
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vexs[i] == u) {
            *idx = i;
            return OK;
        }
    }

    return ERROR;
}

/*!
 * 结点(索引)v在图G中的第一个(索引)邻接节点
 * @param G 图指针
 * @param v 结点索引v
 * @return 第一个邻接节点的索引
 * @note
 *  成功: 返回索引值
 *  失败: 返回 -1
 */
int FirstAdjVex(MGraph *G, int v) {
    for (int i = 0; i < G->vexnum; i++) {
        if (G->arcs[v][i].adj != INFINITY) {
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
int NextAdjVex(MGraph *G, int v, int w) {
    if (w == G->vexnum - 1) {
        return -1;
    }

    for (int i = w + 1; i < G->vexnum; i++) {
        if (G->arcs[v][i].adj != INFINITY) {
            return i;
        }
    }

    return -1;
}


// 获取结点的第一条弧(边)
ArcCell* GetFirstArc(MGraph *G, int vertexIdx) {
    for (int i = 0; i < G->vexnum; i++) {
        if (G->weight_type == DOUBLE && G->arcs[vertexIdx][i].info->value.double_value != DBL_MAX) {
            return &G->arcs[vertexIdx][i];
        } else if (G->weight_type == INT && G->arcs[vertexIdx][i].info->value.int_value != INT_MAX) {
            return &G->arcs[vertexIdx][i];
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
ArcCell* GetNextArc(MGraph *G, int vertexIdx, ArcCell* arc) {
    int endingVertexIdx = arc->info->endingVertexIndex;

    for (int i = endingVertexIdx + 1; i < G->vexnum; i++) {
        if (G->weight_type == DOUBLE && G->arcs[vertexIdx][i].info->value.double_value != DBL_MAX) {
            return &G->arcs[vertexIdx][i];
        } else if (G->weight_type == INT && G->arcs[vertexIdx][i].info->value.int_value != INT_MAX) {
            return &G->arcs[vertexIdx][i];
        }
    }

    return NULL;
}


// 使用弧信息数组构造图
Status CreateGraphByArcCellArr(MGraph *G, ArcCell *arcCellArr, int vertexNum, int arcNum) {

    return OK;
}


/*!
 * 构造无向网
 * @param G
 * @param arcCellArr
 * @param arcCount
 * @param vertexArr
 * @param vertexCount
 * @return 是否成功
 * @note
 * vertexArr为图结点数组, 本代码将VertexType设置为int, 表示 结点0, 结点1, 结点2...
 * 实际上VertexType也可以设置为char, 表示 结点a, 结点b, 结点c ...
 * 由于本代码重点在实现算法, 因此不做VertexType的灵活性工作
 *
 * 如有这方面兴趣, 请参考C++版本实现 https://gitee.com/cyberdash/data-structure-cpp
 */
Status CreateUDNByArcCellArr(MGraph *G, ArcCell *arcCellArr, int arcCount, VertexType *vertexArr, int vertexCount) {

    G->vexnum = vertexCount;
    G->arcnum = arcCount;

    G->weight_type = arcCellArr->adj;  // 读arcCellArr第一项的adj

    //! 对G->arcs进行初始化
    for (int i = 0; i < G->vexnum; ++i) {
        G->vexs[i] = vertexArr[i];
        for (int j = 0; j < G->vexnum; ++j) {

            G->arcs[i][j].adj = G->weight_type;    //! 弧(边)权值类型

            G->arcs[i][j].info = (InfoType*)malloc(sizeof(InfoType));
            /* error handler */
            G->arcs[i][j].info->startingVertexIndex = i; //! 弧(边)的起始结点索引
            G->arcs[i][j].info->endingVertexIndex = j;   //! 弧(边)的终点结点索引

            if (G->weight_type == DOUBLE) {
                G->arcs[i][j].info->value.double_value = DBL_MAX;   //! 如果是DOUBLE类型, 则将double_value设置成最大值
            } else if (G->weight_type == INT) {
                G->arcs[i][j].info->value.int_value = INT_MAX;      //! 如果是INT类型, 则将int_value设置成最大值
            }
        }
    }

    //! 使用arcCellArr填充G->arcs中对应的结点数据
    for (int k = 0; k < arcCount; ++k) {

        int i = arcCellArr[k].info->startingVertexIndex;    //! 起始结点索引
        int j = arcCellArr[k].info->endingVertexIndex;      //! 终点结点索引

        //! 弧(边): i --> j
        G->arcs[i][j].info->startingVertexIndex = arcCellArr[k].info->startingVertexIndex;
        G->arcs[i][j].info->endingVertexIndex = arcCellArr[k].info->endingVertexIndex;
        G->arcs[i][j].info->value = arcCellArr[k].info->value;

        //! 弧(边): j --> i
        G->arcs[j][i].info->startingVertexIndex = arcCellArr[k].info->endingVertexIndex;
        G->arcs[j][i].info->endingVertexIndex = arcCellArr[k].info->startingVertexIndex;
        G->arcs[j][i].info->value = arcCellArr[k].info->value;
    }

    return OK;
}


/*
// 使用弧信息数组构造无向网
Status CreateUDNByArcCellArr(MGraph *G, ArcCell *arcCellArr, int vertexNum, int arcNum) {

}
 */


Status PrintGraphMatrix(MGraph* G, VRType valueType) {
    valueType = G->weight_type;

    for (int i = 0; i < G->vexnum; i++) {
        for (int j = 0; j < G->vexnum; j++) {

            if (valueType == DOUBLE) {
                double weight = G->arcs[i][j].info->value.double_value == DBL_MAX ? 0
                    : G->arcs[i][j].info->value.double_value;

                printf("%lf ", weight);
            } else if (valueType == INT) {
                int weight = G->arcs[i][j].info->value.int_value == INT_MAX ? 0
                    : G->arcs[i][j].info->value.int_value;

                printf("%d ", weight);
            } else {
                int hasWeight = G->arcs[i][j].info->value.int_value;

                printf("%d ", hasWeight);
            }

        }
        printf("\n");
    }

    return OK;
}
