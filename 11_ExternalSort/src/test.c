/*!
 * @file test.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 外部排序败者树测试源文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdio.h>
#include "test.h"
#include "loser_tree.h"


/*!
 * @brief 测试败者树K路归并排序
 */
void TestLoserTree() {
    printf("\n");
    printf("|------------------------- CyberDash -------------------------|\n");
    printf("|                     Test LoserTree Sort                     |\n");
    printf("|                         测试败者树排序                        |\n\n\n");

    /// 5路归并\n
    int arr0[] = { 6, 15, 16, 17, 18, 19, 20, 70, 71, 72, 73, 74, 75, 76, 77, 78 };
    int arr1[] = { 12, 13, 14, 16, 16, 26, 26, 26, 36, 36, 36, 55, 55, 55, 55, 81, 81, 81 };
    int arr2[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    int arr3[] = { 9, 18, 27, 36, 45, 54, 63, 72, 81, 90, 99 };
    int arr4[] = { 20, 24, 28, 46, 52, 64 };

    int* array[] = { arr0, arr1, arr2, arr3, arr4 };
    int sorted_list_lengths[] = { sizeof(arr0)/sizeof(int), sizeof(arr1)/sizeof(int),
                                  sizeof(arr2)/sizeof(int), sizeof(arr3)/sizeof(int),
                                  sizeof(arr4)/sizeof(int) };

    KWayMerge(array, sizeof(array) / sizeof(int*), sorted_list_lengths);

    printf("|-------------------------------------------------------------|\n");
}
