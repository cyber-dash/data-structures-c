/*!
 * @file huffman_tree.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief Huffman(哈夫曼)树源文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "huffman_tree.h"
#include "common.h"


/*!
 * 查找items中权值最小的两个(parent为0的)元素的索引
 * @param items 哈夫曼树结点数组(指针)
 * @param last_index 最后索引(划定查找范围)(起始索引为1)
 * @param min_index 最小元素数组索引(指针)
 * @param sec_min_index 第二小元素数组索引(指针)
 */
int SelectTwoMinItems(huffman_tree_node_t* items, int last_index, int* min_index, int* sec_min_index) {

    // 如果数组元素少于2, 返回FALSE
    if (last_index < 2) {
        return FALSE;
    }

    double min_weight = -1;     // 最小权值
    double sec_min_weight = -1; // 第二小权值

    // 从1到last_index遍历
    for (int i = 1; i <= last_index; i++) {

        // parent大于0(已是某子树子节点), continue
        if (items[i].parent > 0) {
            continue;
        }

        // min_weight未赋值
        if (min_weight < 0) {
            min_weight = items[i].weight;
            *min_index = i;
            continue;
        }

        // sec_min_weight未赋值, min_weight已赋值
        if (sec_min_weight < 0) {
            if (items[i].weight >= min_weight) {    // 当前项weight >= min_weight
                sec_min_weight = items[i].weight;
                *sec_min_index = i;
            } else {    // 当前项weight < min_weight
                sec_min_weight = min_weight;
                min_weight = items[i].weight;
                *sec_min_index = *min_index;
                *min_index = i;
            }
            continue;
        }

        if (items[i].weight < min_weight) {
            // 第二小item信息更新
            *sec_min_index = *min_index;
            sec_min_weight = min_weight;
            // 最小item信息更新
            *min_index = i;
            min_weight = items[i].weight;
        } else if (items[i].weight < sec_min_weight) {
            // 第二小item更新
            *sec_min_index = i;
            sec_min_weight = items[i].weight;
        }
    }

    return TRUE;
}


/*!
 * @brief <h1>哈夫曼(Huffman)编码</h1>
 * @param huffman_tree **哈夫曼(Huffman)树**
 * @param huffman_codes **哈夫曼(Huffman)编码**
 * @param weights **码字权重的数组**
 * @param codeword_count **码字数量**
 */
void HuffmanCoding(huffman_tree_node_t* huffman_tree,
                   huffman_code_t huffman_codes,
                   double* weights,
                   int codeword_count)
{
    if (codeword_count <= 1) {
        return;
    }

    /// ## 1 分配内存 ##
    /// &emsp; Huffman树的结点数 = 2 * 码字数 - 1 \n
    /// &emsp; Huffman树结点数组huffman_tree分配内存, **索引0元素不使用**
    int huffman_tree_node_count = 2 * codeword_count - 1;
    huffman_tree = (huffman_tree_t)malloc((huffman_tree_node_count + 1) * sizeof(huffman_tree_node_t));

    int i = 1;
    huffman_tree_node_t* cur = huffman_tree + 1;

    /// ##2 初始化Huffman树##
    /// &emsp; 索引[1 - codeword_count]数组元素, parent/left_child/right_child初始化为0, weight为对应码字的权重\n

    /// ###2.1 数组索引[1 - codeword_count]元素赋值(不包括索引0)###
    /// &emsp; huffman_tree数组索引[1 - codeword_count], codeword_count个元素(**对应原始码字**)初始化
    for (; i <= codeword_count; i++, cur++, weights++) {
        cur->weight = *weights;
        cur->parent = 0;
        cur->left_child = 0;
        cur->right_child = 0;
    }

    /// ###2.2 数组后codeword_count - 2个元素赋值###
    /// &emsp; huffman_tree数组的后面codeword_count - 2个结点初始化(权值weight设置为0)
    for (; i <= huffman_tree_node_count; i++, cur++) {
        cur->weight = 0;
        cur->parent = 0;
        cur->left_child = 0;
        cur->right_child = 0;
    }

    /// ##3 建Huffman树##
    /// &emsp; **Loop:** 遍历huffman_tree[codeword_count, huffman_tree_node_count - 1]\n
    for (i = codeword_count; i < huffman_tree_node_count; i++) {
        /// &emsp;&emsp; 在huffman_tree_nodes[1 ... i]选择parent为0(未与其他结点构成子树)且weight最小的两个结点,
        /// 将他们的数组索引分别为min_index和sec_min_index
        int min_index;
        int sec_min_index;
        SelectTwoMinItems(huffman_tree, i, &min_index, &sec_min_index);

        /// &emsp;&emsp; 新子树根索引为i + 1, 即min_index和sec_min_index是i + 1的左右孩子
        huffman_tree[min_index].parent = i + 1;
        huffman_tree[sec_min_index].parent = i + 1;

        huffman_tree[i + 1].left_child = min_index;
        huffman_tree[i + 1].right_child = sec_min_index;

        /// &emsp;&emsp; 更新新子树的根结点权值
        huffman_tree[i + 1].weight = huffman_tree[min_index].weight + huffman_tree[sec_min_index].weight;
    }

    /// ##4 从叶子到根逆向求每个字符的赫夫曼编码##
    /// ###4.1 暂存变量cur_huffman_code###
    char* cur_huffman_code = (char*)malloc(codeword_count * sizeof(char));
    cur_huffman_code[codeword_count - 1] = '\0';

    /// ###4.2 求每个码字的Huffman编码###
    /// &emsp; **Loop:** 遍历每个码字\n
    for (i = 1; i <= codeword_count; i++) {
        /// &emsp;&emsp; cur_huffman_code_index指向cur_huffman_code右侧第一个数据位的索引
        int cur_huffman_code_index = codeword_count - 2;

        /// &emsp;&emsp; **Loop:** 从叶子到根逆向求编码\n
        for (int child = i, parent = huffman_tree[i].parent;
            parent != 0;
            child = parent, parent = huffman_tree[parent].parent)
        {
            /// &emsp;&emsp;&emsp; **If:** child索引是parent索引的左孩子,\n
            /// &emsp;&emsp;&emsp;&emsp; **Then:** cur_huffman_code_index位置元素设置为'0'\n
            /// &emsp;&emsp;&emsp; **If:** child索引是parent索引的右孩子,\n
            /// &emsp;&emsp;&emsp;&emsp; **Then:** cur_huffman_code_index位置元素设置为'1'\n
            if (huffman_tree[parent].left_child == child) {
                cur_huffman_code[cur_huffman_code_index] = '0';
            } else if (huffman_tree[parent].right_child == child) {
                cur_huffman_code[cur_huffman_code_index] = '1';
            }
            /// &emsp;&emsp;&emsp; cur_huffman_code_index向前移动1位
            cur_huffman_code_index--;
        }

        /// &emsp;&emsp; 算出当前码字的Huffman编码长度
        int cur_huffman_code_length = codeword_count - cur_huffman_code_index - 1;

        /// &emsp;&emsp; 将cur_huffman_code的Huffman编码填充到huffman_codes响应的位置
        for (int j = 0; j < cur_huffman_code_length; j++, cur_huffman_code_index++) {
            huffman_codes[i][j] = cur_huffman_code[cur_huffman_code_index + 1];
        }
    }

    free(cur_huffman_code);
    cur_huffman_code = NULL;
}

