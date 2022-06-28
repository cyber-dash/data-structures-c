//
// Created by cyberdash@163.com on 2022/2/16.
//

#ifndef CYBER_DASH_QUEUE_TYPE_H
#define CYBER_DASH_QUEUE_TYPE_H


#define QUEUE_ELEM int

typedef enum Status {
    OK,
    NON_ALLOCATED,
    NON_EXISTENT,
    ERROR,
    OVERFLOW,
} Status;


#endif // CYBER_DASH_QUEUE_TYPE_H
