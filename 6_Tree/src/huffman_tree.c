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
#include "huffman_tree.h"
#include "common.h"


/*!
 * @brief **查找elements中权值最小的两个(parent为0的)元素的索引**
 * @param elements 哈夫曼树结点数组(指针)
 * @param last_index 最后元素的数组索引(划定查找范围)
 * @param smallest_elem_index 最小元素的数组索引(指针)
 * @param sec_smallest_elem_index 第二小元素的数组索引(指针)
 * @return 执行结果
 * @note
 * 查找elements中权值最小的两个(parent为0的)元素的索引
 * --------------------------------------------
 * --------------------------------------------
 *
 * --------------------------------------------
 *
 * 注意: 查找的起始索引为1
 *
 * --------------------------------------------
 * - 数组范围判断\n
 * &emsp; **if** 数组元素数量少于2 :\n
 * &emsp;&emsp; 返回NON_EXISTENT\n
 * - 初始化最小值和第二小值\n
 * &emsp; 最小值smallest_weight初始化为-1\n
 * &emsp; 第二小值sec_smallest_weight初始化为-1\n
 * - 遍历数组查找最小的两项\n
 * &emsp; **for loop** 遍历数组 :\n
 * &emsp;&emsp; **if** 当前项parent大于0 :\n
 * &emsp;&emsp;&emsp; continue\n
 * &emsp;&emsp; **if** 最小值 < 0(依然是初始化数值) :\n
 * &emsp;&emsp;&emsp; 最小值更新为当前元素weight\n
 * &emsp;&emsp;&emsp; 最小值元素索引更新为i\n
 * &emsp;&emsp;&emsp; continue\n
 * &emsp;&emsp; **if** 第二小值 <0(依然是初始化数值) :\n
 * &emsp;&emsp;&emsp; if 当前项weight >= 最小值 :\n
 * &emsp;&emsp;&emsp;&emsp; 第二小值更新为当前项weight\n
 * &emsp;&emsp;&emsp;&emsp; 第二小值元素索引更新为i\n
 * &emsp;&emsp;&emsp; **else** (当前项weight < min_weight) :\n
 * &emsp;&emsp;&emsp;&emsp; 第二小值更新为最小值\n
 * &emsp;&emsp;&emsp;&emsp; 最小值更新为当前项weight\n
 * &emsp;&emsp;&emsp;&emsp; 第二小值元素索引更新为smallest_elem_index\n
 * &emsp;&emsp;&emsp; continue\n
 * &emsp;&emsp; **if** 当前元素weight < 最小值 :\n
 * &emsp;&emsp;&emsp; 第二小值元素索引更新为smallest_elem_index\n
 * &emsp;&emsp;&emsp; 第二小值更新为最小值\n
 * &emsp;&emsp;&emsp; 最小值元素索引更新为i\n
 * &emsp;&emsp;&emsp; 最小值更新为当前元素weight\n
 * &emsp;&emsp; **else if** 当前元素weight < 第二小值 :\n
 * &emsp;&emsp;&emsp; 第二小值元素索引更新为i\n
 * &emsp;&emsp;&emsp; 第二小值更新为当前元素weight\n
 */
status_t SelectTwoSmallestElements(huffman_tree_node_t* elements,
                                   int last_index,
                                   int* smallest_elem_index,
                                   int* sec_smallest_elem_index)
{
    // ----- 数组范围判断 -----
    if (last_index < 2) {   // if 数组元素数量少于2
        return NON_EXISTENT;    // 返回NON_EXISTENT
    }

    // ----- 初始化最小值和第二小值 -----
    double smallest_weight = -1;        // 最小值smallest_weight初始化为-1
    double sec_smallest_weight = -1;    // 第二小值sec_smallest_weight初始化为-1

    // ----- 遍历数组查找最小的两项 -----
    for (int i = 1; i <= last_index; i++) { // for loop 遍历数组

        if (elements[i].parent > 0) {  // if 当前项parent大于0
            continue;
        }

        if (smallest_weight < 0) {          // if 最小值 < 0(依然是初始化数值)
            smallest_weight = elements[i].weight;  // 最小值更新为当前元素weight
            *smallest_elem_index = i;           // 最小值元素索引更新为i
            continue;                           // continue
        }

        if (sec_smallest_weight < 0) {                  // if 第二小值 <0(依然是初始化数值)
            if (elements[i].weight >= smallest_weight) {       // if 当前项weight >= 最小值
                sec_smallest_weight = elements[i].weight;          // 第二小值更新为当前项weight
                *sec_smallest_elem_index = i;                   // 第二小值元素索引更新为i
            } else {                                        // 当前项weight < min_weight
                sec_smallest_weight = smallest_weight;          // 第二小值更新为最小值
                smallest_weight = elements[i].weight;              // 最小值更新为当前项weight
                *sec_smallest_elem_index = *smallest_elem_index;// 第二小值元素索引更新为smallest_elem_index
                *smallest_elem_index = i;                       // 最小值元素索引更新为i
            }

            continue;
        }

        if (elements[i].weight < smallest_weight) {    // if 当前元素weight < 最小值
            *sec_smallest_elem_index = *smallest_elem_index;    // 第二小值元素索引更新为smallest_elem_index
            sec_smallest_weight = smallest_weight;  // 第二小值更新为最小值
            *smallest_elem_index = i;   // 最小值元素索引更新为i
            smallest_weight = elements[i].weight;  // 最小值更新为当前元素weight
        } else if (elements[i].weight < sec_smallest_weight) { // 当前元素weight < 第二小值
            *sec_smallest_elem_index = i;   // 第二小值元素索引更新为i
            sec_smallest_weight = elements[i].weight;  // 第二小值更新为当前元素weight
        }
    }

    return OK;  // 返回OK
}


/*!
 * @brief **哈夫曼(Huffman)编码**
 * @param huffman_tree 哈夫曼(Huffman)树
 * @param huffman_codes 哈夫曼(Huffman)编码
 * @param weights 码字权重的数组
 * @param codeword_count 码字数量
 * @note
 * 哈夫曼(Huffman)编码
 * ------------------
 * ------------------
 *
 * ------------------
 *
 * todo: 返回值应该用status_t类型
 *
 * ------------------
 * ## 1 分配内存 ##
 * &emsp; Huffman树的结点数 = 2 * 码字数 - 1 \n
 * &emsp; Huffman树结点数组huffman_tree分配内存, **索引0元素不使用**\n
 * ##2 初始化Huffman树##
 * &emsp; huffman_tree数组, 索引[1 - codeword_count], 前codeword_count个元素(**对应原始码字**)初始化,
 *  parent/left_child/right_child初始化为0, weight为对应码字的权重\n
 * &emsp; huffman_tree数组, 后面codeword_count - 2个元素初始化(权值weight设置为0)\n
 * ##3 建Huffman树##
 * &emsp; **Loop:** 遍历huffman_tree[codeword_count, huffman_tree_node_count - 1]\n
 * &emsp;&emsp; 在huffman_tree_nodes[1 ... i]选择parent为0(未与其他结点构成子树)且weight最小的两个结点,
 * 将他们的数组索引分别为min_index和sec_min_index\n
 * &emsp;&emsp; 新子树根索引为i + 1, 即min_index和sec_min_index是i + 1的左右孩子\n
 * &emsp;&emsp; 更新新子树的根结点权值\n
 * ##4 从叶子到根逆向求每个字符的赫夫曼编码##
 * &emsp; **Loop:** 遍历每个码字\n
 * &emsp;&emsp; cur_huffman_code_index指向cur_huffman_code右侧第一个数据位的索引\n
 * &emsp;&emsp; **Loop:** 从叶子到根逆向求编码\n
 * &emsp;&emsp;&emsp; **If:** child索引是parent索引的左孩子,\n
 * &emsp;&emsp;&emsp;&emsp; **Then:** cur_huffman_code_index位置元素设置为'0'\n
 * &emsp;&emsp;&emsp; **If:** child索引是parent索引的右孩子,\n
 * &emsp;&emsp;&emsp;&emsp; **Then:** cur_huffman_code_index位置元素设置为'1'\n
 * &emsp;&emsp;&emsp; cur_huffman_code_index向前移动1位\n
 * &emsp;&emsp; 算出当前码字的Huffman编码长度\n
 * &emsp;&emsp; 将cur_huffman_code的Huffman编码填充到huffman_codes响应的位置\n
 */
void HuffmanCoding(huffman_tree_node_t* huffman_tree,
                   huffman_code_t huffman_codes,
                   double* weights,
                   int codeword_count)
{
    if (codeword_count <= 1) {
        return;
    }

    // ----- 1 分配内存 -----
    // Huffman树的结点数 = 2 * 码字数 - 1
    int huffman_tree_node_count = 2 * codeword_count - 1;
    // Huffman树结点数组huffman_tree分配内存, (索引0元素不使用)
    huffman_tree = (huffman_tree_t)malloc((huffman_tree_node_count + 1) * sizeof(huffman_tree_node_t));

    int i = 1;  // 起始遍历索引
    huffman_tree_node_t* cur = huffman_tree + 1;    // 遍历指针

    // ----- 2 初始化Huffman树 -----

    // huffman_tree数组, 索引[1 - codeword_count], 前codeword_count个元素(**对应原始码字**)初始化,
    //  parent/left_child/right_child初始化为0, weight为对应码字的权重
    for (; i <= codeword_count; i++, cur++, weights++) {
        cur->weight = *weights;
        cur->parent = 0;
        cur->left_child = 0;
        cur->right_child = 0;
    }

    // huffman_tree数组, 后面codeword_count - 2个元素初始化(权值weight设置为0)
    for (; i <= huffman_tree_node_count; i++, cur++) {
        cur->weight = 0;
        cur->parent = 0;
        cur->left_child = 0;
        cur->right_child = 0;
    }

    // ----- 3 建Huffman树 -----

    // Loop 遍历huffman_tree[codeword_count, huffman_tree_node_count - 1]
    for (i = codeword_count; i < huffman_tree_node_count; i++) {
        // 在huffman_tree_nodes[1 ... i]选择parent为0(未与其他结点构成子树)且weight最小的两个结点,
        // 将他们的数组索引分别为smallest_elem_index和sec_smallest_elem_index
        int smallest_elem_index;
        int sec_smallest_elem_index;
        SelectTwoSmallestElements(huffman_tree, i, &smallest_elem_index, &sec_smallest_elem_index);

        // 新子树根索引为i + 1, 即min_index和sec_min_index是i + 1的左右孩子
        huffman_tree[smallest_elem_index].parent = i + 1;
        huffman_tree[sec_smallest_elem_index].parent = i + 1;

        huffman_tree[i + 1].left_child = smallest_elem_index;
        huffman_tree[i + 1].right_child = sec_smallest_elem_index;

        // 更新新子树的根结点权值
        huffman_tree[i + 1].weight = huffman_tree[smallest_elem_index].weight + huffman_tree[sec_smallest_elem_index].weight;
    }

    // ----- 4 从叶子到根逆向求每个字符的赫夫曼编码 -----
    char* cur_huffman_code = (char*)malloc(codeword_count * sizeof(char));  // 当前哈夫曼编码
    cur_huffman_code[codeword_count - 1] = '\0';

    for (i = 1; i <= codeword_count; i++) { // Loop 遍历每个码字
        // cur_huffman_code_index指向cur_huffman_code右侧第一个数据位的索引
        int cur_huffman_code_index = codeword_count - 2;

        // Loop 从叶子到根逆向求编码
        for (int child = i, parent = huffman_tree[i].parent;
            parent != 0;
            child = parent, parent = huffman_tree[parent].parent)
        {
            if (huffman_tree[parent].left_child == child) { // If child索引是parent索引的左孩子
                cur_huffman_code[cur_huffman_code_index] = '0'; // cur_huffman_code_index位置元素设置为'0'
            } else if (huffman_tree[parent].right_child == child) { // If child索引是parent索引的右孩子
                cur_huffman_code[cur_huffman_code_index] = '1'; // cur_huffman_code_index位置元素设置为'1'
            }
            cur_huffman_code_index--;   // cur_huffman_code_index向前移动1位
        }

        int cur_huffman_code_length = codeword_count - cur_huffman_code_index - 1;  // 算出当前码字的Huffman编码长度

        // 将cur_huffman_code的Huffman编码填充到huffman_codes响应的位置
        for (int j = 0; j < cur_huffman_code_length; j++, cur_huffman_code_index++) {
            huffman_codes[i][j] = cur_huffman_code[cur_huffman_code_index + 1];
        }
    }

    free(cur_huffman_code);
    cur_huffman_code = NULL;
}

