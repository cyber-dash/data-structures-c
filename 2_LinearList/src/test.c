//
// Created by cyberdash@163.com on 2021/12/26.
//

#include <stdlib.h>
#include <stdio.h>
#include "test.h"

int compare(ElemType a, ElemType b) {
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

    SqList* sqList = (SqList*)malloc(sizeof(SqList));
    InitList_Sq(sqList);

    printf("初始化线性表sqList完成\n\n");

    ElemType e1 = 1;
    ElemType e2 = 2;
    ElemType e3 = 3;

    printf("在位置1前边插入e1: %d\n", e1);
    ListInsert_Sq(sqList, 1, e1);
    printf("在位置2前边插入e2: %d\n", e2);
    ListInsert_Sq(sqList, 2, e2);
    printf("在位置3前边插入e3: %d\n", e3);
    ListInsert_Sq(sqList, 3, e3);

    printf("\n打印线性表sqList:\n");
    PrintList_Sq(sqList);

    printf("\n-------------------------------------------------------------\n\n");
}


void test_ListDelete_Sq() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                       测试线性表的删除                       |\n");

    SqList* sqList = (SqList*)malloc(sizeof(SqList));
    InitList_Sq(sqList);

    printf("初始化线性表sqList完成\n\n");

    ElemType e1 = 1;
    ElemType e2 = 3;
    ElemType e3 = 5;

    printf("在位置1前边插入e1: %d\n", e1);
    ListInsert_Sq(sqList, 1, e1);
    printf("在位置2前边插入e2: %d\n", e2);
    ListInsert_Sq(sqList, 2, e2);
    printf("在位置3前边插入e3: %d\n", e3);
    ListInsert_Sq(sqList, 3, e3);

    printf("\n删除位置2的元素\n");
    ElemType delete_item;
    ListDelete_Sq(sqList, 2, &delete_item);
    printf("被删除的元素值: %d\n", delete_item);

    printf("\n打印线性表sqList:\n");
    PrintList_Sq(sqList);

    printf("\n-------------------------------------------------------------\n\n");
}


void test_LocateElem_Sq() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                       测试线性表的定位                       |\n");

    SqList* sqList = (SqList*)malloc(sizeof(SqList));
    InitList_Sq(sqList);

    printf("初始化线性表sqList完成\n\n");

    ElemType e1 = 1;
    ElemType e2 = 3;
    ElemType e3 = 5;

    printf("在位置1前边插入e1: %d\n", e1);
    ListInsert_Sq(sqList, 1, e1);
    printf("在位置2前边插入e2: %d\n", e2);
    ListInsert_Sq(sqList, 2, e2);
    printf("在位置3前边插入e3: %d\n", e3);
    ListInsert_Sq(sqList, 3, e3);

    ElemType e0 = 4;
    int pos0 = LocateElem_Sq(sqList, e0, compare);
    int pos1 = LocateElem_Sq(sqList, e1, compare);
    printf("e0:%d在线性表中的位置:%d\n", e0, pos0);
    printf("e1:%d在线性表中的位置:%d\n", e1, pos1);

    printf("\n-------------------------------------------------------------\n\n");
}
