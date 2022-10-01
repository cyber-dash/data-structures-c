/*!
 * @file seq_stack.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  栈 顺序栈
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_STACK_H
#define CYBER_DASH_STACK_H


#define STACK_INIT_CAPACITY 100   //!< 栈初始容量
#define STACK_INCREMENT 10        //!< 栈容量增量
#define STACK_ELEM int            //!< 栈结点类型

/*! @brief 函数返回值枚举 */
typedef enum Status {
    OK, //!< 正确
    NON_ALLOCATED,  //!< 内存分配失败
    NON_EXISTENT,   //!< 不存在
    OVERFLOW,       //!< 溢出
    ERROR           //!< 其他错误
} status_t;

/*! @brief 顺序栈 */
typedef struct {
    STACK_ELEM* elements;   //!< 栈元素数组
    STACK_ELEM* top;        //!< 栈顶指针
    int capacity;           //!< 容量
    int size;               //!< 栈当前长度
} seq_stack_t;

// 顺序栈初始化
status_t SeqStackInit(seq_stack_t* seq_stack); // 构造一个空栈S

// 顺序栈销毁
status_t SeqStackDestroy(seq_stack_t* seq_stack); // 销毁栈S, S不再存在

// 顺序栈清空
status_t SeqStackClear(seq_stack_t* seq_stack); // 把S置为空栈

// 顺序栈是否为空
status_t SeqStackIsEmpty(seq_stack_t seq_stack); // 若栈S为空栈, 则返回TRUE, 否则返回FALSE

// 顺序栈长度
int SeqStackSize(seq_stack_t seq_stack); // 返回S的元素个数, 即栈的长度

// 顺序栈取栈顶
status_t SeqStackTop(seq_stack_t seq_stack, STACK_ELEM* top_elem); //

// 顺序栈入栈
status_t SeqStackPush(seq_stack_t* seq_stack, STACK_ELEM elem);

// 顺序栈出栈
status_t SeqStackPop(seq_stack_t* seq_stack, STACK_ELEM *elem);

// 顺序栈打印
void SeqStackPrint(seq_stack_t *seq_stack);    // 打印队列


#endif // CYBER_DASH_STACK_H
