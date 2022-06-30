//
// Created by cyberdash@163.com on 2022/1/23.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "test.h"


Status VisitChar(BINARY_TREE_NODE_DATA e) { // 输出元素e的值
  printf("%c", e);                 // 使用时, 加上格式串
  return OK;
}


Status VisitBinaryTreeNode(binary_tree_node_t e) { // 输出元素e的值
  printf("%c", e.data);                 // 使用时, 加上格式串
  return OK;
}


void TestBinaryTreeCreateBiTree() {
  binary_tree_t* testTree = (binary_tree_t*)malloc(sizeof(binary_tree_t));
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

    binary_tree_t *testTree = (binary_tree_t*)malloc(sizeof(binary_tree_t));

    char treeString[] = "ABC  DE G  F   ";
    int pos = 0;

    Status status = BinaryTreeCreateByPreOrderStringRecursive(testTree, treeString, &pos, strlen(treeString));

    status = BinaryTreePreOrderTraverseRecursive(*testTree, VisitChar);
    if (status == OK) {
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

    binary_tree_t* test_tree = (binary_tree_t*)malloc(sizeof(binary_tree_t));

    char treeString[] = "ABC  DE G  F   ";
    int pos = 0;

    Status status = BinaryTreeCreateByPreOrderStringRecursive(test_tree, treeString, &pos, strlen(treeString));

    status = BinaryTreeInOrderTraverse(*test_tree, VisitChar);
    if (status == OK) {
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

    binary_tree_t* testTree = (binary_tree_t*)malloc(sizeof(binary_tree_t));

    char treeString[] = "ABC  DE G  F   ";
    int pos = 0;

    BinaryTreeCreateByPreOrderStringRecursive(testTree, treeString, &pos, strlen(treeString));

    Status res = BinaryTreeInOrderTraverse2(*testTree, VisitChar);
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
