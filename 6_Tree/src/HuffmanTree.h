//
// Created by cyberdash@163.com on 2022/1/19.
//

#ifndef CYBER_DASH_HUFFMAN_TREE_H
#define CYBER_DASH_HUFFMAN_TREE_H


typedef struct {
    unsigned int  weight;
    unsigned int  parent, lchild, rchild;
}HTNode, *HuffmanTree;        // 动态分配数组存储赫夫曼树
typedef char **HuffmanCode;   // 动态分配数组春初赫夫曼编码表

void HuffmanCoding(HuffmanTree HT, HuffmanCode *HC, int *w, int n);


#endif // CYBER_DASH_HUFFMAN_TREE_H
