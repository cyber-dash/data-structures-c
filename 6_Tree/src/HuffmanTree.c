//
// Created by cyberdash@163.com on 2022/1/19.
//

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "HuffmanTree.h"
#include "type.h"


int Select(huffman_tree_t items, int last_index, int* min_index, int* sec_min_index);


void HuffmanCoding(huffman_tree_node_t* huffman_tree_nodes,
                   huffman_code_t* huffman_code_array,
                   int* weight_array_ptr,
                   int codeword_count)
{
    // w存放n个字符的权值(均>0), 构造赫夫曼树HT, 并求出n个字符的赫夫曼编码HC.
    if (codeword_count <= 1) {
        return;
    }

    int huffman_tree_node_count = 2 * codeword_count - 1;  // m个节点
    huffman_tree_nodes = (huffman_tree_t)malloc((huffman_tree_node_count + 1) * sizeof(huffman_tree_node_t));      // 0号单元未用

    int i = 1;
    huffman_tree_node_t* cur = huffman_tree_nodes + 1;

    // 从数组索引1开始, 将n个codeword对应的节点初始化
    for (; i <= codeword_count; i++, cur++, weight_array_ptr++) {
        cur->weight = *weight_array_ptr;
        cur->parent = 0;
        cur->left_child = 0;
        cur->right_child = 0;
    }

    // huffman_tree_nodes数组的后面剩余节点初始化(权值设置为0)
    for (; i <= huffman_tree_node_count; i++, cur++) {
        cur->weight = 0;
        cur->parent = 0;
        cur->left_child = 0;
        cur->right_child = 0;
    }

    /// --- 建Huffman树 ---

    for (i = codeword_count; i <= huffman_tree_node_count; i++) {
        // 在huffman_tree_nodes[1 ... huffman_tree_node_count]选择parent为0(未与其他结点构成子树)且weight最小的两个结点,
        // 其数组索引分别为min_index和sec_min_index
        int min_index;
        int sec_min_index;
        Select(huffman_tree_nodes, i, &min_index, &sec_min_index);

        // 新子树parent为i + 1
        huffman_tree_nodes[min_index].parent = i + 1;
        huffman_tree_nodes[sec_min_index].parent = i + 1;

        // 设置新子树的左右孩子
        huffman_tree_nodes[i + 1].left_child = min_index;
        huffman_tree_nodes[i + 1].right_child = sec_min_index;

        // 新子树的权值
        huffman_tree_nodes[i + 1].weight = huffman_tree_nodes[min_index].weight + huffman_tree_nodes[sec_min_index].weight;
    }

    // ---- 从叶子到根逆向求每个字符的赫夫曼编码 ----

    huffman_code_array = (huffman_code_t*)malloc((codeword_count + 1) * sizeof(char*));

    // n个字符编码的哈夫曼编码,
    char* cur_huffman_code = (char*)malloc(codeword_count * sizeof(char));
    cur_huffman_code[codeword_count - 1] = 0;

    for (i = 1; i <= codeword_count; i++) {
        // int cur_huffman_code_index = codeword_count - 1;    // 当前哈夫曼编码的数组索引位
        int cur_huffman_code_index = codeword_count - 2;    // 当前哈夫曼编码的数组索引位

        // 从叶子到根逆向求编码
        for (int child = i, parent = huffman_tree_nodes[i].parent;  // 循环初始化的child/parent
            parent != 0;                                            // 循环终止条件: parent != 0
            child = parent, parent = huffman_tree_nodes[parent].parent)
        {
            /// 设置哈夫曼编码当前索引为的值
            if (huffman_tree_nodes[parent].left_child == child) {   // 如果child索引是parent索引的左孩子, 设置为0
                // cur_huffman_code[cur_huffman_code_index - 1] = '0';
                cur_huffman_code[cur_huffman_code_index] = '0';
            } else if (huffman_tree_nodes[parent].right_child == child) {   // 如果child索引是parent索引的右孩子, 设置为1
                // cur_huffman_code[cur_huffman_code_index - 1] = '1';
                cur_huffman_code[cur_huffman_code_index] = '1';
            }
            cur_huffman_code_index--;
        }

        // *huffman_code_array[i] = (char*)malloc((codeword_count - cur_huffman_code_index) * sizeof(char));    // 为第i个字符编码分配空间
        // strcpy_s(*huffman_code_array[i], codeword_count - cur_huffman_code_index, &cur_huffman_code[cur_huffman_code_index]);          // 从cd复制编码(串)到HC

        int cur_huffman_code_length = codeword_count - cur_huffman_code_index - 1;
        *huffman_code_array[i] = (char*)malloc(cur_huffman_code_length * sizeof(char));    // 为第i个字符编码分配空间
        strcpy_s(*huffman_code_array[i], cur_huffman_code_length, &cur_huffman_code[cur_huffman_code_index]);          // 从cd复制编码(串)到HC
    }

    printf("%s\n", cur_huffman_code);

    free(cur_huffman_code);
}


/*!
 *
 * @param items
 * @param last_index
 * @param min_index
 * @param sec_min_index
 */
int Select(huffman_tree_node_t* items, int last_index, int* min_index, int* sec_min_index) {
    if (last_index < 2) {
        return FALSE;
    }

    double min_weight = 0;
    unsigned int sec_min_weight = 0;

    if (items[1].weight >= items[2].weight) {
        *min_index = 2;
        *sec_min_index = 1;
        min_weight = items[2].weight;
        sec_min_weight = items[1].weight;
    } else {
        *min_index = 1;
        *sec_min_index = 2;
        min_weight = items[1].weight;
        sec_min_weight = items[2].weight;
    }

    if (last_index == 2) {
        return TRUE;
    }

    for (int i = 3; i <= last_index; i++) {
        int cur_weight = items[i].weight;
        if (cur_weight < min_weight) {  // 如果cur_weight比之前最小的weight(min_weight)还小,
            // 第二小item信息更新
            *sec_min_index = *min_index;
            sec_min_weight = min_weight;
            // 最小item信息更新
            *min_index = i;
            min_weight = cur_weight;
        } else if (cur_weight < sec_min_weight) {   // 如果min_weight < cur_weight < sec_min_weight
            // 第二小item更新
            *sec_min_index = i;
            sec_min_weight = cur_weight;
        }
    }
}
