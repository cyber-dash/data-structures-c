//
// Created by cyberdash@163.com on 2021/12/30.
//

#include "stack.h"
#include "stdlib.h"


/*!
 * 顺序栈初始化
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
    if (SeqStackIsEmpty(seq_stack)){
        return NON_EXISTENT;
    }

    *elem = *(seq_stack.top - 1);   // 使用栈顶元素赋值

    return OK;
}


Status SeqStackPush(seq_stack_t* seq_stack, binary_tree_node_t* node) {
    // 栈满, 追加存储空间
    if (seq_stack->top - seq_stack->elements >= seq_stack->capacity) {
        seq_stack->elements = (STACK_ELEM*)realloc(seq_stack->elements,
                                                   (seq_stack->capacity + STACKINCREMENT) * sizeof(STACK_ELEM));
        if (!seq_stack->elements) {
            return NON_ALLOCATED;   // 存储分配失败
        }

        seq_stack->top = seq_stack->elements + seq_stack->capacity; // 调整top指向栈顶
        seq_stack->capacity += STACKINCREMENT;  // 调整扩容数值
    }

    *seq_stack->top = node; // node赋值到top指向的位置
    seq_stack->top++;       // top向后移一位

    return OK;
}


/*!
 * 出栈
 * @param seq_stack 顺序栈(指针)
 * @param elem 保存出栈元素的元素变量(指针)
 * @return 执行结果
 */
Status SeqStackPop(seq_stack_t* seq_stack, STACK_ELEM* elem) {
    if (seq_stack->top == seq_stack->elements) {
        return NON_EXISTENT;
    }

    seq_stack->top--;           // top向前移一位
    *elem = *seq_stack->top;    // top指向的元素值赋给elem

    return OK;
}


/*!
 * 栈销毁
 * @param seq_stack 顺序栈(指针)
 * @return
 */
Status SeqStackDestroy(seq_stack_t* seq_stack) {
    free(seq_stack->elements);
    free(seq_stack);

    return OK;
}


/*!
 * 栈清空
 * @param seq_stack 顺序栈(指针)
 * @return 执行结果
 */
Status ClearStack(seq_stack_t* seq_stack) {
    STACK_ELEM elem;
    while (SeqStackIsEmpty(*seq_stack) != OK) {
        SeqStackPop(seq_stack, &elem);
    }

    return OK;
}


/*!
 * 栈是否为空
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
 * 栈长度
 * @param seq_stack 顺序栈
 * @return 长度值
 */
int SeqStackLength(seq_stack_t seq_stack) {
    return seq_stack.top - seq_stack.elements;
}
