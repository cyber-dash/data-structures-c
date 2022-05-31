//
// Created by cyberdash@163.com on 2022/1/19.
//

#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"


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
Status CreateBiTree(BiTree *T) {
  char ch;
  int res = scanf("%c", &ch);
  if (ch == ' ') *T = NULL;
  else {
    if (!(*T = (BiTNode*)malloc(sizeof(BiTNode)))) exit(OVERFLOW);
    (*T)->data = ch;                    // 生成根节点
    CreateBiTree(&(*T)->lchild);   // 构造左子树
    CreateBiTree(&(*T)->rchild);   // 构造右子树
  }

  return OK;
} // CreateBiTree


/*!
 * 使用(使用前序遍历)字符串创建二叉树
 * @param T 二叉树指针
 * @param string 字符串地址(前序遍历, 需要表示出叶子节点左右孩子为NULL)
 * @param posPtr 字符位置指针(字符串数组的数组索引)
 * @param strLen 字符串长度
 * @return 是否成功
 * @note
 * 本函数在书中未出现, 是对CreateBiTree函数的改造
 * 避免在函数调用中手动输入, 改为传字符串参数, 更加灵活
 */
Status CreateBiTreeByString(BiTree *T, char *string, int *posPtr, int strLen) {
    int pos = *posPtr;
    if (pos >= strLen) {
        return OK;
    }

    char ch = string[pos];
    *posPtr = pos + 1;
    if (ch == ' ')
        *T = NULL;
    else {
        if (!(*T = (BiTNode*)malloc(sizeof(BiTNode)))) {
            return OVERFLOW;
        }
        (*T)->data = ch; // 子树根节点赋值
        Status res = CreateBiTreeByString(&(*T)->lchild, string, posPtr, strLen);   // 构造左子树
        if (res != OK) {
            return ERROR;
        }

        res = CreateBiTreeByString(&(*T)->rchild, string, posPtr, strLen);   // 构造右子树
        if (res != OK) {
            return ERROR;
        }
    }

    return OK;
}


/*!
 * @brief 前序遍历
 * @param T 二叉树节点指针
 * @param Visit 节点元素访问函数
 * @return 是否遍历成功
 */
Status PreOrderTraverse(BiTree T, Status (*Visit)(TElemType e)) {
  if (T) {
    Visit(T->data);
    if (PreOrderTraverse(T->lchild, Visit)) {
      if (PreOrderTraverse(T->rchild, Visit)) {
        return OK;
      }
    }
    return ERROR;
  }else return OK;
} // PreOrderTraverse


/*!
 * 算法6.2 中序遍历
 * @param T 二叉树
 * @param Visit 结点元素访问函数
 * @return 是否成功
 * @note
 */
Status InOrderTraverse(BiTree T, Status (*Visit)(TElemType e)) {
    SqStack S;
    InitStack(&S);
    Push(&S, T); // 根指针进栈

    while (!StackEmpty(S)) {
        BiTNode *p;
        while (GetTop(S, &p) && p) Push(&S, p->lchild); // 向左走到尽头
        Pop(&S, &p);

        if (!StackEmpty(S)) {
            Pop(&S, &p);    if (!Visit(p->data)) return ERROR;
            Push(&S, p->rchild);
        }
    }

    return OK;
}


/*!
 * 算法6.3 中序遍历
 * @param Visit 结点元素访问函数
 * @return 是否成功
 * @note
 * 第131页
 */
Status InOrderTraverse2(BiTree T, Status (*Visit)(TElemType e)) {
    SqStack S;
    InitStack(&S);

    BiTNode *p = T;
    while (p || !StackEmpty(S)) {
        if (p) { Push(&S, p); p = p->lchild; }
        else {
            Pop(&S, &p);    if (!Visit(p->data)) return ERROR;
            p = p->rchild;
        }
    }

    return OK;
}


