/*!
 * @file huffman_tree.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief Huffman(哈夫曼)树头文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_HUFFMAN_TREE_H
#define CYBER_DASH_HUFFMAN_TREE_H


/*! @brief 哈夫曼(Huffman)树结点 */
typedef struct huffman_tree_node {
    int parent;                 //!< 父结点索引
    unsigned int  left_child;   //!< 左孩子结点索引
    unsigned int  right_child;  //!< 右孩子结点索引
    double weight;              //!< 权重
} huffman_tree_node_t;

/*!
 * @brief 哈夫曼(Huffman)树
 * @note
 * 使用huffman_tree_node_t类型的数组, 实现哈夫曼(Huffman)树
 */
typedef huffman_tree_node_t* huffman_tree_t;

/*!
 * @brief 哈夫曼编码表
 * @note
 * 支持最多100个码字\n 编码长度最多999个char类型字符
 */
typedef char huffman_code_t[100][1000];

// 哈夫曼(Huffman)编码
void HuffmanCoding(huffman_tree_node_t* huffman_tree,
                   huffman_code_t huffman_codes,
                   double* weights,
                   int codeword_count);


#endif // CYBER_DASH_HUFFMAN_TREE_H
