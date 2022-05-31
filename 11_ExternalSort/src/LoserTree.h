//
// Created by cyberdash@163.com on 2022/4/6.
//

#ifndef CYBER_DASH_LOSER_TREE_H
#define CYBER_DASH_LOSER_TREE_H


#define k 5
typedef int KeyType;        // 定义关键字类型为整数类型

typedef int LoserTree[k];
typedef struct {
    KeyType  key;
}LeafNode, LeafArr[k + 1];   // 外结点, 只存放待归并记录的关键字

void K_Merge(LoserTree loserTree, LeafArr b, int* array[], int limitLen);


#endif // CYBER_DASH_LOSER_TREE_H
