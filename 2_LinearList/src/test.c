//
// Created by cyberdash@163.com on 2021/12/26.
//

#include <stdlib.h>
#include <stdio.h>
#include "test.h"

int compare(ELEM_TYPE a, ELEM_TYPE b) {
    if (a > b) {
        return 1;
    }
    else if (a == b) {
        return 0;
    }
    else {
        return -1;
    }
}

void test_ListInsert_Sq() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                       测试线性表的插入                       |\n");

    seq_list_t* sqList = (seq_list_t*)malloc(sizeof(seq_list_t));
    SeqListInit(sqList);

    printf("初始化线性表sqList完成\n\n");

    ELEM_TYPE e1 = 1;
    ELEM_TYPE e2 = 2;
    ELEM_TYPE e3 = 3;

    printf("在位置1前边插入e1: %d\n", e1);
    SeqListInsert(sqList, 1, e1);
    printf("在位置2前边插入e2: %d\n", e2);
    SeqListInsert(sqList, 2, e2);
    printf("在位置3前边插入e3: %d\n", e3);
    SeqListInsert(sqList, 3, e3);

    printf("\n打印线性表sqList:\n");
    SeqListPrint(sqList);

    printf("\n-------------------------------------------------------------\n\n");
}


void test_ListDelete_Sq() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                       测试线性表的删除                       |\n");

    seq_list_t* sqList = (seq_list_t*)malloc(sizeof(seq_list_t));
    SeqListInit(sqList);

    printf("初始化线性表sqList完成\n\n");

    ELEM_TYPE e1 = 1;
    ELEM_TYPE e2 = 3;
    ELEM_TYPE e3 = 5;

    printf("在位置1前边插入e1: %d\n", e1);
    SeqListInsert(sqList, 1, e1);
    printf("在位置2前边插入e2: %d\n", e2);
    SeqListInsert(sqList, 2, e2);
    printf("在位置3前边插入e3: %d\n", e3);
    SeqListInsert(sqList, 3, e3);

    printf("\n删除位置2的元素\n");
    ELEM_TYPE delete_item;
    SeqListDelete(sqList, 2, &delete_item);
    printf("被删除的元素值: %d\n", delete_item);

    printf("\n打印线性表sqList:\n");
    SeqListPrint(sqList);

    printf("\n-------------------------------------------------------------\n\n");
}


void test_LocateElem_Sq() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                       测试线性表的定位                       |\n");

    seq_list_t* sqList = (seq_list_t*)malloc(sizeof(seq_list_t));
    SeqListInit(sqList);

    printf("初始化线性表sqList完成\n\n");

    ELEM_TYPE e1 = 1;
    ELEM_TYPE e2 = 3;
    ELEM_TYPE e3 = 5;

    printf("在位置1前边插入e1: %d\n", e1);
    SeqListInsert(sqList, 1, e1);
    printf("在位置2前边插入e2: %d\n", e2);
    SeqListInsert(sqList, 2, e2);
    printf("在位置3前边插入e3: %d\n", e3);
    SeqListInsert(sqList, 3, e3);

    ELEM_TYPE e0 = 4;
    int pos0 = SeqListLocate(sqList, e0, compare);
    int pos1 = SeqListLocate(sqList, e1, compare);
    printf("e0:%d在线性表中的位置:%d\n", e0, pos0);
    printf("e1:%d在线性表中的位置:%d\n", e1, pos1);

    printf("\n-------------------------------------------------------------\n\n");
}
