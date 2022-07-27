/*!
 * @file cyberdash_string.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 字符串头文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */
#ifndef CYBER_DASH_STRING_H
#define CYBER_DASH_STRING_H


/*! @brief 函数返回值枚举 */
typedef enum Status {
    OK = 0,         //!< 正确
    NON_ALLOCATED,  //!< 内存分配失败
    NON_EXISTENT,   //!< 不存在
    OVERFLOW,       //!< 溢出
    ERROR,          //!< 其他错误
} status_t;

/*! @brief 字符串 */
typedef struct {
    char* buffer;   //!< char缓存数组
    int length;     //!< 长度
} string_t;


// 字符串赋值
status_t StringAssign(string_t* str, const char* chars, int str_len);

// 字符串复制
status_t StringCopy(string_t* dest_str, string_t* src_str);

// 是否为空字符串
int StringEmpty(string_t* str);

// 字符串比较
int StringCompare(string_t* str1, string_t* str2);

// 字符串长度
int StringLength(string_t* str);

// 字符串清空
status_t StringClear(string_t* str);

// 字符串拼接
status_t StringConcat(string_t* resulting_string, string_t* str1, string_t* str2);

// 字符串子串
status_t StringSubStr(string_t* str, string_t* sub_str, int offset, int sub_str_len);

// 字符串插入
status_t StringInsert(string_t* str, int index, string_t* insert_str);

// 字符串暴力匹配(BF)
int StringBruteForceSearch(string_t* str, string_t *pattern, int offset);

// 字符串KMP匹配
int StringKMPSearch(string_t *str, string_t *pattern, int offset);


#endif //CYBER_DASH_STRING_H
