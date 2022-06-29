//
// Created by cyberdash@163.com on 2022/3/24.
//

#ifndef CYBER_DASH_TREE_COMMON_H
#define CYBER_DASH_TREE_COMMON_H


#define TREE_NODE_DATA char
#define TRUE    1
#define FALSE   0
#define MAX_TREE_SIZE 100           // 最大结点数

typedef enum Status {
    OK,
    NON_ALLOCATED,
    NON_EXISTENT,
    ERROR,
    OVERFLOW
} Status;


#endif // CYBER_DASH_TREE_COMMON_H
