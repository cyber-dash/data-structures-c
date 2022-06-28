//
// Created by cyberdash@163.com on 2021/12/30.
//

#ifndef CYBER_DASH_STACK_H
#define CYBER_DASH_STACK_H

#define STACK_INIT_CAPACITY 100 // 存储空间初始分配量
#define STACK_INCREMENT 10  // 存储空间分配增量
#define STACK_ELEM int

typedef enum Status {
    OK,
    NON_ALLOCATED,
    NON_EXISTENT,
    ERROR,
    OVERFLOW
} Status;

typedef struct {
    STACK_ELEM* elements;   //!< 在栈构造之前和销毁之后, base的值为null
    STACK_ELEM* top;        //!< 栈顶指针, 当栈内有元素时指向栈顶元素的下一个地址, 当栈内没有元素时指向elements数组首地址
    int capacity;           //!< 栈容量
    int size;               //!< 栈当前元素数
}seq_stack_t;

//-----基本操作的函数原型说明-----
Status SeqStackInit(seq_stack_t* seq_stack); // 构造一个空栈S
Status SeqStackDestroy(seq_stack_t* seq_stack); // 销毁栈S, S不再存在
Status SeqStackClear(seq_stack_t* seq_stack); // 把S置为空栈
Status SeqStackIsEmpty(seq_stack_t seq_stack); // 若栈S为空栈, 则返回TRUE, 否则返回FALSE
int SeqStackSize(seq_stack_t seq_stack); // 返回S的元素个数, 即栈的长度
Status SeqStackTop(seq_stack_t sea_stack, STACK_ELEM* top_elem); //
Status SeqStackPush(seq_stack_t* seq_stack, STACK_ELEM elem);
Status SeqStackPop(seq_stack_t* seq_stack, STACK_ELEM *elem);
void SeqStackPrint(seq_stack_t *seq_stack);    // 打印队列


#endif // CYBER_DASH_STACK_H
