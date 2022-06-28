//
// Created by cyberdash@163.com on 2022/3/24.
//

#ifndef CYBER_DASH_TREE_BINARY_TREE_NODE_H
#define CYBER_DASH_TREE_BINARY_TREE_NODE_H

typedef struct binary_tree_node_t {
    TElemType       data;
    struct binary_tree_node_t  *lchild, *rchild;   // 左右孩子指针
}binary_tree_node_t, *binary_tree_t;


#endif //CYBER_DASH_TREE_BINARY_TREE_NODE_H
