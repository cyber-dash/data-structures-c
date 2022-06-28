//
// Created by cyberdash@163.com on 2021/12/30.
//


#include "tree.h"
#include "BinaryTreeNode.h"


#ifndef CYBER_DASH_STACK_H
#define CYBER_DASH_STACK_H

#define STACK_INIT_SIZE 100 // 存储空间初始分配量
#define STACKINCREMENT  10  // 存储空间分配增量


#define SElemType binary_tree_node_t*  // 栈元素类型(二叉树结点指针)

typedef struct {
    SElemType* elements;  // 在栈构造之前和销毁之后, base的值为null
    SElemType* top;   // 栈顶指针
    int size;      // 当前已分配的存储空间, 以元素为单位
} seq_stack_t;

//-----基本操作的函数原型说明-----
Status StackInit(seq_stack_t *S); // 构造一个空栈S
Status DestroyStack(seq_stack_t *S); // 销毁栈S, S不再存在
Status ClearStack(seq_stack_t *S); // 把S置为空栈
Status StackEmpty(seq_stack_t S); // 若栈S为空栈, 则返回TRUE, 否则返回FALSE
int StackLength(seq_stack_t S); // 返回S的元素个数, 即栈的长度
Status StackGetTop(seq_stack_t S, SElemType *e); //
Status StackPush(seq_stack_t *S, binary_tree_node_t *e);
Status Pop(seq_stack_t *S, SElemType *e);


#endif // CYBER_DASH_STACK_H
