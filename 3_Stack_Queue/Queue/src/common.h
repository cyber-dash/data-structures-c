/*!
 * @file common.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief common头文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_QUEUE_TYPE_H
#define CYBER_DASH_QUEUE_TYPE_H


#define QUEUE_ELEM int  //!< 队列元素类型

/*! @brief 函数返回值枚举 */
typedef enum {
    OK = 0,             //!< 正确
    NON_ALLOCATED = 1,  //!< 内存分配失败
    NON_EXISTENT = 2,   //!< 不存在
    OVERFLOW = 3,       //!< 溢出
    ERROR = 4           //!< 其他类型错误
} status_t;


#endif // CYBER_DASH_QUEUE_TYPE_H
