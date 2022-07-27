//
// Created by cyberdash@163.com on 2022/2/16.
//

#ifndef CYBER_DASH_QUEUE_TYPE_H
#define CYBER_DASH_QUEUE_TYPE_H


#define QUEUE_ELEM int

/*! @brief 函数返回值枚举 */
typedef enum {
    OK = 0,             //!< 正确
    NON_ALLOCATED = 1,  //!< 内存分配失败
    NON_EXISTENT = 2,   //!< 不存在
    OVERFLOW = 3,       //!< 溢出
    ERROR = 4           //!< 其他类型错误
} status_t;


#endif // CYBER_DASH_QUEUE_TYPE_H
