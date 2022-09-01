//
// Created by svenlee on 2022/9/1.
//

#ifndef CYBER_DASH_LINKED_LIST_COMMON_H
#define CYBER_DASH_LINKED_LIST_COMMON_H

#define ELEM_TYPE   int //!< 链表元素类型

/*! @brief 返回值类型 */
typedef enum {
    OK,             //!< 成功/正确
    NON_ALLOCATED,  //!< 内存分配失败
    NON_EXISTENT,   //!< 不存在
    ERROR           //!< 错误
} status_t;

#endif // CYBER_DASH_LINKED_LIST_COMMON_H
