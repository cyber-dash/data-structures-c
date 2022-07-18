//
// Created by cyberdash@163.com on 2022/1/19.
//

#ifndef CYBER_DASH_BINARY_TREE_H
#define CYBER_DASH_BINARY_TREE_H

#include "stack.h"
#include "type.h"
#include "binary_tree_node.h"


typedef BINARY_TREE_NODE_DATA SqBiTree[MAX_TREE_SIZE]; // 0号单元存储根节点


Status BinaryTreeCreateByPreOrderStringRecursive(binary_tree_t *node, char *pre_order_str, int *traverse_index, int pre_order_str_len);

Status BinaryTreePreOrderTraverseRecursive(binary_tree_t node, Status (*Visit)(BINARY_TREE_NODE_DATA e));

Status BinaryTreeInOrderTraverse(binary_tree_t node, Status (*Visit)(BINARY_TREE_NODE_DATA e));

Status BinaryTreeInOrderTraverse2(binary_tree_t node, Status (*Visit)(BINARY_TREE_NODE_DATA e));

Status BinaryTreePostOrderTraverseRecursive(binary_tree_t node, Status (*Visit)(BINARY_TREE_NODE_DATA e));

Status PostOrderTraverse(binary_tree_t T, Status (*Visit)(BINARY_TREE_NODE_DATA e));

Status LevelOrderTraverse(binary_tree_t T, Status (*Visit)(BINARY_TREE_NODE_DATA e));


#endif // CYBER_DASH_BINARY_TREE_H
