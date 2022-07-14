﻿/*!
 * @file binary_tree.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 二叉树源文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"


/*!
 * <h1>使用前序遍历字符串(NULL结点使用空格)创建二叉树(递归)</h1>
 * @param node **二叉树结点(二级指针)**
 * @param pre_order_str **前序遍历字符串首地址(NULL结点使用空格)**
 * @param traverse_index **遍历字符的索引**
 * @param pre_order_str_len **前序遍历字符串(NULL结点使用空格)长度**
 * @return 是否成功
 * @note
 * NULL结点使用空格表示
 */
Status BinaryTreeCreateByPreOrderStringRecursive(binary_tree_node_t** node,
                                                 char* pre_order_str,
                                                 int* traverse_index,
                                                 size_t pre_order_str_len)
{
    // 如果遍历字符的索引>=字符串长度, 越界(即之后的字符串不参与create), 终止递归
    if (*traverse_index >= (int)pre_order_str_len) {
        return OK;
    }

    char chr = pre_order_str[*traverse_index];  // 遍历索引的字符赋给chr
    *traverse_index = *traverse_index + 1;      // 遍历字符的索引指向的位置, 向后挪1位(指向下一字符)

    // 如果chr为空格, 则为NULL结点, 返回OK, 终止递归
    if (chr == ' ') {
        *node = NULL;
        return OK;
    }

    // 内存分配失败, 返回错误码NON_ALLOCATED, 终止递归
    if (!(*node = (binary_tree_node_t*)malloc(sizeof(binary_tree_node_t)))) {
        return NON_ALLOCATED;
    }

    (*node)->data = chr; // 节点数据项赋值

    // 对左孩子结点执行递归, 构造左孩子结点为根结点的子树
    Status status = BinaryTreeCreateByPreOrderStringRecursive(&(*node)->left_child,
                                                              pre_order_str,
                                                              traverse_index,
                                                              pre_order_str_len);
    if (status != OK) { // 如果错误, 返回错误码
        return status;
    }

    // 对右孩子结点执行递归, 构造左孩子结点为根结点的子树
    status = BinaryTreeCreateByPreOrderStringRecursive(&(*node)->right_child,
                                                       pre_order_str,
                                                       traverse_index,
                                                       pre_order_str_len);

    return status;
}


/*!
 * @brief <h1>二叉树前序遍历(递归)</h1>
 * @param node **二叉树结点(指针)**
 * @param Visit **结点元素访问函数**
 * @return **执行结果**
 */
Status BinaryTreePreOrderTraverseRecursive(binary_tree_node_t* node, Status (*Visit)(BINARY_TREE_NODE_DATA)) {

    /// ##1 NULL结点, 返回OK, 正确情况下的递归终止##
    if (node == NULL) {
        return OK;
    }

    /// ##2 访问结点, 如果访问失败, 返回错误码, 错误情况下的递归终止##
    Status status = Visit(node->data);
    if (status != OK) {
        return status;
    }

    /// ##3 递归##
    /// ###3.1 对node左孩子结点(为根结点的子树)进行递归
    status = BinaryTreePreOrderTraverseRecursive(node->left_child, Visit);
    if (status != OK) { // 如果遍历失败, 返回错误码
        return status;
    }

    /// ###3.2 对node右孩子结点(为根结点的子树)进行递归
    status = BinaryTreePreOrderTraverseRecursive(node->right_child, Visit);

    return status;
}


/*!
 * @brief 二叉树中序遍历
 * @param node 二叉树结点(指针)
 * @param Visit 结点元素访问函数
 * @return 执行结果
 */
Status BinaryTreeInOrderTraverse(binary_tree_node_t* node, Status (*Visit)(BINARY_TREE_NODE_DATA)) {

    seq_stack_t stack;
    SeqStackInit(&stack);

    binary_tree_node_t* cur = node;
    while (cur || !SeqStackIsEmpty(stack)) {
        if (cur) {
            SeqStackPush(&stack, cur);
            cur = cur->left_child;
        } else {
            SeqStackPop(&stack, &cur);
            if (Visit(cur->data) != OK) {
                return ERROR;
            }
            cur = cur->right_child;
        }
    }

    return OK;
}


/*!
 * 二叉树中序遍历2
 * @param node 二叉树结点(指针)
 * @param Visit 结点元素访问函数
 * @return 执行结果
 * @note
 */
Status BinaryTreeInOrderTraverse2(binary_tree_node_t* node, Status (*Visit)(BINARY_TREE_NODE_DATA)) {

    //!< 初始化栈
    seq_stack_t stack;
    SeqStackInit(&stack);

    SeqStackPush(&stack, node); //!< 根结点入栈

    while (!SeqStackIsEmpty(stack)) {

        binary_tree_node_t* cur;    //!< 遍历结点

        //!< 一直向左子树遍历, 过程中结点入栈
        while (SeqStackGetTop(stack, &cur) == OK && cur) {
            SeqStackPush(&stack, cur->left_child);
        }

        SeqStackPop(&stack, &cur); //!< 栈顶的NULL出栈, 使栈顶是树结点

        //!< 如果栈空, 跳出循环, 中序遍历结束
        if (SeqStackIsEmpty(stack)) {
            break;
        }

        //!< 栈顶出栈, 赋给遍历结点cur
        SeqStackPop(&stack, &cur);

        //!< 访问遍历结点结点cur
        if (Visit(cur->data) != OK) {
            return ERROR;
        }

        //!< 遍历节点cur的右孩子结点入栈
        SeqStackPush(&stack, cur->right_child);
    }

    return OK;
}


// 二叉树后序遍历(递归)
Status BinaryTreePostOrderTraverseRecursive(binary_tree_node_t* node, Status (*Visit)(BINARY_TREE_NODE_DATA data)) {

    /// ##1 NULL结点, 返回OK, 正确情况下的递归终止##
    if (node == NULL) {
        return OK;
    }

    /// ###3.1 对node左孩子结点(为根结点的子树)进行递归
    Status status = BinaryTreePostOrderTraverseRecursive(node->left_child, Visit);
    if (status != OK) { // 如果遍历失败, 返回错误码
        return status;
    }

    status = BinaryTreePostOrderTraverseRecursive(node->right_child, Visit);
    if (status != OK) { // 如果遍历失败, 返回错误码
        return status;
    }

    status = Visit(node->data);

    return status;
}

