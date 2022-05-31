//
// Created by cyberdash@163.com on 2021/12/30.
//

#include "stack.h"
#include "stdlib.h"
#include "stdio.h"


Status InitStack(SqStack *S) {
    // 构造一个空栈S
    S->base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if (!S->base) exit(OVERFLOW);   // 存储分配失败
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;

    return OK;
}


Status GetTop(SqStack S, SElemType *e) {
    // 若栈不空, 则用e返回S的栈顶元素, 并返回OK; 否则返回ERROR
    if (S.top == S.base) return ERROR;
    *e = *(S.top - 1);
    return OK;
} // GetTop


Status Push(SqStack *S, SElemType e) {
    // 插入元素e为新的栈顶元素
    if (S->top - S->base >= S->stacksize) { // 栈满, 追加存储空间
        S->base = (SElemType*)realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
        if (!S->base) exit(OVERFLOW);   // 存储分配失败

        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    *S->top++ = e;
    return OK;
} // Push


Status Pop(SqStack *S, SElemType *e) {
    // 若栈不空, 则删除S的栈顶元素, 用e返回其值, 并返回OK; 否则返回ERROR
    if (S->top == S->base) return ERROR;
    *e = *--S->top;
    return OK;
} // Pop


// 销毁栈S, S不再存在
Status DestroyStack(SqStack *S) {
    free(S->base);
    free(S);

    return OK;
}


// 把S置为空栈
Status ClearStack(SqStack *S) {
    SElemType e;
    while (StackEmpty(*S) != OK) {
        Pop(S, &e);
    }

    return OK;
}


// 若栈S为空栈, 则返回TRUE, 否则返回FALSE
Status StackEmpty(SqStack S) {
    if (S.top == S.base) {
        return OK;
    }

    return ERROR;
}


// 返回S的元素个数, 即栈的长度
int StackLength(SqStack S) {
    return S.top - S.base;
}
