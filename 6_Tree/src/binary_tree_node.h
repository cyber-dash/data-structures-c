/*!
 * @file binary_tree_node.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 二叉树结点头文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_TREE_BINARY_TREE_NODE_H
#define CYBER_DASH_TREE_BINARY_TREE_NODE_H


typedef struct binary_tree_node_t {
    BINARY_TREE_NODE_DATA  data;    //!< 数据项
    struct binary_tree_node_t*  left_child;   // 左孩子指针
    struct binary_tree_node_t*  right_child;   // 右孩子指针
} binary_tree_node_t, *binary_tree_t;


#endif //CYBER_DASH_TREE_BINARY_TREE_NODE_H
