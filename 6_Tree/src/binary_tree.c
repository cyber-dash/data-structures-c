//
// Created by cyberdash@163.com on 2022/1/19.
//

#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"


/*!
 * @brief 算法6.4 建立二叉树
 * @param T 二叉树BiTree*类型指针
 * @return 创建结果
 * @note
 * 第131页, "一个按先序序列建立二叉树的二叉链表的过程"
 * 可以在终端输入"ABC  DE G  F   ", 书中的例子
 *         A
 *        /
 *       B
 *      / \
 *     C   D
 *        / \
 *       E   F
 *        \
 *         G
 */
Status CreateBiTree(binary_tree_t *T) {
  char ch;
  int res = scanf("%c", &ch);
  if (ch == ' ') *T = NULL;
  else {
    if (!(*T = (binary_tree_node_t*)malloc(sizeof(binary_tree_node_t)))) exit(OVERFLOW);
    (*T)->data = ch;                    // 生成根节点
    CreateBiTree(&(*T)->left_child);   // 构造左子树
    CreateBiTree(&(*T)->right_child);   // 构造右子树
  }

  return OK;
} // CreateBiTree


/*!
 * 使用前序遍历字符串(NULL结点使用空格)创建二叉树(递归)
 * @param node 二叉树结点(二级指针)
 * @param pre_order_str 字符串地址(前序遍历, 需要表示出叶子节点左右孩子为NULL)
 * @param traverse_index 字符位置指针(字符串数组的数组索引)
 * @param str_len 字符串长度
 * @return 是否成功
 * @note
 * 本函数在书中未出现, 是对CreateBiTree函数的改造
 * 避免在函数调用中手动输入, 改为传字符串参数, 更加灵活
 */
Status BinaryTreeCreateByPreOrderStringRecursive(binary_tree_node_t** node,
                                                 char* pre_order_str,
                                                 int* traverse_index,
                                                 int str_len)
{
    int index = *traverse_index;
    if (index >= str_len) {
        return OK;
    }

    char chr = pre_order_str[index];
    *traverse_index = index + 1;
    if (chr == ' ') {
        *node = NULL;
        return OK;
    }

    if (!(*node = (binary_tree_node_t*)malloc(sizeof(binary_tree_node_t)))) {
        return NON_ALLOCATED;
    }

    (*node)->data = chr; // 节点数据项赋值

    Status status = BinaryTreeCreateByPreOrderStringRecursive(&(*node)->left_child,
                                                              pre_order_str,
                                                              traverse_index,
                                                              str_len);
    if (status != OK) {
        return status;
    }

    status = BinaryTreeCreateByPreOrderStringRecursive(&(*node)->right_child,
                                                       pre_order_str,
                                                       traverse_index,
                                                       str_len);

    return status;
}


/*!
 * @brief 二叉树前序遍历(递归)
 * @param node 二叉树结点(指针)
 * @param Visit 结点元素访问函数
 * @return 执行结果
 */
Status BinaryTreePreOrderTraverseRecursive(binary_tree_node_t* node, Status (*Visit)(BINARY_TREE_NODE_DATA)) {

    // 结点如果为NULL, 返回OK, 正确情况下的递归终止
    if (node == NULL) {
        return OK;
    }

    // 访问结点, 如果访问失败, 返回失败原因, 错误情况下的递归终止
    Status status = Visit(node->data);
    if (status != OK) {
        return status;
    }

    // 对node左孩子进行递归
    status = BinaryTreePreOrderTraverseRecursive(node->left_child, Visit);
    if (status != OK) {
        return status;
    }

    // 对node右孩子进行递归
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

    seq_stack_t stack;
    SeqStackInit(&stack);

    SeqStackPush(&stack, node); // 根指针进栈

    while (!SeqStackIsEmpty(stack)) {

        binary_tree_node_t* cur;

        // 一直向左子树遍历
        while (SeqStackGetTop(stack, &cur) == OK && cur) {
            SeqStackPush(&stack, cur->left_child);
        }
        SeqStackPop(&stack, &cur); // 把栈顶的NULL结点pop出去, pop完后栈顶是树结点

        // 如果栈空, 跳出循环, 中序遍历结束
        if (SeqStackIsEmpty(stack)) {
            break;
        }

        // 栈顶出栈, 赋给cur
        SeqStackPop(&stack, &cur);

        // 访问结点cur
        if (Visit(cur->data) != OK) {
            return ERROR;
        }

        // cur的右孩子结点入栈
        SeqStackPush(&stack, cur->right_child);
    }

    return OK;
}




