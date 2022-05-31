//
// Created by cyberdash@163.com on 2022/4/6.
//

#include "test.h"
#include "stdio.h"
#include "LoserTree.h"


void TestLoserTree() {
    printf("\n");
    printf("|------------------------- CyberDash -------------------------|\n");
    printf("|                      Test LoserTree Sort                    |\n");
    printf("|                         测试败者树排序                        |\n\n\n");


    // int array[4][5] = {
    //     10, 9,  20, 6,  12,
    //     60, 50, 30, 44, 80,
    //     90, 11, 8,  44, 49,
    //     79, 3,  9,  14, 13,
    // };
    // int array[3][5] = {
    //     6,12,10,9,20,
    //     15,37,15,18,22,
    //     25,48,16,20,40
    // };

    int arr0[] = { 6, 15, 25 };
    int arr1[] = { 12, 37, 48 };
    int arr2[] = { 10, 15, 16 };
    int arr3[] = { 9, 18, 20 };
    int arr4[] = { 20, 22, 40 };
    int* array[] = { arr0, arr1, arr2, arr3, arr4 };

    LoserTree loserTree;
    LeafArr leafArr;

    K_Merge(loserTree, leafArr, array, 3);

    printf("|-------------------------------------------------------------|\n");
}
