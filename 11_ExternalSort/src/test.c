/*!
 * @file test.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 外部排序 败者树 测试用例
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "test.h"
#include "stdio.h"
#include "loser_tree.h"


/*!
 * @brief 测试败者树K路归并排序
 */
void TestLoserTree() {
    printf("\n");
    printf("|------------------------- CyberDash -------------------------|\n");
    printf("|                      Test loser_tree_t Sort                 |\n");
    printf("|                         测试败者树排序                        |\n\n\n");

    /// 5路归并\n
    /// ```
    /// 第0路: 6,  15, 25
    /// 第1路: 12, 37, 48
    /// 第2路: 10, 15, 16
    /// 第3路: 9,  18, 20
    /// 第4路: 20, 22, 40
    /// ```

    int arr0[] = { 6, 15, 25 };
    int arr1[] = { 12, 37, 48 };
    int arr2[] = { 10, 15, 16 };
    int arr3[] = { 9, 18, 20 };
    int arr4[] = { 20, 22, 40 };
    int* array[] = { arr0, arr1, arr2, arr3, arr4 };

    loser_tree_t loserTree;
    leaves_t leafArr;

    KWayMerge(loserTree, leafArr, array, 5, 3);

    printf("|-------------------------------------------------------------|\n");
}
