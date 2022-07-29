/*!
 * @file loser_tree_t.c
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
 * <h1>交换函数</h1>
 * @param item1 **元素1**(指针)
 * @param item2 **元素2**(指针)
 */
void swap(int* item1, int* item2) {
    int tmp = *item1;
    *item1 = *item2;
    *item2 = tmp;
}


/*!
 * <h1>调整败者树</h1>
 * @param loser_tree
 * @param leaves
 * @param winner_leaf_index
 * @note
 */
void LoserTreeAdjust(int* loser_tree, leaf_t* leaves, int K, int winner_leaf_index) {
    /// 沿从叶子结点leaves[winner_leaf_index]到根结点loser_tree[0]的路径调整败者树
    /// 结点与父节点作比较, 败者存在父节点, 胜者继续向上执行相同操作
    /// ###1 沿从叶子节点leaves[winner_leaf_index]到根节点loser_tree[0]的路径调整败者树###
    /// &emsp; **for loop* 遍历从叶子leaves[winner_leaf_index]的双亲结点到根结点的所有节点 :\n
    for (int cur_ancestor_index = (winner_leaf_index + K) / 2;
         cur_ancestor_index > 0;
         cur_ancestor_index = cur_ancestor_index / 2)
    {
        /// &emsp;&emsp; **if** 叶子节点leaves[winner_leaf_index]的key 大于
        /// 当前祖先节点leaves[loser_tree[cur_ancestor_index]]的key :\n
        /// &emsp;&emsp; (即winner_leaf_index在本轮为败者, loser_tree[cur_ancestor_index]为胜者)
		if(leaves[winner_leaf_index].key > leaves[loser_tree[cur_ancestor_index]].key) {
            /// &emsp;&emsp;&emsp; winner_leaf_index作为本轮败者存入loser_tree[cur_ancestor_index]\n
            /// &emsp;&emsp;&emsp; loser_tree[cur_ancestor_index]作为胜者, 赋给winner_leaf_index继续向上进行下一轮比较\n
            swap(&winner_leaf_index, &loser_tree[cur_ancestor_index]);
		}
	}

    /// 将最终的胜者赋给loser_tree[0]
    loser_tree[0] = winner_leaf_index;							//顶部结点为最小值
}


/*!
 * <h1>构造败者树</h1>
 * @param loser_tree **败者树非叶子节点数组**
 * @param leaves **败者树叶子节点数组**
 * @param K **路数**
 * @param sorted_list_lengths
 * @note
 * loser_tree构成非叶子结点, 其中loser_tree[0]为根节点, 用来保存最小值
 */
void CreateLoserTree(int* loser_tree, leaf_t* leaves, int K, int* sorted_list_lengths) {
    leaves[K].key = INT_MIN;// 设INT_MIN为关键字可能的最小值

    /// ###1 设置败者树非叶子节点数组各元素初值(都设为K)###
    /// &emsp; **for loop** 遍历loser_tree :\n
    /// &emsp;&emsp; loser_tree[i] <= K\n
    /// &emsp; (叶子数组的索引范围是[0 ... K], 此时把所有非叶子元素的值都设为K, 不在叶子数组的索引范围内)\n
    for (int i = 0; i < K; ++i) {
        loser_tree[i] = K;                    // 设置loserTree中"败者"的初值
    }
    /// 示例:
    /// &emsp; 初始:\n
    /// ```
    ///             5  ----- 5
    ///            / \
    ///           /   \
    ///          /     \
    ///         5       5
    ///        / \     / \
    ///       5 6|0 12|1 10|2
    ///      / \
    ///    9|3 20|4
    /// ```

    /// ### 2 依次用叶子数组元素调整败者树###
    /// ### &emsp; **while** 从后向前遍历叶子数组 :\n
    for (int leaf_index = K - 1; leaf_index >= 0; leaf_index--) {
        /// &emsp;&emsp; 使用当前叶子索引, 调用LoserTreeAdjust调整败者树\n
        LoserTreeAdjust(loser_tree, leaves, K, leaf_index);
        sorted_list_lengths[leaf_index]--;
    }

    /// &emsp; 建树结束:\n
    /// ```
    ///             2 ----- 0
    ///            / \
    ///           /   \
    ///          /     \
    ///         3       1
    ///        / \     / \
    ///       4 6|0 12|1 10|2
    ///      / \
    ///    9|3 20|4
    /// ```
}


/*!
 * <h1>K路合并</h1>
 * @param K_way_sorted_lists **K组待归并有序序列**
 * @param K **路数**
 * @param sorted_list_lengths **K组有序序列的长度**
 * @note
 */
void KWayMerge(int* K_way_sorted_lists[], int K, int* sorted_list_lengths) {

    /// ###1 初始化败者树叶子数组和非叶子数组###
    leaf_t* leaves = (leaf_t*)malloc(sizeof(leaf_t) * K);
    memset(leaves, 0, sizeof(leaf_t) * K);

    int* loser_tree = (int*)malloc(sizeof(int) * K);
    memset(loser_tree, 0, sizeof(int) * K);

    /// ###2 叶子数组读入各归并段首元素###
    /// &emsp; **for loop** 遍历K个输入归并段 : \n
    /// &emsp;&emsp; 该段当前第0个记录的关键字, 赋值到败者树叶子数组leaves[i].key
    for (int i = 0; i < K; ++i) {
        leaves[i].key = K_way_sorted_lists[i][0];
    }

    /// ### 3 构造败者树 ###
    CreateLoserTree(loser_tree, leaves, K, sorted_list_lengths);

    /// ### 4 构造各路的当前遍历索引的数组 ###
    /// &emsp; 初始化每个元素为1(构造败者树时, 各路的索引0元素已经进入败者树)
    int* traverse_index_per_sorted_list = (int*)malloc(sizeof(int) * K);
    for (int leaf_index = 0; leaf_index < K; leaf_index++) {
        traverse_index_per_sorted_list[leaf_index] = 1;
    }

    /// ### 5 使用败者树进行K路归并 ###
    /// &emsp; **while** 败者树根结点有值(根结点的key不为INT_MAX) :\n
    while (leaves[loser_tree[0]].key != INT_MAX) {
        /// &emsp;&emsp; 取根结点的值为胜者
        int winner_leaf_index = loser_tree[0];
        printf("%d  ", leaves[loser_tree[0]].key);

        /// &emsp;&emsp;&emsp; **if** 胜者的归并段还有元素 :\n
        /// &emsp;&emsp;&emsp;&emsp; 胜者的归并段的当前头元素, 赋值给胜者叶子结点
        if (traverse_index_per_sorted_list[winner_leaf_index] <= sorted_list_lengths[winner_leaf_index]) {
            leaves[winner_leaf_index].key =
                K_way_sorted_lists[winner_leaf_index][traverse_index_per_sorted_list[winner_leaf_index]];
            traverse_index_per_sorted_list[winner_leaf_index]++;
        } else {
            /// &emsp;&emsp;&emsp; **else** (胜者的归并段元素已经全部被归并)
            /// &emsp;&emsp;&emsp;&emsp; 胜者叶子结点的key设置为INT_MAX
            leaves[winner_leaf_index].key = INT_MAX;
        }

        /// &emsp;&emsp;&emsp; 使用胜者的叶子数组索引执行LoserTreeAdjust(调整败者树)\n
        LoserTreeAdjust(loser_tree, leaves, K, winner_leaf_index);
    }

    printf("\n");
}
