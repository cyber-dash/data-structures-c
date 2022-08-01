/*!
 * @file common.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief common头文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#define ELEM    int //!< 元素类型

typedef enum {
    OK = 0,         //!< 正确
    NON_ALLOCATED,  //!< 分配内存失败
    OVERFLOW,
    UNDERFLOW,
    ERROR
} status_t;
