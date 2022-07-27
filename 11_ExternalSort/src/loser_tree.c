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
#include "loser_tree.h"
#include "limits.h"


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
 * @param leaf_index
 * @note
 */
void LoserTreeAdjust(loser_tree_t loser_tree, leaves_t leaves, int K, int leaf_index) {
    //沿从叶子结点b[s]到根结点ls[0]的路径调整败者树

    /// ###1 从索引leaf_index叶子节点到根节点的路径调整败者树###
    /// &emsp; **for loop* 索引leaf_index的所有祖先节点 :\n
    for (int cur_ancestor_index = (leaf_index + K) / 2;
         cur_ancestor_index > 0;
         cur_ancestor_index = cur_ancestor_index / 2)
    {
        /// &emsp;&emsp; **if** 索引leaf_index的叶子节点的key > 索引loser_tree[cur_ancestor_index]的叶子节点的key
		if(leaves[leaf_index].key > leaves[loser_tree[cur_ancestor_index]].key) {		//s指示新的胜利者（小为胜，向上比较，大为败，留在双亲结点）
            swap(&leaf_index, &loser_tree[cur_ancestor_index]);
		}
	}

    loser_tree[0] = leaf_index;							//顶部结点为最小值
}


/*!
 * <h1>构造败者树</h1>
 * @param loser_tree **败者树非叶子节点数组**
 * @param leaves **败者树叶子节点数组**
 * @param K **多少路**
 * @note
 * loser_tree构成非叶子结点, 其中loser_tree[0]为根节点, 用来保存最小值
 */
void CreateLoserTree(loser_tree_t loser_tree, leaves_t leaves, int K) {
    leaves[K].key = INT_MIN;// 设INT_MIN为关键字可能的最小值

    /// ###1 设置败者树非叶子节点数组各元素初值(都设为K)###
    /// &emsp; **for loop** 遍历loser_tree :\n
    /// &emsp;&emsp; loser_tree[i] <= K\n
    /// &emsp; (叶子数组的索引范围是[0 ... K], 此时把所有非叶子元素的值都设为K, 不在叶子数组的索引范围内)\n
    for (int i = 0; i < K; ++i) {
        loser_tree[i] = K;                    // 设置loserTree中"败者"的初值
    }

    for (int leaf_index = K - 1; leaf_index >= 0; leaf_index--) {
        // 依次从loser_tree[K - 1], loser_tree[K - 2] ... leaves[0]出发调整败者
        LoserTreeAdjust(loser_tree, leaves, K, leaf_index);
    }
}


/*!
 * <h1>K路合并</h1>
 * @param loser_tree **败者树数组**
 * @param leaves **叶子数组**
 * @param K_way_sorted_lists **K组待排序数组**
 * @param limit_length **有序数组的最大长度**
 * @note
 */
void KWayMerge(int* loser_tree, leaves_t leaves, int* K_way_sorted_lists[], int K, int limit_length) {
    // 将编号0到K - 1的K个输入归并段中的记录, 归并到输出归并段

    /// ###1 读入各归并段首元素###
    /// &emsp; **for loop** 遍历K个输入归并段 : \n
    /// &emsp;&emsp; 该段当前第0个记录的关键字, 赋值到败者树叶子数组leaves[i].key
    for (int i = 0; i < K; ++i) {
        leaves[i].key = K_way_sorted_lists[i][0];
    }

    /// ###2 构造败者树###
    CreateLoserTree(loser_tree, leaves, K);

    int* traverse_index_per_sorted_list = (int*)malloc(sizeof(int) * K);
    for (int leaf_index = 0; leaf_index < K; leaf_index++) {
        traverse_index_per_sorted_list[leaf_index] = 1;
    }

    while (leaves[loser_tree[0]].key != INT_MAX) {
        int min_item_leaf_index = loser_tree[0];
        printf("%d  ", leaves[loser_tree[0]].key);

        if (traverse_index_per_sorted_list[min_item_leaf_index] < limit_length) { // 如果queueIdx归并段, 还有元素, 赋值
            leaves[min_item_leaf_index].key =
                K_way_sorted_lists[min_item_leaf_index][traverse_index_per_sorted_list[min_item_leaf_index]];
            traverse_index_per_sorted_list[min_item_leaf_index]++;
        } else { // 如果已经全部执行完
            leaves[min_item_leaf_index].key = INT_MAX;
        }
        LoserTreeAdjust(loser_tree, leaves, K, min_item_leaf_index);
    }

    printf("\n");
}
