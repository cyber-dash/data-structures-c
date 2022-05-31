//
// Created by cyberdash@163.com on 2021/12/30.
//

#include "test.h"
#include "stack.h"
#include "stdlib.h"
#include "stdio.h"


void TestStackInsert() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                        Test Insert                        |\n");
    printf("|                          测试栈插入                         |\n");

    SqStack *sqStack = (SqStack*)malloc(sizeof(SqStack));
    Status res = InitStack(sqStack);
    if (res != OK) {
        printf("初始化栈失败");
    }

    Push(sqStack, 1);
    Push(sqStack, 2);
    Push(sqStack, 3);
    Push(sqStack, 4);
    Push(sqStack, 5);

    PrintStack(sqStack);

    printf("|-----------------------------------------------------------|\n\n");
}


void TestClearStack() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                      Test ClearStack                      |\n");
    printf("|                          测试清除栈                         |\n");

    SqStack sqStack;
    Status res = InitStack(&sqStack);
    if (res != OK) {
        printf("初始化栈失败");
    }

    Push(&sqStack, 1);
    Push(&sqStack, 2);
    Push(&sqStack, 3);
    Push(&sqStack, 4);
    Push(&sqStack, 5);

    res = ClearStack(&sqStack);
    if (res == OK) {
        if (StackEmpty(sqStack) == OK) {
            printf("清除栈成功\n");
        }
    }

    printf("|-----------------------------------------------------------|\n\n");
}


void TestStackLength() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                        Test Length                        |\n");
    printf("|                          测试栈长度                         |\n");

    SqStack sqStack;
    Status res = InitStack(&sqStack);
    if (res != OK) {
        printf("初始化栈失败");
    }

    Push(&sqStack, 1);
    Push(&sqStack, 2);
    Push(&sqStack, 3);
    Push(&sqStack, 4);
    Push(&sqStack, 5);

    printf("栈长度: %d\n", StackLength(sqStack));

    printf("|-----------------------------------------------------------|\n\n");
}


void TestGetTop() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                        Test GetTop                        |\n");
    printf("|                         测试获取栈顶                        |\n");

    SqStack sqStack;
    Status res = InitStack(&sqStack);
    if (res != OK) {
        printf("初始化栈失败");
    }

    SElemType top;

    Push(&sqStack, 1);
    Push(&sqStack, 2);
    Push(&sqStack, 3);
    Push(&sqStack, 4);
    Push(&sqStack, 5);

    GetTop(sqStack, &top);

    printf("栈顶: %d\n", top);

    printf("|-----------------------------------------------------------|\n\n");
}
