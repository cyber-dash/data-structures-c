/*!
 * @file graph.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 图头文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */
#ifndef CYBER_DASH_COMMON_H
#define CYBER_DASH_COMMON_H


#include "common.h"


#define MAX_VERTEX_CNT  10  //!< 最大顶点数
#define MAX_EDGE_CNT    30  //!< 最大边数
#define VERTEX_TYPE	    int //!< 结点类型


/*! @brief 图类型 */
typedef enum {
    DG,    //!< 有向图
    DN,    //!< 有向网
    UDG,   //!< 无向图
    UDN    //!< 无向网
} GRAPH_KIND;

/*! @brief 权值类型 */
typedef enum {
    NO_EDGE,    //!< 没有边(弧)
    UNWEIGHTED, //!< 无权值
    // INT,
    DOUBLE,     //!< 双精度
} WEIGHT_TYPE;

/*! @brief 权值联合体 */
typedef union {
    int int_value;          //!< 整型类型值
    double double_value;    //!< 双精度类型值
} WEIGHT;

/*! @brief 路径 */
typedef struct path   path_t;

/*! @brief 边 */
typedef path_t        edge_t;

/*! @brief 路径结构体 */
struct path {
    int starting_vertex_index;    //!< 起点索引
    int ending_vertex_index;      //!< 终点索引
    WEIGHT_TYPE weight_type;      //!< 边权值类型
    WEIGHT weight;                //!< 边权值
};

/*! @brief 邻接矩阵 */
typedef edge_t adj_matrix_t[MAX_VERTEX_CNT][MAX_VERTEX_CNT];

/*! @brief 最小生成树数组 */
typedef edge_t MST_t[MAX_VERTEX_CNT];

/*! @brief 邻接矩阵图 */
typedef struct {
    int vertex_count;    //!< 图结点数
    int edge_count;      //!< 图弧(边)数

    GRAPH_KIND  kind;           //!< 图的种类标志
    WEIGHT_TYPE weight_type;    //!< 边权值类型

    VERTEX_TYPE vertex_array[MAX_VERTEX_CNT];    //!< 顶点集合(数组)
    edge_t edge_array[MAX_EDGE_CNT];             //!< 边集合(数组)
    adj_matrix_t adj_matrix;                     //!< 邻接矩阵

} matrix_graph_t;


#endif // CYBER_DASH_COMMON_H
