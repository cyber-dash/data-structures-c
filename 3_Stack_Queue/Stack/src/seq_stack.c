/*!
 * @file seq_stack.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  栈 顺序栈
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "seq_stack.h"
#include "stdlib.h"
#include "stdio.h"


/*!
 * @brief **顺序栈初始化**
 * @param seq_stack **顺序栈**(指针)
 * @return **执行结果**
 * @note
 */
status_t SeqStackInit(seq_stack_t* seq_stack) {

    // 为elements分配内存
    seq_stack->elements = (STACK_ELEM*)malloc(STACK_INIT_CAPACITY * sizeof(STACK_ELEM));
    if (!seq_stack->elements){
        return NON_ALLOCATED;   // 存储分配失败
    }

    seq_stack->top = seq_stack->elements;       // top指向数组首地址
    seq_stack->capacity = STACK_INIT_CAPACITY;  // 栈容量
    seq_stack->size = 0;                        // 栈内元素数0个

    return OK;
}


/*!
 * @brief **顺序栈取栈顶**
 * @param sea_stack **顺序栈**
 * @param top_elem **栈顶元素的保存变量**(指针)
 * @return **执行结果**
 * @note
 */
status_t SeqStackTop(seq_stack_t sea_stack, STACK_ELEM* top_elem) {
    // 若栈不空, 则用top_elem保存栈顶元素, 并返回OK; 否则返回NON_EXISTENT
    if (sea_stack.top == sea_stack.elements) {
        return NON_EXISTENT;
    }

    *top_elem = *(sea_stack.top - 1);

    return OK;
}


/*!
 * @brief **顺序栈入栈**
 * @param seq_stack **顺序栈**(指针)
 * @param elem **入栈元素**
 * @return **执行结果**
 * @note
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
 * @param seq_stack **顺序栈**(指针)
 * @param elem **栈顶元素**
 * @return **执行结果**
 * @note
 *
 * 顺序栈出栈
 * --------
 * --------
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
 * @param seq_stack **顺序栈**
 * @return **执行结果**
 * @note
 */
status_t SeqStackDestroy(seq_stack_t* seq_stack) {
    free(seq_stack->elements);
    free(seq_stack);

    return OK;
}


/*!
 * @brief **顺序栈清空**
 * @param seq_stack **顺序栈**
 * @return **执行结果**
 * @note
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
 * @param seq_stack **顺序栈**
 * @return **执行结果**
 * @note
 */
status_t SeqStackIsEmpty(seq_stack_t seq_stack) {
    if (seq_stack.top == seq_stack.elements) {
        return OK;
    }

    return ERROR;
}


/*!
 * @brief **顺序栈长度**
 * @param seq_stack **顺序栈**
 * @return **长度**
 * @note
 */
int SeqStackSize(seq_stack_t seq_stack) {
    return seq_stack.top - seq_stack.elements;
}


/*!
 * @brief **顺序栈打印**
 * @param seq_stack **顺序栈**
 * @note
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
