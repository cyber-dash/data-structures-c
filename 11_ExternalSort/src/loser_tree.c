/*!
 * @file loser_tree_t.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 外部排序败者树源文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */
#include "loser_tree.h"
#include "limits.h"
#include "stdio.h"


void Adjust(loser_tree_t loser_tree, leaves_t leaves, int idx)
{
	int parent, tmp;
	
	parent = (idx + SIZE) / 2;						//ls[t]是b[s]的双亲结点
	
	while(parent>0)							//沿从叶子结点b[s]到根结点ls[0]的路径调整败者树 
	{
		if(leaves[idx].key > leaves[loser_tree[parent]].key)		//s指示新的胜利者（小为胜，向上比较，大为败，留在双亲结点）
		{
			tmp = idx;
			idx = loser_tree[parent];
            loser_tree[parent] = tmp;
		}
		
		parent = parent/2;
	}

    loser_tree[0] = idx;							//顶部结点为最小值
}

/*!
 * 构造败者树
 * @param loserTree
 * @param leafArr
 * @note
 * 败者树数组构成非叶子结点, 其中loserTree[0]为根节点, 用来保存最小值
 */
void CreateLoserTree(loser_tree_t loserTree, leaves_t leafArr) {
    leafArr[SIZE].key = INT_MIN;                // 设INT_MIN为关键字可能的最小值
    for (int i = 0; i < SIZE; ++i) {
        loserTree[i] = SIZE;                    // 设置loserTree中"败者"的初值
    }
    for (int i = SIZE - 1; i >= 0; --i) {
        Adjust(loserTree, leafArr, i);  // 依次从leafArr[SIZE - 1], leafArr[SIZE - 2] ... leafArr[0]出发调整败者
    }
} // CreateLoserTree


void K_Merge(loser_tree_t loser_tree, leaves_t leafArr, int* array[], int limit_length) {
    // 利用败者树ls将编号从0到k - 1的k个输入归并段中的记录归并到输出归并段

    // 分别从k个输入归并段读入该段当前第一个记录的关键字到外结点
    for (int i = 0; i < SIZE; ++i) {
        //leafArr[i].key = *((int*)array + i);
        leafArr[i].key = array[i][0];
    }

    CreateLoserTree(loser_tree, leafArr);
    int everyQueueWorkingIdx[SIZE] = {1, 1, 1, 1, 1};

    while (leafArr[loser_tree[0]].key != INT_MAX) {
        int queueIdx = loser_tree[0];
        printf("%d  ", leafArr[loser_tree[0]].key);

        if (everyQueueWorkingIdx[queueIdx] < limit_length) { // 如果queueIdx归并段, 还有元素, 赋值
            leafArr[queueIdx].key = array[queueIdx][everyQueueWorkingIdx[queueIdx]];
            everyQueueWorkingIdx[queueIdx]++;
        } else { // 如果已经全部执行完
            leafArr[queueIdx].key = INT_MAX;
        }
        Adjust(loser_tree, leafArr, queueIdx);
    }

    printf("\n");
}
