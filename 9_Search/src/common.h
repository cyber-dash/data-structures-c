/*!
 * @file search.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 查找
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_SEARCH_H
#define CYBER_DASH_SEARCH_H


#define KEY     int
#define VALUE   double

#define EQUAL(a, b) ((a) == (b))
#define LESS_THAN(a, b) ((a) < (b))
#define LESS_THAN_OR_EQUAL(a, b) ((a) <= (b))


typedef enum Status {
    OK = 0,
    NON_ALLOCATED,
    NON_EXISTENT,
    ERROR
} Status;


#endif // CYBER_DASH_SEARCH_H
