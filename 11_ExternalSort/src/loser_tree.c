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
 * @param index
 */
void LoserTreeAdjust(loser_tree_t loser_tree, leaves_t leaves, int index) {
    //沿从叶子结点b[s]到根结点ls[0]的路径调整败者树
    for (int parent = (index + SEQ_QUEUE_COUNT) / 2; parent > 0; parent = parent / 2) {
		if(leaves[index].key > leaves[loser_tree[parent]].key) {		//s指示新的胜利者（小为胜，向上比较，大为败，留在双亲结点）
            swap(&index, &loser_tree[parent]);
		}
	}

    loser_tree[0] = index;							//顶部结点为最小值
}


/*!
 * <h1>构造败者树</h1>
 * @param loser_tree
 * @param leaves
 * @note
 * 败者树数组构成非叶子结点, 其中loserTree[0]为根节点, 用来保存最小值
 */
void CreateLoserTree(loser_tree_t loser_tree, leaves_t leaves) {
    leaves[SEQ_QUEUE_COUNT].key = INT_MIN;                // 设INT_MIN为关键字可能的最小值
    for (int i = 0; i < SEQ_QUEUE_COUNT; ++i) {
        loser_tree[i] = SEQ_QUEUE_COUNT;                    // 设置loserTree中"败者"的初值
    }
    for (int i = SEQ_QUEUE_COUNT - 1; i >= 0; --i) {
        LoserTreeAdjust(loser_tree, leaves, i);  // 依次从leafArr[SEQ_QUEUE_COUNT - 1], leaves[SEQ_QUEUE_COUNT - 2] ... leaves[0]出发调整败者
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
void KWayMerge(loser_tree_t loser_tree, leaves_t leaves, int* K_way_sorted_lists[], int K, int limit_length) {
    // 利用败者树ls将编号从0到k - 1的k个输入归并段中的记录归并到输出归并段

    // 分别从k个输入归并段读入该段当前第一个记录的关键字到外结点
    for (int i = 0; i < K; ++i) {
        leaves[i].key = K_way_sorted_lists[i][0];
    }

    CreateLoserTree(loser_tree, leaves);
    int* everyQueueWorkingIdx = (int*)malloc(sizeof(int) * K);
    for (int i = 0; i < K; i++) {
        everyQueueWorkingIdx[i] = 1;
    }

    while (leaves[loser_tree[0]].key != INT_MAX) {
        int queue_idx = loser_tree[0];
        printf("%d  ", leaves[loser_tree[0]].key);

        if (everyQueueWorkingIdx[queue_idx] < limit_length) { // 如果queueIdx归并段, 还有元素, 赋值
            leaves[queue_idx].key = K_way_sorted_lists[queue_idx][everyQueueWorkingIdx[queue_idx]];
            everyQueueWorkingIdx[queue_idx]++;
        } else { // 如果已经全部执行完
            leaves[queue_idx].key = INT_MAX;
        }
        LoserTreeAdjust(loser_tree, leaves, queue_idx);
    }

    printf("\n");
}
