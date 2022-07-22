/*!
 * @file cyberdash_string.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  串
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdlib.h>
#include <string.h>
#include "cyberdash_string.h"


/*!
 * <h1>字符串赋值</h1>
 * @param str **字符串**
 * @param chars **char数组**
 * @param str_len **字符串长度**
 * @return **执行结果**
 * @note
 */
status_t StringAssign(string_t* str, const char* chars, int str_len) {

    /// ### 1 释放str->buffer###
	if (str->buffer) {
		free(str->buffer);
	}

    /// ### 2 处理str_len等于0###
    /// &emsp; **if** str_len为0 :\n
    /// &emsp;&emsp; str->buffer设置为NULL\n
    /// &emsp;&emsp; str->length设置为0\n
    /// &emsp;&emsp; 返回OK\n
	if (str_len == 0) {
        str->buffer = NULL;
        str->length = 0;
        return OK;
	}

    /// ### 3 str->buffer分配内存###
    if (!(str->buffer = (char*)malloc(str_len + 1))) {
        return NON_ALLOCATED;
    }

    for (int i = 0; i < str_len; i++) {
        str->buffer[i] = chars[i];
    }

    str->length = str_len;

	return OK;
}


/*!
 * 字符串复制
 * @param dest_str
 * @param src_str
 * @return
 */
status_t StringCopy(string_t* dest_str, string_t* src_str) {
	for (int i = 0; i < StringLength(dest_str) && i < StringLength(src_str); i++) {
        dest_str->buffer[i] = src_str->buffer[i];
	}

    dest_str->length = src_str->length;

	return OK;
}


int StringEmpty(string_t* str) {
	return str->length == 0;
}


int StringCompare(string_t* string1, string_t* string2) {
	for (int i = 0; i < string1->length && i < string2->length; i++) {
		if (string1->buffer[i] != string2->buffer[i]) {
			return string1->buffer[i] - string2->buffer[i];
		}
	}

	return string1->length - string2->length;
}


int StringLength(string_t* str) {
	return str->length;
}


status_t StringClear(string_t* str) {
	if (str->buffer) {
		free(str->buffer);
        str->buffer = NULL;
	}

    str->length = 0;

	return OK;
}


status_t StringConcat(string_t* target_string, string_t* str1, string_t* str2) {
	if (target_string->buffer) {
		free(target_string->buffer);
	}

	if (!(target_string->buffer = (char *) malloc(str1->length + str2->length))) {
		return OVERFLOW;
	}

	for (int i = 0; i < str1->length; i++) {
        target_string->buffer[i] = str1->buffer[i];
	}

	for (int i = 0; i < str2->length; i++) {
        target_string->buffer[str1->length + i] = str2->buffer[i];
	}

    target_string->length = str1->length + str2->length;

	return OK;
}


// todo:
status_t StringSubString(string_t* sub_string, string_t* src_string, int pos, int len) {
	int i;

	if (pos < 1 || pos >= src_string->length || len < 0 || len > src_string->length - pos + 1) {
		return ERROR;
	}

	if (sub_string->buffer) {
		free(sub_string->buffer);
	}

	if (len == 0) {
        sub_string->buffer = NULL;
        sub_string->length = 0;
	} else {
        sub_string->buffer = (char *) malloc(len);
		if (sub_string->buffer == NULL) {
			return OVERFLOW;
		}

		for (i = 0; i <= len; i++) {
            sub_string->buffer[i] = src_string->buffer[pos + i - 1];
		}

        sub_string->length = len;
	}

	return OK;
}


/*!
 * <h1>字符串插入</h1>
 * @param str **被插入的字符串**
 * @param index **插入位置**(该位置前)
 * @param insert_str **插入字符**
 * @return 执行结果
 * @note
 */
status_t Insert(string_t* str, int index, string_t* insert_str) {

    /// ###1 非法插入位置处理###
    /// &emsp; 返回OVERFLOW
    if (index < 0 || index > str->length) {
	    return OVERFLOW;
    }

    /// ###2 插入字符串为空串处理###
    /// &emsp; 直接返回OK
    if (insert_str->length == 0) {
        return OK;
    }

    /// ###3 重新分配内存###
    /// &emsp; 使用realloc重新分配内存\n
    /// &emsp;&emsp; 新申请的字符串长度: str->length + insert_str->length\n
    /// &emsp;&emsp; **if** 申请内存失败 :\n
    /// &emsp;&emsp;&emsp; 返回NON_ALLOCATED\n
    int new_length = str->length + insert_str->length;
    str->buffer = (char*)realloc(str->buffer, sizeof(char) * (new_length + 1));
    if (str->buffer == NULL) {
        return NON_ALLOCATED;
    }

    /// ###4 执行插入###
    /// - **移动插入位置后侧(包含)字符**\n
    /// &emsp;索引[index ... str->length - 1], str->length - 1 - index个字符,\n
    /// &emsp;向右侧移动insert_str->length个位置
    int i = str->length - 1;
    for (; i >= index; i--) {
        str->buffer[i + insert_str->length] = str->buffer[i];
    }

    /// - **待插入字符串赋值**\n
    /// &emsp; **for loop** 遍历insert_str :\n
    /// &emsp;&emsp; insert_str向str相应位置赋值\n
    for (i = 0; i < insert_str->length; i++) {
        str->buffer[index + i] = insert_str->buffer[i];
    }

    /// ###5 更新str->length
    str->length = new_length;

    return OK;
}


/*!
 * <h1>字符串暴力匹配(BF)</h1>
 * @param str **目标串**
 * @param pattern **模式串**
 * @param offset **目标串偏移量**
 * @return **匹配索引**
 * @note
 */
int StringBruteForceSearch(string_t* str, string_t* pattern, int offset) {

    /// ###1 匹配点索引初始化为-1###
    int match_index = -1;

    /// ###2 执行BF算法###
    /// &emsp; **for loop** 遍历目标串(starting_index为每次失配后, 下一趟匹配目标串的起始索引, 初始化为offset) :\n
    for (int starting_index = offset; starting_index <= str->length - pattern->length; starting_index++) {
        /// &emsp;&emsp; 模式串索引0开始\n
        int pattern_index = 0;

        /// &emsp;&emsp; **while** 模式串遍历未结束 :\n
        while (pattern_index < pattern->length) {
            /// &emsp;&emsp;&emsp; **if** str->buffer[starting_index + pattern_index] 不等于 pattern->buffer[pattern_index] :\n
            /// &emsp;&emsp;&emsp;&emsp; 跳出循环\n
            if (str->buffer[starting_index + pattern_index] != pattern->buffer[pattern_index]) {
                break;
            }

            /// &emsp;&emsp;&emsp; 模式串索引向后挪1位
            pattern_index++;
        }

        /// &emsp;&emsp; **if** 模式串遍历结束 :\n
        /// &emsp;&emsp;&emsp; 匹配点索引为i\n
        /// &emsp;&emsp;&emsp; 跳出循环\n
        if (pattern_index == pattern->length) {
            match_index = starting_index;
            break;
        }
    }

    /// ###3 返回匹配点索引值###
    return match_index;
}


/*!
 * <h1>KMP算法求next数组</h1>
 * @param pattern **模式串**
 * @param pattern_len **模式串长度**
 * @param next **next数组**(int二级指针)
 * @return 执行结果
 * @note
 */
status_t KMPNext(const char* pattern, int pattern_len, int** next) {

    /// ###1 分配next数组内存###
    /// &emsp; **if** 分配内存失败 :\n
    /// &emsp;&emsp; 返回NON_ALLOCATED\n
    *next = (int*)malloc((pattern_len) * sizeof(int));
    if (*next == NULL) {
        return NON_ALLOCATED;
    }

    /// &emsp; memset置0\n
    memset(*next, 0, pattern_len);

    /// ###2 初始化pattern_index/starting_index/next[0]###
    /// &emsp; pattern_index为模式串的索引, 初始化为0\n
    /// &emsp; starting_index为目标串失配后的起始匹配索引, 初始化为-1\n
    /// &emsp; next[0]设置为-1\n
    int pattern_index = 0;
    int starting_index = -1;

    (*next)[0] = starting_index;

    /// ###3 递归构造nest数组 ###
    /// &emsp; **while** 遍历模式串 :\n
    while (pattern_index < pattern_len) {

        /// &emsp;&emsp; **if** starting_index != -1 :\n
        if (starting_index != -1) {
            /// &emsp;&emsp;&emsp; **if** pattern[pattern_index]和pattern[starting_index]不同(失配) :\n
            /// &emsp;&emsp;&emsp;&emsp; pattern_index++;\n
            /// &emsp;&emsp;&emsp;&emsp; starting_index++;\n
            /// &emsp;&emsp;&emsp;&emsp; (*next)[pattern_index] = starting_index;\n
            /// ```
            /// 如果pattern[pattern_index]和str[starting_index]相同,
            /// 则左右两侧的相同字符串区域扩展
            ///
            /// 示例:
            ///  a b c d 5 6 a b c d 7
            ///  a b
            ///              a b
            ///                  ^
            ///                  |
            ///
            /// 此时:
            ///  pattern_index == 8, 目标串遍历至索引8
            ///  starting_index == 2, 模式串遍历至索引2
            ///
            ///  pattern[8] == pattern[2] == 'c', 走if( == )分支:
            ///     pattern_index++ -> 9,
            ///     starting_index++ -> 3
            ///     更新next[pattern_index] => next[9] = 3
            ///
            ///  a b c d 5 6 a b c d 7
            ///  a b c
            ///              a b c
            ///                    ^
            ///                    |
            ///
            /// ```
            /// &emsp;&emsp;&emsp; **else**\n
            /// &emsp;&emsp;&emsp;&emsp; 令starting_index = next[starting_index]\n
            /// &emsp;&emsp;&emsp;&emsp; (即starting_index退回到前一匹配点)\n
            if (pattern[pattern_index] == pattern[starting_index]) {
                pattern_index++;
                starting_index++;
                (*next)[pattern_index] = starting_index;
            } else {
                starting_index = (*next)[starting_index];
            }
        } else {
            /// &emsp;&emsp; **else**(starting_index == -1) \n
            /// &emsp;&emsp;&emsp; pattern_index++;\n
            /// &emsp;&emsp;&emsp; starting_index++;\n
            /// &emsp;&emsp;&emsp; (*next)[pattern_index] = starting_index;\n
            /// ```
            /// 当模式串字符pattern[1]失配时, 必然从pattern[0]开始重新进行匹配, 因此next[1] = 0
            /// 令使用next[0]处理next[1] => 因此next[0] = -1
            /// 此处逻辑可以和下面的pattern[pattern_index] == pattern[starting_index]分支逻辑合并
            /// 其余部分则相同(代码可以合并)
            /// ```
            pattern_index++;
            starting_index++;
            (*next)[pattern_index] = starting_index;
        }
    }

    return OK;
}


/*!
 * <h1>字符串KMP匹配</h1>
 * @param str **目标串**
 * @param pattern **模式串**
 * @param offset **目标串偏移量**
 * @return **匹配索引**
 * @note
 */
int StringKMPSearch(string_t* str, string_t* pattern, int offset) {

    /// ###1 求模式串next数组###
    /// &emsp; 调用KMPNext函数求next数组\n
    /// &emsp; **if** 调用失败 :\n
    /// &emsp;&emsp; 返回错误码\n
    int pattern_len = pattern->length;
    int* next;
    status_t status = KMPNext(pattern->buffer, pattern_len, &next);
    if (status != OK) {
        return status;
    }

    int pattern_index = 0;  // 模式串索引
    int str_index = offset; // 目标串索引

    /// ###2 使用next数组找模式串的匹配位置(的索引)###
    while (pattern_index < pattern_len && str_index < str->length) {
        /// &emsp; **if** 模式串索引字符 == 目标串索引的字符\n
        /// &emsp;&emsp; 模式串索引and目标串索引, 则向后移1位\n
        if (pattern->buffer[pattern_index] == str->buffer[str_index]) {
            pattern_index++;
            str_index++;
        } else {
        /// &emsp; **else**(模式串索引字符 != 目标串索引的字符): \n
            /// &emsp;&emsp; **if** 模式串索引0字符失配 :\n
            /// &emsp;&emsp;&emsp; 目标串索引向后移1位\n
            if (pattern_index == 0) {
                str_index++;
            } else {
                /// &emsp;&emsp; **else**(模式串索引非0字符失配) :\n
                /// &emsp;&emsp;&emsp; 从模式串的next[pattern_index]开始执行下一趟匹配\n
                pattern_index = next[pattern_index];
            }
        }
    }

    free(next);

    int match_pos;

    ///###3 求目标串匹配索引###
    ///&emsp; **if** 模式串匹配索引 < 模式串长度 :\n
    ///&emsp;&emsp; 匹配索引为-1(没有匹配点)\n
    ///&emsp; **else**\n
    ///&emsp;&emsp; 匹配索引为str_index - pattern_len\n
    if (pattern_index < pattern_len) {
        match_pos = -1; // 不匹配
    } else {
        match_pos = str_index - pattern_len; // 算出目标串中匹配的第一个字符的(在目标串中的)位置
    }

    return match_pos;
}


