/*!
 * @file cyberdash_string.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  串
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */
#ifndef CYBER_DASH_STRING_H
#define CYBER_DASH_STRING_H


typedef enum Status {
    OK = 0,
    NON_ALLOCATED,
    NON_EXISTENT,
    OVERFLOW,
    ERROR,
} status_t;

typedef struct {
    char* buffer;
    int length;
} string_t;

status_t StringAssign(string_t* str, const char* chars, int str_len);

int StringLength(string_t* str);

int StringCompare(string_t* str1, string_t* str2);

status_t StringClear(string_t* str);

status_t StringConcat(string_t* resulting_str, string_t* str1, string_t* str2);

// todo:
status_t StringSubStr(string_t* str, string_t* sub_str, int offset, int sub_str_len);

int StringBruteForceSearch(string_t* str, string_t *pattern, int offset);

int StringKMPSearch(string_t *str, string_t *pattern, int offset);

status_t StringCopy(string_t *dest_str, string_t *src_str);

int StringEmpty(string_t* str);

status_t StringInsert(string_t* str, int index, string_t* insert_str);


#endif //CYBER_DASH_STRING_H
