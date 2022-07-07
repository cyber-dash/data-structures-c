//
// Created by cyberdash@163.com on 2022/1/23.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "test.h"


/*!
 * 字符访问函数
 * @param chr 字符
 * @return 执行结果
 */
Status VisitChar(BINARY_TREE_NODE_DATA chr) {
  printf("%c", chr);
  return OK;
}


/*!
 * 二叉树结点访问函数
 * @param node 二叉树结点
 * @return 执行结果
 */
Status VisitBinaryTreeNode(binary_tree_node_t node) {
  printf("%c", node.data);
  return OK;
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

    binary_tree_t* binary_tree = (binary_tree_t*)malloc(sizeof(binary_tree_t));

    char pre_order_str[] = "ABC  DE G  F   ";
    int traverse_index = 0;

    Status status = BinaryTreeCreateByPreOrderStringRecursive(binary_tree,
                                                              pre_order_str,
                                                              &traverse_index,
                                                              strlen(pre_order_str));
    if (status != OK) {
        printf("\n建二叉树失败\n");
    }

    status = BinaryTreePreOrderTraverseRecursive(*binary_tree, VisitChar);
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

    binary_tree_t* binary_tree = (binary_tree_t*)malloc(sizeof(binary_tree_t));

    char pre_order_str[] = "ABC  DE G  F   ";
    int traverse_index = 0;

    Status status = BinaryTreeCreateByPreOrderStringRecursive(binary_tree, pre_order_str, &traverse_index, strlen(pre_order_str));
    if (status != OK) {
        printf("\n建二叉树失败\n");
    }

    status = BinaryTreeInOrderTraverse(*binary_tree, VisitChar);
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

    binary_tree_t* binary_tree = (binary_tree_t*)malloc(sizeof(binary_tree_t));

    char treeString[] = "ABC  DE G  F   ";
    int traverse_index = 0;

    BinaryTreeCreateByPreOrderStringRecursive(binary_tree, treeString, &traverse_index, strlen(treeString));

    Status res = BinaryTreeInOrderTraverse2(*binary_tree, VisitChar);
    if (res == OK) {
        printf("\n中序遍历结束\n");
    } else {
        printf("\n中序遍历失败\n");
    }

    printf("|-----------------------------------------------------------|\n\n");
}


void TestHuffmanTree() {

    char codewords[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    double probabilities[8] = { 0.01, 0.02, 0.03, 0.04, 0.1, 0.2, 0.25, 0.35 };

    huffman_tree_node_t huffman_tree_nodes[9];

    char huffman_codes[9][9];

    char** codes = (huffman_code_t)huffman_codes;

    HuffmanCoding(huffman_tree_nodes, codes, probabilities, 8);
    // HuffmanCoding(huffman_tree_nodes, (huffman_code_t*)&huffman_codes, probabilities, 8);
}
