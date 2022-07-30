/*!
 * @file common.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief common头文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_SEARCH_H
#define CYBER_DASH_SEARCH_H


#define KEY     int     //!< 关键码类型
#define VALUE   double  //!< 数据项类型

#define EQUAL(a, b) ((a) == (b))    //!< 等于
#define LESS_THAN(a, b) ((a) < (b)) //!< 小于
#define LESS_THAN_OR_EQUAL(a, b) ((a) <= (b))   //!< 小于等于


/*! @brief 函数返回值枚举 */
typedef enum {
    OK = 0,         //!< 正确
    NON_ALLOCATED,  //!< 内存分配失败
    NON_EXISTENT,   //!< 不存在
    ERROR           //!< 其他错误
} status_t;


#endif // CYBER_DASH_SEARCH_H
