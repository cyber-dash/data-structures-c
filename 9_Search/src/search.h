//
// Created by cyberdash@163.com on 2022/5/12.
//

#ifndef CYBER_DASH_SEARCH_H
#define CYBER_DASH_SEARCH_H


#define KeyType     int
#define ValueType   double

// --- 对数值型关键字
#define EQ(a, b) ((a) == (b))
#define LT(a, b) ((a) < (b))
#define LQ(a, b) ((a) <= (b))


typedef enum Status { STATUS_OK, STATUS_ERROR, STATUS_OVERFLOW } Status;

typedef struct {
    KeyType     key;
    ValueType   value;
} SElemType;

typedef struct {
    KeyType     key;
    ValueType   value;
} ElemType;

typedef struct BiTNode {
    ElemType    data;
    struct BiTNode* lchild; // 左孩子指针
    struct BiTNode* rchild; // 右孩子指针
} BiTNode, *BiTree;


#endif // CYBER_DASH_SEARCH_H
