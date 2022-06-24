//
// Created by cyberdash@163.com on 2022/4/19.
//

#ifndef CYBER_DASH_COMMON_H
#define CYBER_DASH_COMMON_H


#define MAX_VERTEX_CNT  50  //!< 最大顶点个数
#define VERTEX_TYPE	    int //!< 结点类型

#define FALSE   0
#define TRUE    1


/*!
 * 函数返回值
 */
typedef enum {
    OK,
    ERROR,
    OVERFLOW,
    NON_ALLOCATED,
    NON_EXISTENT
} Status;


typedef enum {
    DG,    //!< 有向图
    DN,    //!< 有向网
    UDG,   //!< 无向图
    UDN    //!< 无向网
} GRAPH_KIND;


typedef enum {
    NO_EDGE,    //!< 没有边(弧)
    UNWEIGHTED, //!< 无权值
    // INT,
    DOUBLE,     //!< 双精度
} WEIGHT_TYPE;


typedef union {
    int     int_value;
    double  double_value;
} WEIGHT;


typedef struct edge_t {
    int starting_vertex_index;    //!< 起点索引
    int ending_vertex_index;      //!< 终点索引
    WEIGHT_TYPE weight_type;    //!< 边权值类型
    WEIGHT weight;              //!< 边权值
} edge_t, path_t, adj_matrix_t[MAX_VERTEX_CNT][MAX_VERTEX_CNT], MST_t[MAX_VERTEX_CNT * MAX_VERTEX_CNT];




/*!
 * 邻接矩阵图
 */
typedef struct {
    int			    vertex_count;                                  //!< 图结点数
    int             edge_count;                                    //!< 图弧(边)数

    GRAPH_KIND	    kind;					                       //!< 图的种类标志
    WEIGHT_TYPE     weight_type;                                   //!< 边权值类型

    VERTEX_TYPE     vertex_array[MAX_VERTEX_CNT];                  //!< 顶点集合(数组)
    edge_t          edge_array[MAX_VERTEX_CNT * MAX_VERTEX_CNT];   //!< 边集合(数组)
    adj_matrix_t	adj_matrix;                                    //!< 邻接矩阵

} matrix_graph_t;


#endif // CYBER_DASH_COMMON_H
