//
// Created by cyberdash@163.com on 2021/12/30.
//


#include "type.h"
#include "binary_tree_node.h"


#ifndef CYBER_DASH_STACK_H
#define CYBER_DASH_STACK_H

#define STACK_INIT_CAPACITY 100 // 存储空间初始分配量
#define STACKINCREMENT  10  // 存储空间分配增量


#define STACK_ELEM binary_tree_node_t*  // 栈元素类型(二叉树结点指针)

typedef struct {
    STACK_ELEM* elements;
    STACK_ELEM* top;
    int capacity;
} seq_stack_t;

//-----基本操作的函数原型说明-----
Status SeqStackInit(seq_stack_t *seq_stack); // 构造一个空栈S
Status SeqStackDestroy(seq_stack_t *seq_stack); // 销毁栈S, S不再存在
Status ClearStack(seq_stack_t *seq_stack); // 把S置为空栈
int SeqStackIsEmpty(seq_stack_t seq_stack); // 若栈S为空栈, 则返回TRUE, 否则返回FALSE
int SeqStackLength(seq_stack_t seq_stack); // 返回S的元素个数, 即栈的长度
Status SeqStackGetTop(seq_stack_t seq_stack, STACK_ELEM *elem); //
Status SeqStackPush(seq_stack_t *seq_stack, binary_tree_node_t *node);
Status SeqStackPop(seq_stack_t *seq_stack, STACK_ELEM *elem);


#endif // CYBER_DASH_STACK_H
