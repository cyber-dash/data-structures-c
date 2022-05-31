//
// Created by cyberdash@163.com on 2022/5/13.
//

#include "test.h"
#include "stdio.h"
#include "stdlib.h"


void TestInitSeq() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                    Test StaticSearchTable                   \n");
    printf("                       初始化静态查找表                        \n\n\n");

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}

void TestSearchSeq() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("               Test StaticSearchTable SeqSearch              \n");
    printf("                      测试静态查找表顺序查找                    \n\n\n");

    KeyType key_array[6] = { 1, 2, 4, 5, 7, 8};
    ValueType value_array[6] = { 0.9, 3.9, -0.3, 3.8, 4.5, 2.4};

    ElemType elem_array[6];
	int i;
    for (i = 0; i < 6; i++) {
        elem_array[i].key = key_array[i];
        elem_array[i].value = value_array[i];
    }

    SSTable* static_search_table = (SSTable*)malloc(sizeof(SSTable));
    Init_Seq(static_search_table, elem_array, sizeof(elem_array) / sizeof(ElemType));

    int key1 = 3;
    int key2 = 4;
    int pos1 = Search_Seq(static_search_table, key1);
    if (!pos1) {
        printf("key:%d 的位置: 没有此元素\n", key1);
    } else {
        printf("key:%d 的位置: %d", key1, pos1);
    }

    printf("\n");

    int pos2 = Search_Seq(static_search_table, key2);
    if (!pos2) {
        printf("key:%d 的位置: 没有此元素\n", key2);
    } else {
        printf("key:%d 的位置: %d", key2, pos2);
    }

    printf("\n");

    // Print_Seq(static_search_table);

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}

void TestSearchBin() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("               Test StaticSearchTable BinSearch              \n");
    printf("                      测试静态查找表二分查找                     \n\n\n");

    KeyType key_array[6] = { 1, 2, 4, 5, 7, 8};
    ValueType value_array[6] = { 0.9, 3.9, -0.3, 3.8, 4.5, 2.4};

    ElemType elem_array[6];
	int i;
    for (i = 0; i < 6; i++) {
        elem_array[i].key = key_array[i];
        elem_array[i].value = value_array[i];
    }

    SSTable* static_search_table = (SSTable*)malloc(sizeof(SSTable));
    Init_Seq(static_search_table, elem_array, sizeof(elem_array) / sizeof(ElemType));

    int key1 = 3;
    int key2 = 4;
    int pos1 = Search_Bin(static_search_table, key1);
    if (!pos1) {
        printf("key:%d 的位置: 没有此元素\n", key1);
    } else {
        printf("key:%d 的位置: %d", key1, pos1);
    }

    printf("\n");

    int pos2 = Search_Bin(static_search_table, key2);
    if (!pos2) {
        printf("key:%d 的位置: 没有此元素\n", key2);
    } else {
        printf("key:%d 的位置: %d", key2, pos2);
    }

    printf("\n");

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}
