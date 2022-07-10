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
    char* str;
    unsigned int length;
} cyber_dash_string_t;

Status StringAssign(cyber_dash_string_t* cyber_dash_string, char* src_str, unsigned int str_len);

int StringLength(cyber_dash_string_t* cyber_dash_string);

int StringCompare(cyber_dash_string_t* string1, cyber_dash_string_t* string2);

Status StringClear(cyber_dash_string_t* cyber_dash_string);

Status StringConcat(cyber_dash_string_t* target_string, cyber_dash_string_t* src_string1, cyber_dash_string_t* src_string2);

// todo:
Status StringSubString(cyber_dash_string_t* sub_string, cyber_dash_string_t *src_string, int pos, int len);

int BruteForce(cyber_dash_string_t *S, cyber_dash_string_t *T, int pos);

int KMP(cyber_dash_string_t *S, cyber_dash_string_t *T, int pos);

Status StringCopy(cyber_dash_string_t *target_string, cyber_dash_string_t *src_string);

int StringEmpty(cyber_dash_string_t *cyber_dash_string);

Status Insert(cyber_dash_string_t *S, int pos, cyber_dash_string_t *T);


#endif //CYBER_DASH_STRING_H
