//
// Created by cyberdash@163.com on 2021/12/30.
//

#include "test.h"
#include "seq_stack.h"
#include "stdlib.h"
#include "stdio.h"


void TestStackInsert() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                        Test Insert                        |\n");
    printf("|                          测试栈插入                         |\n");

    seq_stack_t *sqStack = (seq_stack_t*)malloc(sizeof(seq_stack_t));
    Status res = SeqStackInit(sqStack);
    if (res != OK) {
        printf("初始化栈失败");
    }

    SeqStackPush(sqStack, 1);
    SeqStackPush(sqStack, 2);
    SeqStackPush(sqStack, 3);
    SeqStackPush(sqStack, 4);
    SeqStackPush(sqStack, 5);

    SeqStackPrint(sqStack);

    printf("|-----------------------------------------------------------|\n\n");
}


void TestClearStack() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                      Test SeqStackClear                      |\n");
    printf("|                          测试清除栈                         |\n");

    seq_stack_t sqStack;
    Status res = SeqStackInit(&sqStack);
    if (res != OK) {
        printf("初始化栈失败");
    }

    SeqStackPush(&sqStack, 1);
    SeqStackPush(&sqStack, 2);
    SeqStackPush(&sqStack, 3);
    SeqStackPush(&sqStack, 4);
    SeqStackPush(&sqStack, 5);

    res = SeqStackClear(&sqStack);
    if (res == OK) {
        if (SeqStackIsEmpty(sqStack) == OK) {
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

    seq_stack_t sqStack;
    Status res = SeqStackInit(&sqStack);
    if (res != OK) {
        printf("初始化栈失败");
    }

    SeqStackPush(&sqStack, 1);
    SeqStackPush(&sqStack, 2);
    SeqStackPush(&sqStack, 3);
    SeqStackPush(&sqStack, 4);
    SeqStackPush(&sqStack, 5);

    printf("栈长度: %d\n", SeqStackSize(sqStack));

    printf("|-----------------------------------------------------------|\n\n");
}


void TestGetTop() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                        Test SeqStackTop                        |\n");
    printf("|                         测试获取栈顶                        |\n");

    seq_stack_t sqStack;
    Status res = SeqStackInit(&sqStack);
    if (res != OK) {
        printf("初始化栈失败");
    }

    STACK_ELEM top;

    SeqStackPush(&sqStack, 1);
    SeqStackPush(&sqStack, 2);
    SeqStackPush(&sqStack, 3);
    SeqStackPush(&sqStack, 4);
    SeqStackPush(&sqStack, 5);

    SeqStackTop(sqStack, &top);

    printf("栈顶: %d\n", top);

    printf("|-----------------------------------------------------------|\n\n");
}
