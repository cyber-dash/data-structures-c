/*!
 * @file test.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 查找 测试用例
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "test.h"
#include "stdio.h"
#include "stdlib.h"


void TestStaticSearchTableSeqSearch() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("               Test StaticSearchTable SeqSearch              \n");
    printf("                      测试静态查找表顺序查找                    \n\n\n");

    KEY keys[6] = {1, 2, 4, 5, 7, 8};
    VALUE values[6] = {0.9, 3.9, -0.3, 3.8, 4.5, 2.4};

    elem_t elements[6];

    for (int i = 0; i < 6; i++) {
        elements[i].key = keys[i];
        elements[i].value = values[i];
    }

    static_search_table_t* static_search_table = (static_search_table_t*)malloc(sizeof(static_search_table_t));
    StaticSearchTableInit(static_search_table, elements, sizeof(elements) / sizeof(elem_t));

    StaticSearchTablePrint(static_search_table);

    int key1 = 3;
    int key2 = 4;

    int index1 = StaticSearchTableSeqSearch(static_search_table, key1);
    if (!index1) {
        printf("查找key/%d: 没有此元素\n", key1);
    } else {
        printf("查找key/%d: %d", key1, index1);
    }

    printf("\n");

    int index2 = StaticSearchTableBinarySearch(static_search_table, key2);
    if (!index2) {
        printf("查找key:%d: 没有此元素\n", key2);
    } else {
        printf("查找key:%d: %d", key2, index2);
    }

    printf("\n");

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}


void TestStaticSearchTableBinarySearch() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("              Test StaticSearchTable BinarySearch            \n");
    printf("                      测试静态查找表二分查找                    \n\n\n");

    KEY keys[6] = {1, 2, 4, 5, 7, 8};
    VALUE values[6] = {0.9, 3.9, -0.3, 3.8, 4.5, 2.4};

    elem_t elements[6];

    for (int i = 0; i < 6; i++) {
        elements[i].key = keys[i];
        elements[i].value = values[i];
    }

    static_search_table_t* static_search_table = (static_search_table_t*)malloc(sizeof(static_search_table_t));
    StaticSearchTableInit(static_search_table, elements, sizeof(elements) / sizeof(elem_t));

    StaticSearchTablePrint(static_search_table);

    int key1 = 3;
    int key2 = 4;

    int index1 = StaticSearchTableBinarySearch(static_search_table, key1);
    if (!index1) {
        printf("查找key/%d: 没有此元素\n", key1);
    } else {
        printf("查找key/%d: %d", key1, index1);
    }

    printf("\n");

    int index2 = StaticSearchTableBinarySearch(static_search_table, key2);
    if (!index2) {
        printf("查找key:%d: 没有此元素\n", key2);
    } else {
        printf("查找key:%d: %d", key2, index2);
    }

    printf("\n");

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}
