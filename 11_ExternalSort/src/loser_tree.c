/*!
 * @file loser_tree.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 败者树源文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "loser_tree.h"


/*!
 * @brief **交换函数**
 * @param item1 元素1(指针)
 * @param item2 元素2(指针)
 * 交换函数
 * -------
 * -------
 *
 * -------
 */
void swap(int* item1, int* item2) {
    int tmp = *item1;
    *item1 = *item2;
    *item2 = tmp;
}


/*!
 * @brief **调整败者树**
 * @param loser_tree 败者树非叶子结点数组(指针)
 * @param leaves 败者树叶子结点数组(指针)
 * @param K 路数
 * @param winner_leaf_index 胜者索引
 * @note
 * 调整败者树
 * ---------
 * ---------
 *
 * ---------
 *
 * 沿着"路径(叶子结点leaves[winner_leaf_index] --> 根结点loser_tree[0])"调整败者树\n
 * 每个遍历结点与其父节点作比较, 败者存在父节点, 胜者继续向上执行相同操作\n
 *
 * ---------
 * **for loop** 遍历从叶子leaves[winner_leaf_index]的双亲结点到根结点的所有节点 :\n
 * &emsp; **if** 叶子节点leaves[winner_leaf_index]的key > 当前祖先节点leaves[loser_tree[cur_ancestor_index]]的key
 * (即winner_leaf_index在本轮为败者, loser_tree[cur_ancestor_index]为胜者) : \n
 * &emsp;&emsp; winner_leaf_index作为本轮败者存入loser_tree[cur_ancestor_index]\n
 * &emsp;&emsp; loser_tree[cur_ancestor_index]作为胜者, 赋给winner_leaf_index继续向上进行下一轮比较\n
 * 将最终的胜者赋给loser_tree[0]
 */
void LoserTreeAdjust(int* loser_tree, leaf_t* leaves, int K, int winner_leaf_index) {
    // for loop 遍历从叶子leaves[winner_leaf_index]的双亲结点到根结点的所有节点
    for (int cur_ancestor_index = (winner_leaf_index + K) / 2;
         cur_ancestor_index > 0;
         cur_ancestor_index = cur_ancestor_index / 2)
    {
        // if 叶子节点leaves[winner_leaf_index]的key > 当前祖先节点leaves[loser_tree[cur_ancestor_index]]的key
        // (即winner_leaf_index在本轮为败者, loser_tree[cur_ancestor_index]为胜者)
		if(leaves[winner_leaf_index].key > leaves[loser_tree[cur_ancestor_index]].key) {
            // winner_leaf_index作为本轮败者存入loser_tree[cur_ancestor_index]
            // loser_tree[cur_ancestor_index]作为胜者, 赋给winner_leaf_index继续向上进行下一轮比较\n
            swap(&winner_leaf_index, &loser_tree[cur_ancestor_index]);
		}
	}

    loser_tree[0] = winner_leaf_index;  // 将最终的胜者赋给loser_tree[0]
}


/*!
 * @brief **构造败者树**
 * @param loser_tree 非叶子节点数组
 * @param leaves 叶子节点数组
 * @param K 路数
 * @param sorted_list_lengths 各路有序序列的长度数组
 * @note
 * 构造败者树
 * ---------
 * ---------
 *
 * ---------
 *
 * **loser_tree数组** 说明:\n
 * 每个元素的值, 为叶子数组的数组索引值\n
 * 其中loser_tree[0]为根节点, 用来保存每趟最终的胜者(最小值)\n\n
 * **leaves数组** 说明:\n
 * leaves[i]表示第i个归并段(有序序列)的队头(未进入有序区的最前元素)\n
 *
 * ---------
 * ###1 非叶子节点数组初始化(各元素都设为K)###
 * &emsp; **for loop** 遍历loser_tree :\n
 * &emsp;&emsp; 每个非叶子元素的值(叶子数组的数组索引)都设为K(不在叶子数组的索引范围内[0 ... K - 1])\n
 * ```
 * 初始化:
 *
 * K: 5
 *
 * int arr0[] = { 6, 15, 16, 17, 18, 19, 20, 70, 71, 72, 73, 74, 75, 76, 77, 78 };
 * int arr1[] = { 12, 13, 14, 16, 16, 26, 26, 26, 36, 36, 36, 55, 55, 55, 55, 81, 81, 81 };
 * int arr2[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
 * int arr3[] = { 9, 18, 27, 36, 45, 54, 63, 72, 81, 90, 99 };
 * int arr4[] = { 20, 24, 28, 46, 52, 64 };
 *
 * 非叶子数组: { 5, 5, 5, 5, 5 }
 * 叶子数组: { {key: 6}, {key: 12}, {key: 10}, {key: 9}, {key: 20} }
 *
 *              5  ----- 5
 *             / \
 *            /   \
 *           /     \
 *          5       5
 *         / \     / \
 *        5 6|0 12|1 10|2
 *       / \
 *     9|3 20|4
 *
 *
 *     12|1 表示 (值)12|(叶子数组索引)1
 *     10|2 表示 (值)10|(叶子数组索引)2
 *
 *     ...
 * ```
 * ### 2 依次用叶子数组元素调整败者树###
 * &emsp; **while** 从后向前遍历叶子数组 :\n
 * &emsp;&emsp; 使用当前叶子索引, 调用LoserTreeAdjust(向上)调整败者树 \n
 * &emsp;&emsp; leaf_index对应的有序序列, 长度减1 \n
 * ```
 * 调整树结束:
 *
 * K: 5
 *
 * 非叶子数组: { 0, 2, 3, 1, 4 }
 * 叶子数组: { {key: 6}, {key: 12}, {key: 10}, {key: 9}, {key: 20} }
 *
 *             2 ----- 0
 *            / \
 *           /   \
 *          /     \
 *         3       1
 *        / \     / \
 *       4 6|0 12|1 10|2
 *      / \
 *    9|3 20|4
 * ```
 */
void LoserTreeCreate(int* loser_tree, leaf_t* leaves, int K, int* sorted_list_lengths) {

    // ----- 1 初始化非叶子数组和叶子数组 -----
    for (int i = 0; i < K; ++i) {   // for loop 遍历loser_tree
        loser_tree[i] = K;  // 把所有非叶子元素的值(败者初始值)都设为K(不在叶子数组的索引范围内[0 ... K - 1])
    }
    // 示例:
    //             5  ----- 5
    //            / \
    //           /   \
    //          /     \
    //         5       5
    //        / \     / \
    //       5 6|0 12|1 10|2
    //      / \
    //    9|3 20|4
    //
    //  12|1 表示 (值)12|(叶子数组索引)1
    //  10|2 表示 (值)10|(叶子数组索引)2

    leaves[K].key = INT_MIN;// leaves[K]的关键字设置成极小值

    // ----- 2 依次用叶子数组元素调整败者树 -----
    for (int leaf_index = K - 1; leaf_index >= 0; leaf_index--) {   // while 从后向前遍历叶子数组
        LoserTreeAdjust(loser_tree, leaves, K, leaf_index); // 使用当前叶子索引, 调用LoserTreeAdjust(向上)调整败者树
        sorted_list_lengths[leaf_index]--;  // leaf_index对应的有序序列, 长度减1
    }

    // 调整树结束:
    //             2 ----- 0
    //            / \
    //           /   \
    //          /     \
    //         3       1
    //        / \     / \
    //       4 6|0 12|1 10|2
    //      / \
    //    9|3 20|4
}


/*!
 * @brief **K路归并**
 * @param K_way_sorted_lists K组待归并有序序列
 * @param K 路数
 * @param sorted_list_lengths K组有序序列的长度
 * @note
 * K路归并
 * ------
 * ------
 *
 * ------
 *
 * todo: K路归并和打印解耦
 *
 * ------
 * ###1 初始化败者树叶子数组和非叶子数组###
 * ###2 叶子数组读入各归并段首元素###
 * &emsp; **for loop** 遍历K个输入归并段 : \n
 * &emsp;&emsp; 该段当前第0个记录的关键字, 赋值到败者树叶子数组leaves[i].key\n
 * ### 3 构造败者树 ###
 * ### 4 构造各路的当前遍历索引的数组 ###
 * &emsp; 初始化每个元素为1(构造败者树时, 各路的索引0元素已经进入败者树)\n
 * ### 5 使用败者树进行K路归并 ###
 * &emsp; **while** 败者树根结点有值(根结点的key不为INT_MAX) :\n
 * &emsp;&emsp; 取根结点的值为胜者\n
 * &emsp;&emsp; **if** 胜者的归并段还有元素 :\n
 * &emsp;&emsp;&emsp; 胜者的归并段(队列)的当前头元素, 赋值给胜者叶子结点\n
 * &emsp;&emsp;&emsp; 胜者的归并段(队列)的当前头元素指向后一位置(traverse_index_per_sorted_list[winner_leaf_index]++)\n
 * &emsp;&emsp; **else** (胜者的归并段元素已经全部被归并) :\n
 * &emsp;&emsp;&emsp; 胜者叶子结点的key设置为INT_MAX\n
 * &emsp;&emsp; 使用胜者的叶子数组索引执行LoserTreeAdjust(调整败者树)\n
 */
void KWayMerge(int* K_way_sorted_lists[], int K, int* sorted_list_lengths) {

    // ----- 1 初始化败者树叶子数组和非叶子数组 -----
    leaf_t* leaves = (leaf_t*)malloc(sizeof(leaf_t) * (K + 1));
    memset(leaves, 0, sizeof(leaf_t) * K);

    int* loser_tree = (int*)malloc(sizeof(int) * K);
    memset(loser_tree, 0, sizeof(int) * K);

    // ----- 2 叶子数组读入各归并段首元素 -----
    // todo: 这部分可以写到Create里
    for (int i = 0; i < K; ++i) {   // for loop 遍历K个输入归并段
        leaves[i].key = K_way_sorted_lists[i][0];   // 该段当前第0个记录的关键字, 赋值到败者树叶子数组leaves[i].key
    }

    // ----- 3 构造败者树 -----
    LoserTreeCreate(loser_tree, leaves, K, sorted_list_lengths);

    // ----- 4 构造各路的当前遍历索引的数组 -----
    int* traverse_index_per_sorted_list = (int*)malloc(sizeof(int) * K);
    for (int leaf_index = 0; leaf_index < K; leaf_index++) {
        traverse_index_per_sorted_list[leaf_index] = 1; // 初始化每个元素为1(构造败者树时, 各路的索引0元素已经进入败者树)
    }

    // ----- 5 使用败者树进行K路归并 -----
    while (leaves[loser_tree[0]].key != INT_MAX) {  // while 败者树根结点有值(根结点的key不为INT_MAX)
        int winner_leaf_index = loser_tree[0];  // 取根结点的值为胜者
        printf("%d  ", leaves[loser_tree[0]].key);

        // if 胜者的归并段还有元素
        if (traverse_index_per_sorted_list[winner_leaf_index] <= sorted_list_lengths[winner_leaf_index]) {
            // 胜者的归并段的当前头元素, 赋值给胜者叶子结点
            leaves[winner_leaf_index].key =
                K_way_sorted_lists[winner_leaf_index][traverse_index_per_sorted_list[winner_leaf_index]];
            // 胜者的归并段(队列)的当前头元素指向后一位置
            traverse_index_per_sorted_list[winner_leaf_index]++;
        } else {    // else (胜者的归并段元素已经全部被归并)
            leaves[winner_leaf_index].key = INT_MAX;    // 胜者叶子结点的key设置为INT_MAX\n
        }

        LoserTreeAdjust(loser_tree, leaves, K, winner_leaf_index); // 使用胜者的叶子数组索引执行LoserTreeAdjust(调整败者树)
    }

    printf("\n");
}
