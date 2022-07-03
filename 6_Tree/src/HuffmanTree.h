//
// Created by cyberdash@163.com on 2022/1/19.
//

#ifndef CYBER_DASH_HUFFMAN_TREE_H
#define CYBER_DASH_HUFFMAN_TREE_H


typedef struct {
    double weight;
    int  parent;
    unsigned int  left_child;
    unsigned int  right_child;
} huffman_tree_node_t, *huffman_tree_t;        // 动态分配数组存储赫夫曼树

typedef char **huffman_code_t;   // 动态分配数组, 存储赫夫曼编码表

void HuffmanCoding(huffman_tree_node_t* huffman_tree_nodes, huffman_code_t* huffman_code, int *weight_array_ptr, int codeword_count);


#endif // CYBER_DASH_HUFFMAN_TREE_H
