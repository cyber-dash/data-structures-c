//
// Created by cyberdash@163.com on 2022/3/24.
//

#ifndef CYBER_DASH_TREE_BINARY_TREE_NODE_H
#define CYBER_DASH_TREE_BINARY_TREE_NODE_H

typedef struct BiTNode {
    TElemType       data;
    struct BiTNode  *lchild, *rchild;   // 左右孩子指针
}BiTNode, *BiTree;


#endif //CYBER_DASH_TREE_BINARY_TREE_NODE_H
