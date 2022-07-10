/*!
 * @file binary_tree.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  二叉树
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */
#ifndef CYBER_DASH_BINARY_TREE_H
#define CYBER_DASH_BINARY_TREE_H

#include "type.h"
#include "stddef.h"
#include "stack.h"
#include "binary_tree_node.h"


Status BinaryTreeCreateByPreOrderStringRecursive(binary_tree_t *node,
                                                 char* pre_order_str,
                                                 int* traverse_index,
                                                 size_t pre_order_str_len);

Status BinaryTreePreOrderTraverseRecursive(binary_tree_t node, Status (*Visit)(BINARY_TREE_NODE_DATA e));

Status BinaryTreeInOrderTraverse(binary_tree_t node, Status (*Visit)(BINARY_TREE_NODE_DATA e));

Status BinaryTreeInOrderTraverse2(binary_tree_t node, Status (*Visit)(BINARY_TREE_NODE_DATA e));

Status PostOrderTraverse(binary_tree_t binary_tree, Status (*Visit)(BINARY_TREE_NODE_DATA e));

Status LevelOrderTraverse(binary_tree_t binary_tree, Status (*Visit)(BINARY_TREE_NODE_DATA e));


#endif // CYBER_DASH_BINARY_TREE_H
