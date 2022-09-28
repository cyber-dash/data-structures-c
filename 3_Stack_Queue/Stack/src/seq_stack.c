/*!
 * @file seq_stack.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  栈 顺序栈
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdlib.h>
#include <stdio.h>
#include "seq_stack.h"


/*!
 * @brief **顺序栈初始化**
 * @param seq_stack 顺序栈(指针)
 * @return 执行结果
 * @note
 * 顺序栈初始化
 * ----------
 * ----------
 *
 * ----------
 *
 * top指向的地址并不存放栈元素, 是为了方便操作
 *
 * ----------
 * - 数组elements分配内存\n
 * &emsp; **if** 内存分配失败 :\n
 * &emsp;&emsp; 返回NON_ALLOCATED\n
 * - 栈属性初始化\n
 * &emsp; top指向elements数组首地址\n
 * &emsp; 设置栈容量\n
 * &emsp; 栈内元素数0个\n
 */
status_t SeqStackInit(seq_stack_t* seq_stack) {

    // 为elements分配内存
    seq_stack->elements = (STACK_ELEM*)malloc(STACK_INIT_CAPACITY * sizeof(STACK_ELEM));
    if (!seq_stack->elements) {  // if 内存分配失败
        return NON_ALLOCATED;   // 返回NON_ALLOCATED
    }

    seq_stack->top = seq_stack->elements;       // top指向数组首地址
    seq_stack->capacity = STACK_INIT_CAPACITY;  // 栈容量
    seq_stack->size = 0;                        // 栈内元素数0个

    return OK;
}


/*!
 * @brief **顺序栈取栈顶**
 * @param seq_stack 顺序栈
 * @param top_elem 栈顶元素的保存变量(指针)
 * @return 执行结果
 * @note
 * 顺序栈取栈顶
 * ----------
 * ----------
 *
 * ----------
 *
 * 读操作, 栈顶并不出栈
 *
 * ----------
 * - 判断栈空\n
 * &emsp; **if** 栈空 :\n
 * &emsp;&emsp; 返回NON_EXISTENT\n
 * - 赋值\n
 * &emsp; 将*(seq_stack.top - 1)赋给*top_elem\n
 */
status_t SeqStackTop(seq_stack_t seq_stack, STACK_ELEM* top_elem) {

    // ----- 判断栈空 -----
    if (seq_stack.top == seq_stack.elements) {  // if 栈空
        return NON_EXISTENT;    // 返回NON_EXISTENT
    }

    // ----- 赋值 -----
    *top_elem = *(seq_stack.top - 1);   // 将*(seq_stack.top - 1)赋给*top_elem

    return OK;
}


/*!
 * @brief **顺序栈入栈**
 * @param seq_stack 顺序栈(指针)
 * @param elem 入栈元素
 * @return 执行结果
 * @note
 * 顺序栈入栈
 * --------
 * --------
 *
 * --------
 * - 判断栈满\n
 * &emsp; **if** top - elements >= capacity :\n
 * &emsp;&emsp; elements重新分配内存\n
 * &emsp;&emsp; **if** 内存分配失败 :\n
 * &emsp;&emsp;&emsp; 返回NON_ALLOCATED\n
 * &emsp;&emsp; top指针重新指向最新的位置elements + capacity\n
 * &emsp;&emsp; capacity调整\n
 * - 栈属性调整\n
 * &emsp; 入栈元素赋给top指针指向的位置\n
 * &emsp; top指针向后移动一位\n
 * &emsp; 当前栈size增加1\n
 */
status_t SeqStackPush(seq_stack_t* seq_stack, STACK_ELEM elem) {
    // 栈满, 扩充elements数组, todo: 这里的>=包含两种边界条件, 需要增加case处理
    if (seq_stack->top - seq_stack->elements >= seq_stack->capacity) {
        seq_stack->elements = (STACK_ELEM*)realloc(seq_stack->elements,
                                                   (seq_stack->capacity + STACK_INCREMENT) * sizeof(STACK_ELEM));
        if (!seq_stack->elements) {
            return NON_ALLOCATED;
        }

        // top指针重新指向新位置
        seq_stack->top = seq_stack->elements + seq_stack->capacity;
        // capacity调整
        seq_stack->capacity += STACK_INCREMENT;
    }

    *seq_stack->top = elem; // 入栈元素赋给top指针指向的位置
    seq_stack->top++;       // top指针向后移动一位
    seq_stack->size++;      // 当前栈size增加1

    return OK;
}


/*!
 * @brief **顺序栈出栈**
 * @param seq_stack 顺序栈(指针)
 * @param elem 栈顶元素
 * @return 执行结果
 * @note
 * 顺序栈出栈
 * --------
 * --------
 *
 * --------
 * - 判断栈空\n
 * &emsp; **if** 栈空 :\n
 * &emsp;&emsp; 返回NON_EXISTENT\n
 * - 栈顶赋给elem\n
 * - 栈属性调整\n
 * &emsp; top指针向前挪1位(减1)\n
 * &emsp; size减1\n
 */
status_t SeqStackPop(seq_stack_t* seq_stack, STACK_ELEM* elem) {

    if (seq_stack->top == seq_stack->elements) {
        return NON_EXISTENT;
    }

    *elem = *seq_stack->top;

    seq_stack->top--;
    seq_stack->size--;

    return OK;
}


/*!
 * @brief **顺序栈销毁**
 * @param seq_stack 顺序栈
 * @return 执行结果
 * @note
 * 顺序栈销毁
 * ---------
 * ---------
 *
 * ---------
 * - free栈的elements\n
 * - free栈\n
 */
status_t SeqStackDestroy(seq_stack_t* seq_stack) {
    free(seq_stack->elements);
    free(seq_stack);

    return OK;
}


/*!
 * @brief **顺序栈清空**
 * @param seq_stack 顺序栈
 * @return 执行结果
 * @note
 * 顺序栈清空
 * ---------
 * ---------
 *
 * ---------
 * **while loop** 栈不为空 :\n
 * &emsp; Pop栈顶\n
 */
status_t SeqStackClear(seq_stack_t* seq_stack) {
    STACK_ELEM elem;
    while (SeqStackIsEmpty(*seq_stack) != OK) {
        SeqStackPop(seq_stack, &elem);
    }

    return OK;
}


/*!
 * @brief **顺序栈是否为空**
 * @param seq_stack 顺序栈
 * @return 执行结果
 * @note
 * 顺序栈是否为空
 * ------------
 * ------------
 *
 * ------------
 * **if** top等于elements :\n
 * &emsp; 返回OK\n
 * **else**\n
 * &emsp; 返回ERROR\n
 */
status_t SeqStackIsEmpty(seq_stack_t seq_stack) {
    if (seq_stack.top == seq_stack.elements) {
        return OK;
    }

    return ERROR;   // todo: ERROR用的不好
}


/*!
 * @brief **顺序栈长度**
 * @param seq_stack 顺序栈
 * @return 长度
 * @note
 * 顺序栈长度
 * ---------
 * ---------
 *
 * ---------
 * 返回 top - elements
 */
int SeqStackSize(seq_stack_t seq_stack) {
    return seq_stack.top - seq_stack.elements;
}


/*!
 * @brief **顺序栈打印**
 * @param seq_stack 顺序栈
 * @note
 * 顺序栈打印
 * ---------
 * ---------
 *
 * ---------
 * 遍历栈内元素, 打印
 */
void SeqStackPrint(seq_stack_t* seq_stack) {

    STACK_ELEM* cur = seq_stack->top;

    printf("打印栈, 从栈顶到栈底\n");

    while (cur - seq_stack->elements > 0) {
        printf("%d ", *(cur - 1));
        cur--;
    }

    printf("\n");
}
