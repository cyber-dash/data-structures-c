/*!
 * @file stack.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 栈源文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "stack.h"
#include "stdlib.h"


/*!
 * @brief 顺序栈初始化
 * @param seq_stack 顺序栈(指针)
 * @return 执行结果
 */
Status SeqStackInit(seq_stack_t* seq_stack) {

    // 栈元素数组申请内存
    seq_stack->elements = (STACK_ELEM*)malloc(STACK_INIT_CAPACITY * sizeof(STACK_ELEM));
    if (!seq_stack->elements) {
        return NON_ALLOCATED;   // 存储分配失败
    }

    seq_stack->top = seq_stack->elements;       //!< top指针初始化
    seq_stack->capacity = STACK_INIT_CAPACITY;  //!< 栈容量初始化

    return OK;
}


/*!
 * @brief 获取栈顶元素
 * @param seq_stack 顺序栈
 * @param elem 栈顶元素保存变量
 * @return 执行结果
 */
Status SeqStackGetTop(seq_stack_t seq_stack, STACK_ELEM* elem) {

    // 如果栈空, 返回NON_EXISTENT
    if (SeqStackIsEmpty(seq_stack)){
        return NON_EXISTENT;
    }

    *elem = *(seq_stack.top - 1);   // 使用栈顶元素(top指针指向位置的前一位)赋值

    return OK;
}


/*!
 * @brief 入栈
 * @param seq_stack 顺序栈(指针)
 * @param elem 入栈元素
 * @return 执行结果
 */
Status SeqStackPush(seq_stack_t* seq_stack, binary_tree_node_t* elem) {
    // 栈满, 追加存储空间
    if (seq_stack->top - seq_stack->elements >= seq_stack->capacity) {
        // 调用realloc重新分配内存
        seq_stack->elements = (STACK_ELEM*)realloc(seq_stack->elements,
                                                   (seq_stack->capacity + STACK_INCREMENT) * sizeof(STACK_ELEM));
        if (!seq_stack->elements) {
            return NON_ALLOCATED;   // 如果存储分配失败, 返回NON_ALLOCATED
        }

        seq_stack->top = seq_stack->elements + seq_stack->capacity; // 调整top指向
        seq_stack->capacity += STACK_INCREMENT;  // 调整扩容数值
    }

    *seq_stack->top = elem; // node赋值到top指向的位置
    seq_stack->top++;       // top向后移一位

    return OK;
}


/*!
 * @brief 出栈
 * @param seq_stack 顺序栈(指针)
 * @param elem 保存出栈元素的元素变量(指针)
 * @return 执行结果
 */
Status SeqStackPop(seq_stack_t* seq_stack, STACK_ELEM* elem) {
    //!< 如果栈空, 返回NON_EXISTENT
    if (seq_stack->top == seq_stack->elements) {
        return NON_EXISTENT;
    }

    seq_stack->top--;           //!< top指向向前移一位
    *elem = *seq_stack->top;    //!< top指向的元素值赋给*elem

    return OK;
}


/*!
 * @brief 栈销毁
 * @param seq_stack 顺序栈(指针)
 * @return 执行结果
 */
Status SeqStackDestroy(seq_stack_t* seq_stack) {
    free(seq_stack->elements);
    free(seq_stack);

    return OK;
}


/*!
 * @brief 栈清空
 * @param seq_stack 顺序栈(指针)
 * @return 执行结果
 */
Status SeqStackClear(seq_stack_t* seq_stack) {
    STACK_ELEM elem;
    while (SeqStackIsEmpty(*seq_stack) != OK) {
        SeqStackPop(seq_stack, &elem);
    }

    return OK;
}


/*!
 * @brief 栈是否为空
 * @param seq_stack 顺序栈
 * @return 是否为空
 */
int SeqStackIsEmpty(seq_stack_t seq_stack) {
    if (seq_stack.top == seq_stack.elements) {
        return TRUE;
    }

    return FALSE;
}


/*!
 * @brief 栈长度
 * @param seq_stack 顺序栈
 * @return 长度
 */
int SeqStackLength(seq_stack_t seq_stack) {
    return seq_stack.top - seq_stack.elements;
}
