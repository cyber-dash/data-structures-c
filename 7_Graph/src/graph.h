//
// Created by cyberdash@163.com on 2022/4/19.
//

#ifndef CYBER_DASH_COMMON_H
#define CYBER_DASH_COMMON_H


#define MAX_VERTEX_CNT	30						// 最大顶点个数
#define VERTEX_TYPE	    int
#define FALSE           0
#define TRUE            1

typedef enum {
    OK,
    ERROR,
    OVERFLOW,
    NON_ALLOCATED,
    NON_EXISTENT
} Status;

typedef enum {
    DG,
    DN,
    UDG,
    UDN
} GRAPH_KIND;	// {有向图, 有向网, 无向图, 无向网}

typedef enum {
    NO_EDGE,
    UNWEIGHTED,
    // INT,
    DOUBLE,
} WEIGHT_TYPE;

typedef union {
    int     int_value;
    double  double_value;
} EDGE_WEIGHT;

typedef struct edge_t {
    WEIGHT_TYPE weight_type;     // VRType是顶点关系类型
    int starting_vertex_idx;       // 起点结点索引
    int ending_vertex_idx;         // 终点结点索引
    EDGE_WEIGHT weight;    // 权值
} edge_t, adj_matrix_t[MAX_VERTEX_CNT][MAX_VERTEX_CNT];


typedef struct {
    adj_matrix_t	adj_matrix;                                //!< 邻接矩阵

    int			    vertex_count;                              //!< 图结点数
    VERTEX_TYPE     vertices[MAX_VERTEX_CNT];                  //!< 顶点集合(数组)

    int             edge_count;                                //!< 图弧(边)数
    edge_t          edges[MAX_VERTEX_CNT * MAX_VERTEX_CNT];    //!< 边集合(数组)

    GRAPH_KIND	    kind;					                   //!< 图的种类标志
    WEIGHT_TYPE     weight_type;                               //!< 权值类型
} matrix_graph_t;


/*!
 * 最小生成树结点/数组
 */
typedef struct {
    int starting_vertex_idx;   // 边的起始结点索引
    int ending_vertex_idx;     // 边的终点结点索引
    EDGE_WEIGHT weight;                // 权重
    WEIGHT_TYPE        weight_type;           // 权重类型
} MST_node_t, MST_t[MAX_VERTEX_CNT];


#endif // CYBER_DASH_COMMON_H
