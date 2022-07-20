/*!
 * @file binary_tree_node.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 二叉树结点头文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_TREE_BINARY_TREE_NODE_H
#define CYBER_DASH_TREE_BINARY_TREE_NODE_H


/*! @brief <h1>二叉树结点</h1> */
typedef struct binary_tree_node binary_tree_node_t;

/*! @brief <h1>二叉树结点</h1> */
struct binary_tree_node {
    BINARY_TREE_NODE_DATA       data;    //!< 数据项
    binary_tree_node_t*    left_child;     //!< 左孩子指针
    binary_tree_node_t*    right_child;    //!< 右孩子指针
};

/*! @brief 二叉树 */
typedef binary_tree_node_t* binary_tree_t;


#endif //CYBER_DASH_TREE_BINARY_TREE_NODE_H
