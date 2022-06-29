//
// Created by cyberdash@163.com on 2022/1/19.
//

#ifndef CYBER_DASH_BINARY_TREE_H
#define CYBER_DASH_BINARY_TREE_H

#include "stack.h"
#include "type.h"
#include "BinaryTreeNode.h"


typedef TREE_NODE_DATA SqBiTree[MAX_TREE_SIZE]; // 0号单元存储根节点


Status CreateBiTree(binary_tree_t *T);

Status CreateBiTreeByString(binary_tree_t *T, char *string, int *pos, int strLen);

Status PreOrderTraverse(binary_tree_t T, Status (*Visit)(TREE_NODE_DATA e));

Status InOrderTraverse(binary_tree_t node, Status (*Visit)(TREE_NODE_DATA e));

Status InOrderTraverse2(binary_tree_t node, Status (*Visit)(TREE_NODE_DATA e));

Status PostOrderTraverse(binary_tree_t T, Status (*Visit)(TREE_NODE_DATA e));

Status LevelOrderTraverse(binary_tree_t T, Status (*Visit)(TREE_NODE_DATA e));


#endif // CYBER_DASH_BINARY_TREE_H
