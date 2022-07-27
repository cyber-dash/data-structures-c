/*!
 * @file common.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  广义表common头文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

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
