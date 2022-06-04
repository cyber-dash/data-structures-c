//
// Created by cyberdash@163.com on 2021/12/26.
//

#include <stdlib.h>
#include <stdio.h>
#include "test.h"


int compare(ELEM_TYPE a, ELEM_TYPE b) {
    if (a > b) {
        return 1;
    } else if (a == b) {
        return 0;
    } else {
        return -1;
    }
}


void TestSeqListInsert() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                       测试顺序表的插入                       |\n");

    seq_list_t* seq_list = (seq_list_t*)malloc(sizeof(seq_list_t));
    SeqListInit(seq_list);

    printf("初始化顺序表sqList完成\n\n");

    ELEM_TYPE elem1 = 1;
    ELEM_TYPE elem2 = 2;
    ELEM_TYPE elem3 = 3;

    printf("在位置1前边插入elem1: %d\n", elem1);
    SeqListInsert(seq_list, 1, elem1);
    printf("在位置2前边插入elem2: %d\n", elem2);
    SeqListInsert(seq_list, 2, elem2);
    printf("在位置3前边插入elem3: %d\n", elem3);
    SeqListInsert(seq_list, 3, elem3);

    printf("\n打印顺序表sqList:\n");
    SeqListPrint(seq_list);

    printf("\n-------------------------------------------------------------\n\n");
}


void TestSeqListDelete() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                       测试顺序表的删除                       |\n");

    seq_list_t* seq_list = (seq_list_t*)malloc(sizeof(seq_list_t));
    SeqListInit(seq_list);

    printf("初始化顺序表sqList完成\n\n");

    ELEM_TYPE elem1 = 1;
    ELEM_TYPE elem2 = 3;
    ELEM_TYPE elem3 = 5;

    printf("在位置1前边插入elem1: %d\n", elem1);
    SeqListInsert(seq_list, 1, elem1);
    printf("在位置2前边插入elem2: %d\n", elem2);
    SeqListInsert(seq_list, 2, elem2);
    printf("在位置3前边插入elem3: %d\n", elem3);
    SeqListInsert(seq_list, 3, elem3);

    printf("\n删除位置2的元素\n");
    ELEM_TYPE delete_item;
    SeqListDelete(seq_list, 2, &delete_item);
    printf("被删除的元素值: %d\n", delete_item);

    printf("\n打印顺序表sqList:\n");
    SeqListPrint(seq_list);

    printf("\n-------------------------------------------------------------\n\n");
}


void TestSeqListLocate() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                       测试顺序表的查找                      |\n");

    seq_list_t* seq_list = (seq_list_t*)malloc(sizeof(seq_list_t));
    SeqListInit(seq_list);

    printf("初始化顺序表sqList完成\n\n");

    ELEM_TYPE elem1 = 1;
    ELEM_TYPE elem2 = 3;
    ELEM_TYPE elem3 = 5;

    printf("在位置1前边插入elem1: %d\n", elem1);
    SeqListInsert(seq_list, 1, elem1);
    printf("在位置2前边插入elem2: %d\n", elem2);
    SeqListInsert(seq_list, 2, elem2);
    printf("在位置3前边插入elem3: %d\n", elem3);
    SeqListInsert(seq_list, 3, elem3);

    ELEM_TYPE elem0 = 4;
    int pos0 = SeqListLocate(seq_list, elem0, compare); // 查找elem0的位置
    int pos1 = SeqListLocate(seq_list, elem1, compare); // 查找elem1的位置

    printf("\n");

    printf("elem0:%d在顺序表中的位置:%d\n", elem0, pos0);   // 位置0表示没有该元素
    printf("elem1:%d在顺序表中的位置:%d\n", elem1, pos1);

    printf("\n-------------------------------------------------------------\n\n");
}


void TestSeqListMerge() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                       测试顺序表的合并                       |\n");

    ELEM_TYPE elements[6] = { 1, 2, 3, 4, 5, 6 };

    seq_list_t* seq_list_a = (seq_list_t*)malloc(sizeof(seq_list_t));
    SeqListInit(seq_list_a);
    seq_list_t* seq_list_b = (seq_list_t*)malloc(sizeof(seq_list_t));
    SeqListInit(seq_list_b);

    // 顺序表a插入3个元素
    SeqListInsert(seq_list_a, 1, elements[0]);
    SeqListInsert(seq_list_a, 2, elements[2]);
    SeqListInsert(seq_list_a, 3, elements[4]);
    // 顺序表b插入3个元素
    SeqListInsert(seq_list_b, 1, elements[1]);
    SeqListInsert(seq_list_b, 2, elements[3]);
    SeqListInsert(seq_list_b, 3, elements[5]);

    printf("顺序表a: ");
    SeqListPrint(seq_list_a);
    printf("\n");
    printf("顺序表b: ");
    SeqListPrint(seq_list_a);
    printf("\n");

    seq_list_t* merged_list = (seq_list_t*)malloc(sizeof(seq_list_t));
    SeqListInit(merged_list);

    SeqListMerge(seq_list_a, seq_list_b, merged_list);

    printf("合并后的顺序表merged: list: \n");
    SeqListPrint(merged_list);

    printf("\n-------------------------------------------------------------\n\n");
}
