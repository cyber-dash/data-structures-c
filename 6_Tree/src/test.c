/*!
 * @file test.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 树测试用例源文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "test.h"


/*!
 * @brief 字符访问函数
 * @param chr 字符
 * @return 执行结果
 */
Status VisitChar(BINARY_TREE_NODE_DATA chr) {
  printf("%c", chr);
  return OK;
}


/*!
 * @brief 二叉树结点访问函数
 * @param node 二叉树结点
 * @return 执行结果
 */
Status VisitBinaryTreeNode(binary_tree_node_t node) {
  printf("%c", node.data);
  return OK;
}


/*!
 * @brief <h1>二叉树前序遍历测试函数</h1>
 * @note
 */
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

    /// ###1 构造二叉树###
    /// &emsp; 使用\"ABC&nbsp;&nbsp;DE&nbsp;G&nbsp;&nbsp;F&nbsp;&nbsp;&nbsp;\"\n
    /// &emsp; 调用BinaryTreeCreateByPreOrderStringRecursive, 构造二叉树\n
    /// ```
    ///                            A
    ///                           /
    ///                          B
    ///                         / \
    ///                        C   D
    ///                           / \
    ///                          E   F
    ///                           \
    ///                            G
    /// ```
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

    /// ###2 二叉树前序遍历###
    /// &emsp; 调用BinaryTreePreOrderTraverseRecursive, 执行二叉树前序遍历\n
    status = BinaryTreePreOrderTraverseRecursive(*binary_tree, VisitChar);
    if (status == OK) {
        printf("\n前序遍历结束\n");
    } else {
        printf("\n前序遍历失败\n");
    }

    printf("|-----------------------------------------------------------|\n\n");
}


/*!
 * @brief <h1>测试二叉树中序遍历</h1>
 * @note
 */
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


/*!
 * @brief <h1>测试二叉树中序遍历2</h1>
 * @note
 */
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


/*!
 * @brief <h1>测试二叉树后序遍历</h1>
 * @note
 */
void TestBinaryTreePostOrderTraverse() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                    Test Post Traverse                      |\n");
    printf("|                      测试二叉树后序遍历                   |\n");
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

    status = BinaryTreePostOrderTraverseRecursive(*binary_tree, VisitChar);
    if (status == OK) {
        printf("\n后序遍历结束\n");
    } else {
        printf("\n后序遍历失败\n");
    }

    printf("|-----------------------------------------------------------|\n\n");
}


/*!
 * @brief <h1>测试二叉树层序遍历</h1>
 * @note
 */
void TestBinaryTreeLevelOrderTraverse() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                    Test Level Traverse                    |\n");
    printf("|                      测试二叉树层序遍历                      |\n");
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

    status = BinaryTreeLevelOrderTraverse(*binary_tree, VisitChar);
    if (status == OK) {
        printf("\n层序遍历结束\n");
    } else {
        printf("\n层序遍历失败\n");
    }

    printf("|-----------------------------------------------------------|\n\n");
}


/*!
 * @brief <h1>测试哈夫曼(Huffman)编码</h1>
 * @note
 */
void TestHuffmanCoding() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                     Test HuffmanTree                      |\n");
    printf("|                        测试哈夫曼编码                       |\n\n");

    /// ###1 声明码字###
    /// &emsp; 码字:            { 'a',  'b',  'c',  'd',  'e', 'f', 'g',  'h'  } \n
    /// &emsp; 各码字权重(权值): {  0.01, 0.02, 0.03, 0.04, 0.1, 0.2, 0.25, 0.35 }
    char codewords[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};                // 码字(数组)
    double probabilities[8] = { 0.01, 0.02, 0.03, 0.04, 0.1, 0.2, 0.25, 0.35 };   // 码字权重(数组)

    huffman_tree_t huffman_tree = NULL; // 哈夫曼树
    huffman_code_t huffman_codes;       // 哈夫曼编码

    /// ###2 构造哈夫曼编码###
    /// &emsp; 调用HuffmanCoding
    HuffmanCoding(huffman_tree, huffman_codes, probabilities, 8);

    /// ###3 打印哈夫曼编码###
    for (int i = 1; i <= 8; i++) {
        printf("码字:%c|概率:%.2lf, 哈夫曼(Huffman)编码: %s\n", codewords[i - 1], probabilities[i - 1], huffman_codes[i]);
    }

    printf("|-----------------------------------------------------------|\n\n");
}
