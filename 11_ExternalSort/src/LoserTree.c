/*!
 * @file loserTree.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 外部排序 败者树
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */
#include "LoserTree.h"
#include "limits.h"
#include "stdio.h"


void Adjust(LoserTree loserTree, LeafArr leafArr, int idx)
{
	int parent, tmp;
	
	parent = (idx+k)/2;						//ls[t]是b[s]的双亲结点 
	
	while(parent>0)							//沿从叶子结点b[s]到根结点ls[0]的路径调整败者树 
	{
		if(leafArr[idx].key>leafArr[loserTree[parent]].key)		//s指示新的胜利者（小为胜，向上比较，大为败，留在双亲结点） 
		{
			tmp = idx;
			idx = loserTree[parent];
			loserTree[parent] = tmp;
		}
		
		parent = parent/2;
	}
	
	loserTree[0] = idx;							//顶部结点为最小值 
}

/*!
 * 构造败者树
 * @param loserTree
 * @param leafArr
 * @note
 * 败者树数组构成非叶子结点, 其中loserTree[0]为根节点, 用来保存最小值
 */
void CreateLoserTree(LoserTree loserTree, LeafArr leafArr) {
    leafArr[k].key = INT_MIN;                // 设INT_MIN为关键字可能的最小值
    for (int i = 0; i < k; ++i) {
        loserTree[i] = k;                    // 设置loserTree中"败者"的初值
    }
    for (int i = k - 1; i >= 0; --i) {
        Adjust(loserTree, leafArr, i);  // 依次从leafArr[k - 1], leafArr[k - 2] ... leafArr[0]出发调整败者
    }
} // CreateLoserTree


void K_Merge(LoserTree loserTree, LeafArr leafArr, int* array[], int limitLen) {
    // 利用败者树ls将编号从0到k - 1的k个输入归并段中的记录归并到输出归并段

    // 分别从k个输入归并段读入该段当前第一个记录的关键字到外结点
    for (int i = 0; i < k; ++i) {
        //leafArr[i].key = *((int*)array + i);
        leafArr[i].key = array[i][0];
    }

    CreateLoserTree(loserTree, leafArr);
    int everyQueueWorkingIdx[k] = {1, 1, 1, 1, 1};

    while (leafArr[loserTree[0]].key != INT_MAX) {
        int queueIdx = loserTree[0];
        printf("%d  ", leafArr[loserTree[0]].key);

        if (everyQueueWorkingIdx[queueIdx] < limitLen) { // 如果queueIdx归并段, 还有元素, 赋值
            leafArr[queueIdx].key = array[queueIdx][everyQueueWorkingIdx[queueIdx]];
            everyQueueWorkingIdx[queueIdx]++;
        } else { // 如果已经全部执行完
            leafArr[queueIdx].key = INT_MAX;
        }
        Adjust(loserTree, leafArr, queueIdx);
    }

    printf("\n");
}
