//
// Created by cyberdash@163.com on 2021/12/30.
//

#ifndef CYBER_DASH_STACK_H
#define CYBER_DASH_STACK_H

#define STACK_INIT_SIZE 100 // 存储空间初始分配量
#define STACKINCREMENT  10  // 存储空间分配增量

#define SElemType int
typedef enum Status { OK, ERROR, OVERFLOW } Status;

typedef struct {
    SElemType   *base;  // 在栈构造之前和销毁之后, base的值为null
    SElemType   *top;   // 栈顶指针
    int stacksize;      // 当前已分配的存储空间, 以元素为单位
}SqStack;

//-----基本操作的函数原型说明-----
Status InitStack(SqStack *S); // 构造一个空栈S
Status DestroyStack(SqStack *S); // 销毁栈S, S不再存在
Status ClearStack(SqStack *S); // 把S置为空栈
Status StackEmpty(SqStack S); // 若栈S为空栈, 则返回TRUE, 否则返回FALSE
int StackLength(SqStack S); // 返回S的元素个数, 即栈的长度
Status GetTop(SqStack S, SElemType *e); //
Status Push(SqStack *S, SElemType e);
Status Pop(SqStack *S, SElemType *e);
void PrintStack(SqStack *S);    // 打印队列


#endif // CYBER_DASH_STACK_H
