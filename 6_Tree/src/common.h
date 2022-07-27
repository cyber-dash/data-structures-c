/*!
 * @file common.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id: cyberdash_yuan)
 * @brief common头文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_TREE_TYPE_H
#define CYBER_DASH_TREE_TYPE_H


/*! @brief 二叉树结点数据类型 */
typedef char BINARY_TREE_NODE_DATA;

#define TRUE    1   //!< 逻辑是
#define FALSE   0   //!< 逻辑非
#define MAX_TREE_SIZE 100   //!< 树最大结点数

/*! @brief 函数返回值枚举 */
typedef enum {
    OK = 0,             //!< 正确
    NON_ALLOCATED = 1,  //!< 内存分配失败
    NON_EXISTENT = 2,   //!< 不存在
    OVERFLOW = 3,       //!< 溢出
    ERROR = 4           //!< 其他类型错误
} status_t;


#endif // CYBER_DASH_TREE_TYPE_H
