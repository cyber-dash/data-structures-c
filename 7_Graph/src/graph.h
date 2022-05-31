//
// Created by cyberdash@163.com on 2022/4/19.
//

#ifndef CYBER_DASH_COMMON_H
#define CYBER_DASH_COMMON_H


#define MAX_VERTEX_CNT	30						// 最大顶点个数
#define INFINITY		INT_MAX					// 最大值, todo: 去掉这个
#define VertexType	    int
#define FALSE           0
#define TRUE            1

typedef enum Status {
    OK,
    ERROR,
    OVERFLOW,
    NON_EXISTENT
} Status;

typedef enum {
    DG,
    DN,
    UDG,
    UDN
} GraphKind;	// {有向图, 有向网, 无向图, 无向网}

typedef enum {
    UNWEIGHTED,
    INT,
    DOUBLE,
} VRType;

typedef union {
    int     int_value;
    double  double_value;
} InfoTypeValue;

typedef struct {
    int startingVertexIndex;       // 起点结点索引
    int endingVertexIndex;         // 终点结点索引
    InfoTypeValue value;    // 权值
} InfoType;


typedef struct AceCell {
    VRType adj;     // VRType是顶点关系类型
    InfoType* info;	// 该弧相关信息的指针
}ArcCell, AdjMatrix[MAX_VERTEX_CNT][MAX_VERTEX_CNT];


typedef struct {
    VertexType	vexs[MAX_VERTEX_CNT];	//!< 顶点向量
    AdjMatrix	arcs;					//!< 邻接矩阵
    int			vexnum;                 //!< 图结点数
    int         arcnum;                 //!< 图弧(边)数
    GraphKind	kind;					//!< 图的种类标志
    VRType      weight_type;            //!< 权值类型
}MGraph;


/*!
 * 最小生成树结点/数组
 */
typedef struct {
    VertexType    starting_vertex_idx;   // 边的起始结点索引
    VertexType    ending_vertex_idx;     // 边的终点结点索引
    InfoTypeValue weight;                // 权重
    VRType        weight_type;           // 权重类型
} MinSpanNode, MinSpanNodeArr[MAX_VERTEX_CNT];


#endif // CYBER_DASH_COMMON_H
