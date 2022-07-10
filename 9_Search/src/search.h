/*!
 * @file search.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 查找
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */
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
