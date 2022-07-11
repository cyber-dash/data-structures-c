﻿//
// Created by cyberdash@163.com on 2022/3/24.
//

#ifndef CYBER_DASH_TREE_TYPE_H
#define CYBER_DASH_TREE_TYPE_H


#define BINARY_TREE_NODE_DATA char //!< 二叉树结点数据类型
#define TRUE    1
#define FALSE   0
#define MAX_TREE_SIZE 100   //!< 树最大结点数

/*!
 * 函数返回值枚举
 */
typedef enum Status {
    OK = 0,         //! 正确
    NON_ALLOCATED,  //! 内存分配失败
    NON_EXISTENT,   //! 不存在
    OVERFLOW,       //! 溢出
    ERROR           //! 其他类型错误
} Status;


#endif // CYBER_DASH_TREE_TYPE_H
