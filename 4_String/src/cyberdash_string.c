/*!
 * @file cyberdash_string.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  串
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <malloc.h>
#include <string.h>
#include "cyberdash_string.h"


/*!
 * <h1>字符串赋值</h1>
 * @param str **字符串**
 * @param chars **char数组**
 * @param str_len **字符串长度**
 * @return 执行结果
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
    if (!(str->buffer = (char*)malloc(str_len))) {
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


status_t StringConcat(string_t* target_string,
                      string_t* src_string1,
                      string_t* src_string2)
{
	if (target_string->buffer) {
		free(target_string->buffer);
	}

	if (!(target_string->buffer = (char *) malloc(src_string1->length + src_string2->length))) {
		return OVERFLOW;
	}

	for (int i = 0; i < src_string1->length; i++) {
        target_string->buffer[i] = src_string1->buffer[i];
	}

	for (int i = 0; i < src_string2->length; i++) {
        target_string->buffer[src_string1->length + i] = src_string2->buffer[i];
	}

    target_string->length = src_string1->length + src_string2->length;

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
 * 字符串插入
 * @param str
 * @param pos
 * @param insert_str
 * @return
 */
status_t Insert(string_t* str, int index, string_t* insert_str) {

    if (index < 0 || index > str->length) {
	    return OVERFLOW;
    }

    if (insert_str->length == 0) {
        return OK;
    }

    str->buffer = (char *) realloc(str->buffer, str->length + insert_str->length);
    if (str->buffer == NULL) {
        return NON_ALLOCATED;
    }

    int i = str->length - 1;
    for (; i >= index; i--) {
        str->buffer[i + insert_str->length] = str->buffer[i];
    }

    for (i = 0; i < insert_str->length; i++) {
        str->buffer[index + i] = insert_str->buffer[i];
    }

    str->length += insert_str->length;

    return OK;
}


int BruteForce(string_t* str, string_t* pattern, int offset) {

    int match_offset = -1;
    int pattern_index;

    for (int i = offset; i <= str->length - pattern->length; i++) {
        for (pattern_index = 0; pattern_index < pattern->length; pattern_index++) {
            if (str->buffer[i + pattern_index] != pattern->buffer[pattern_index]) {
                break;
            }
        }

        if (pattern_index == pattern->length) {
            match_offset = i;
            break;
        }
    }

    return match_offset;
}


/*
static void get_next(string_t *T, int next[])
{
	int i = 1;
	int j = 0;

	next[1] = 0;

	while (i < StringLength(T)) {
		if (j == 0 || T->buffer[i] == T->buffer[j]) {
			i++;
            j++;
			if (T->buffer[i] != T->buffer[j]) {
				next[i] = j;
			} else {
				next[i] = next[j];
			}
		} else {
			j = next[j];
		}
	}
}
 */


status_t KMPNext(const char* pattern, int pattern_len, int** next) {

    // 分配next数组内存
    *next = (int*)malloc((pattern_len + 1) * sizeof(int));
    if (*next == NULL) {
        return NON_ALLOCATED;
    }

    memset(*next, 0, pattern_len +1);

    /// 设置next[0] = -1
    int i = 0;
    int starting_index = -1;

    (*next)[0] = starting_index;

    while (i < pattern_len) {

        /// 使用next[0]处理next[1]
        /// 当模式串字符pattern[1]失配时, 必然从pattern[0]开始重新进行匹配, 因此next[1] = 0
        /// 此处逻辑可以和下面的pattern[i] == pattern[starting_index]分支逻辑合并
        /// 因此next[0] = -1
        /// 其余部分则相同(代码可以合并)
        if (starting_index == -1) {
            i++;
            starting_index++;
            (*next)[i] = starting_index;
        }
            /// 使用next[i]求next[i + 1]
        else
        {
            /// 如果pattern[i]和pattern[starting_index]相同, 则左右两侧的相同字符串区域扩展
            /// 示例
            ///  a b c d 5 6 a b c d 7
            ///  a b
            ///              a b
            ///                  ^
            ///                  |
            ///
            ///
            /// i == 8, starting_index == 2
            /// pattern[8] == pattern[2] == 'c', 走if( == )分支:
            ///     8++ -> 9,
            ///     starting_index++ -> 3
            ///     next[9] == pattern[3]
            ///
            ///
            ///  a b c d 5 6 a b c d 7
            ///  a b c
            ///              a b c
            ///                    ^
            ///                    |
            ///
            if (pattern[i] == pattern[starting_index]) {
                i++;
                starting_index++;
                (*next)[i] = starting_index;
            }
                /// 如果pattern[i]和pattern[starting_index]不同, 则使用next数组进行递归, 逐步验证
            else
            {
                starting_index = (*next)[starting_index];
            }
        }
    }

    return OK;
}



/*
int KMP(string_t *S, string_t *T, int pos)
{
	int i = pos, j = 0;
	int* next = malloc(StringLength(T));

	get_next(T, next);

	while (i < StringLength(S) && j <= StringLength(T)) {
		if (j == 0 || S->buffer[i] == T->buffer[j]) {
			i++;
			j++;
		} else {
			j = next[j];
		}
	}

	if (j <= StringLength(T)) {
		return i - StringLength(T);
	}

	return 0;
}
 */

int KMP(string_t* str, string_t* pattern, int offset) {

    int pattern_len = pattern->length;
    int* next;
    status_t status = KMPNext(pattern->buffer, pattern_len, &next);
    if (status != OK) {
        return status;
    }

    // cout<<"模式串: "<<pattern<<endl<<"对应的next数组: ";
    // PrintNextArray(next, pattern_len); // show the next array

    int pattern_str_i = 0;      // 模式串起始位置
    int target_str_i = offset;  // 目标串起始位置

    while (pattern_str_i < pattern_len && target_str_i < str->length) {
        /// 如果模式串字符(位置pattern_str_i)和目标串字符(位置target_str_i)相同, 则向后移位
        if (pattern->buffer[pattern_str_i] == str->buffer[target_str_i]) {
            pattern_str_i++;
            target_str_i++;
        }
        /// 如果模式串字符(位置pattern_str_i)和目标串字符(位置target_str_i)不同
        else
        {
            // 如果是模式串第1个字符不匹配, 则目标串向后移位
            if (pattern_str_i == 0) {
                target_str_i++;
            }
            // 如果不是模式串第1个字符不匹配, 则从模式串的next[pattern_str_i]开始执行下一趟匹配
            else
            {
                pattern_str_i = next[pattern_str_i];
            }
        }
    }

    free(next);

    int match_pos;

    if (pattern_str_i < pattern_len) {
        match_pos = -1; // 不匹配
    } else {
        match_pos = target_str_i - pattern_len; // 算出目标串中匹配的第一个字符的(在目标串中的)位置
    }

    return match_pos;
}


