//
// Created by cyberdash@163.com on 2022/3/24.
//

#ifndef CYBER_DASH_TREE_BINARY_TREE_NODE_H
#define CYBER_DASH_TREE_BINARY_TREE_NODE_H


typedef struct binary_tree_node_t {
    BINARY_TREE_NODE_DATA  data;    //!< 数据项
    struct binary_tree_node_t*  left_child;   // 左孩子指针
    struct binary_tree_node_t*  right_child;   // 右孩子指针
} binary_tree_node_t, *binary_tree_t;


#endif //CYBER_DASH_TREE_BINARY_TREE_NODE_H
