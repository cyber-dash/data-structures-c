/*!
 * @file binary_tree.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 二叉树头文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_BINARY_TREE_H
#define CYBER_DASH_BINARY_TREE_H


#include "common.h"
#include "stddef.h"
#include "stack.h"
#include "binary_tree_node.h"


// 使用前序遍历字符串(NULL结点使用空格)创建二叉树(递归)
Status BinaryTreeCreateByPreOrderStringRecursive(binary_tree_node_t** node,
                                                 char* pre_order_str,
                                                 int* traverse_index,
                                                 size_t pre_order_str_len);

// 二叉树前序遍历(递归)
Status BinaryTreePreOrderTraverseRecursive(binary_tree_node_t* node, Status (*Visit)(BINARY_TREE_NODE_DATA data));

// 二叉树中序遍历
Status BinaryTreeInOrderTraverse(binary_tree_node_t* node, Status (*Visit)(BINARY_TREE_NODE_DATA data));

// 二叉树中序遍历2
Status BinaryTreeInOrderTraverse2(binary_tree_node_t* node, Status (*Visit)(BINARY_TREE_NODE_DATA data));

// 二叉树后序遍历(递归)
Status BinaryTreePostOrderTraverseRecursive(binary_tree_node_t* binary_tree, Status (*Visit)(BINARY_TREE_NODE_DATA data));

Status LevelOrderTraverse(binary_tree_node_t* binary_tree, Status (*Visit)(BINARY_TREE_NODE_DATA data));


#endif // CYBER_DASH_BINARY_TREE_H
