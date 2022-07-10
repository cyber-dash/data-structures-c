/*!
 * @file stack.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 栈头文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "type.h"
#include "binary_tree_node.h"


#ifndef CYBER_DASH_TREE_STACK_H
#define CYBER_DASH_TREE_STACK_H

#define STACK_INIT_CAPACITY 100           //!< 存储空间初始分配量
#define STACK_INCREMENT  10               //!< 存储空间分配增量
#define STACK_ELEM binary_tree_node_t*    //!< 栈元素类型(二叉树结点指针)

typedef struct {
    STACK_ELEM* elements;
    STACK_ELEM* top;
    int capacity;
} seq_stack_t;


Status SeqStackInit(seq_stack_t* seq_stack);
Status SeqStackDestroy(seq_stack_t* seq_stack);
Status SeqStackClear(seq_stack_t* seq_stack);
int SeqStackIsEmpty(seq_stack_t seq_stack);
int SeqStackLength(seq_stack_t seq_stack);
Status SeqStackGetTop(seq_stack_t seq_stack, STACK_ELEM* elem);
Status SeqStackPush(seq_stack_t* seq_stack, binary_tree_node_t* elem);
Status SeqStackPop(seq_stack_t* seq_stack, STACK_ELEM* elem);


#endif // CYBER_DASH_TREE_STACK_H
