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
} Status;

typedef struct {
    char* buffer;
    int length;
} string_t;

Status StringAssign(string_t* str, const char* src_chars, int str_len);

int StringLength(string_t* str);

int StringCompare(string_t* string1, string_t* string2);

Status StringClear(string_t* str);

Status StringConcat(string_t* target_string, string_t* src_string1, string_t* src_string2);

// todo:
Status StringSubString(string_t* sub_string, string_t *src_string, int pos, int len);

int BruteForce(string_t *S, string_t *T, int pos);

int KMP(string_t *S, string_t *T, int pos);

Status StringCopy(string_t *target_string, string_t *src_string);

int StringEmpty(string_t *str);

Status Insert(string_t *S, int pos, string_t *T);


#endif //CYBER_DASH_STRING_H
