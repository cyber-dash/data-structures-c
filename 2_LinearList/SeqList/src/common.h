/*!
 * @file common.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief common头文件
 * @version 1.1.0
 * @date 2022-08-15
 */

#ifndef CYBER_DASH_SEQ_LIST_COMMON_H
#define CYBER_DASH_SEQ_LIST_COMMON_H


#define LIST_INIT_CAPACITY  100 //!< 线性表初始化长度
#define LIST_INCREMENT      10  //!< 线性表增量
#define ELEM_TYPE           int //!< 线性表元素类型

/*! @brief 函数返回值枚举 */
typedef enum {
    OK = 0,             //!< 正确
    NON_ALLOCATED = 1,  //!< 内存分配失败
    NON_EXISTENT = 2,   //!< 不存在
    OVERFLOW = 3,       //!< 溢出
    ERROR = 4           //!< 其他类型错误
} status_t;


#endif // CYBER_DASH_SEQ_LIST_COMMON_H
