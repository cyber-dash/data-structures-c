//
// Created by cyberdash@163.com on 2022/1/19.
//

#ifndef CYBER_DASH_BINARY_TREE_H
#define CYBER_DASH_BINARY_TREE_H

#include "stack.h"
#include "tree.h"
#include "BinaryTreeNode.h"


typedef TElemType SqBiTree[MAX_TREE_SIZE]; // 0号单元存储根节点


Status CreateBiTree(BiTree *T);

Status CreateBiTreeByString(BiTree *T, char *string, int *pos, int strLen);

Status PreOrderTraverse(BiTree T, Status (*Visit)(TElemType e));

Status InOrderTraverse(BiTree T, Status (*Visit)(TElemType e));

Status InOrderTraverse2(BiTree T, Status (*Visit)(TElemType e));

Status PostOrderTraverse(BiTree T, Status (*Visit)(TElemType e));

Status LevelOrderTraverse(BiTree T, Status (*Visit)(TElemType e));


#endif // CYBER_DASH_BINARY_TREE_H
