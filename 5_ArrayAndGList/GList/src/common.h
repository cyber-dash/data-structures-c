//
// Created by cyberdash@163.com on 2022/5/14.
//

#ifndef CYBER_DASH_GEN_LIST_COMMON_H
#define CYBER_DASH_GEN_LIST_COMMON_H


#define MAX_STRING_SIZE 100

/*! @brief 返回值状态 */
typedef enum {
    OK = 0,         //!< 正确
    NON_ALLOCATED,  //!< 内存分配失败
    NON_EXISTENT,   //!< 不存在
    OVERFLOW,       //!< 溢出
    ERROR,          //!< 其他错误
} status_t;

#endif // CYBER_DASH_GEN_LIST_COMMON_H
