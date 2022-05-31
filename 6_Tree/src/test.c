//
// Created by cyberdash@163.com on 2022/1/23.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "test.h"


Status VisitChar(TElemType e) { // 输出元素e的值
  printf("%c", e);                 // 使用时, 加上格式串
  return OK;
}


Status VisitBinaryTreeNode(BiTNode e) { // 输出元素e的值
  printf("%c", e.data);                 // 使用时, 加上格式串
  return OK;
}


void TestBinaryTreeCreateBiTree() {
  BiTree* testTree = (BiTree*)malloc(sizeof(BiTree));
  CreateBiTree(testTree);
}


void TestBinaryTreePreOrderTraverse() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                     Test Pre Traverse                     |\n");
    printf("|                      测试二叉树前序遍历                      |\n");
    printf("|                            A                              |\n");
    printf("|                           /                               |\n");
    printf("|                          B                                |\n");
    printf("|                         / \\                               |\n");
    printf("|                        C   D                              |\n");
    printf("|                           / \\                             |\n");
    printf("|                          E   F                            |\n");
    printf("|                           \\                               |\n");
    printf("|                            G                              |\n");

    BiTree *testTree = (BiTree*)malloc(sizeof(BiTree));

    char treeString[] = "ABC  DE G  F   ";
    int pos = 0;

    CreateBiTreeByString(testTree, treeString, &pos, strlen(treeString));

    Status res = PreOrderTraverse(*testTree, VisitChar);
    if (res == OK) {
        printf("\n前序遍历结束\n");
    } else {
        printf("\n前序遍历失败\n");
    }

    printf("|-----------------------------------------------------------|\n\n");
}


void TestBinaryTreeInOrderTraverse() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                     Test In Traverse                      |\n");
    printf("|                      测试二叉树中序遍历                   |\n");
    printf("|                            A                              |\n");
    printf("|                           /                               |\n");
    printf("|                          B                                |\n");
    printf("|                         / \\                               |\n");
    printf("|                        C   D                              |\n");
    printf("|                           / \\                             |\n");
    printf("|                          E   F                            |\n");
    printf("|                           \\                               |\n");
    printf("|                            G                              |\n");

    BiTree* testTree = (BiTree*)malloc(sizeof(BiTree));

    char treeString[] = "ABC  DE G  F   ";
    int pos = 0;

    CreateBiTreeByString(testTree, treeString, &pos, strlen(treeString));

    Status res = InOrderTraverse(*testTree, VisitChar);
    if (res == OK) {
        printf("\n中序遍历结束\n");
    } else {
        printf("\n中序遍历失败\n");
    }

    printf("|-----------------------------------------------------------|\n\n");
}


void TestBinaryTreeInOrderTraverse2() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                     Test In Traverse2                     |\n");
    printf("|                      测试二叉树中序遍历2                     |\n");
    printf("|                            A                              |\n");
    printf("|                           /                               |\n");
    printf("|                          B                                |\n");
    printf("|                         / \\                               |\n");
    printf("|                        C   D                              |\n");
    printf("|                           / \\                             |\n");
    printf("|                          E   F                            |\n");
    printf("|                           \\                               |\n");
    printf("|                            G                              |\n");

    BiTree* testTree = (BiTree*)malloc(sizeof(BiTree));

    char treeString[] = "ABC  DE G  F   ";
    int pos = 0;

    CreateBiTreeByString(testTree, treeString, &pos, strlen(treeString));

    Status res = InOrderTraverse2(*testTree, VisitChar);
    if (res == OK) {
        printf("\n中序遍历结束\n");
    } else {
        printf("\n中序遍历失败\n");
    }

    printf("|-----------------------------------------------------------|\n\n");
}


void TestHuffmanTree() {
    HuffmanTree* huffmanTree = (HuffmanTree*)malloc(sizeof(HuffmanTree));
    // HuffmanCoding(huffmanTree,           );
}
