/*!
 * @file cyberdash_string.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 字符串源文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdlib.h>
#include <string.h>
#include "cyberdash_string.h"


 /*!
  * 字符串赋值
  * @param str **字符串(指针)**
  * @param chars **char数组**
  * @param str_len **字符串长度**
  * @return **执行结果**
  * @note
  * 字符串赋值
  * ---------
  * ---------
  * ### 1 释放str->buffer###
  */
status_t StringAssign(string_t* str, const char* chars, int str_len) {

	// 释放str->buffer
	if (str->buffer) {
		free(str->buffer);
	}

	// 处理str_len等于0的情况
	if (str_len == 0) {
		str->buffer = NULL; // str->buffer设置为NULL
		str->length = 0;    // 字符串长度设置为0

		return OK;
	}

	/// ### 3 str->buffer分配内存###
    str->buffer = (char*)malloc(str_len + 1);
	if (!str->buffer) {
		return NON_ALLOCATED;
	}

	/// &emsp; 字符串buffer调用memset置0\n
	memset(str->buffer, 0, sizeof(char) * (str_len + 1));

	/// ###4 填充buffer内容, 设置length###
	for (int i = 0; i < str_len; i++) {
		str->buffer[i] = chars[i];
	}

	str->length = str_len;

	return OK;
}


/*!
 * <h1>字符串复制</h1>
 * @param dest_str **目标串(指针)**
 * @param src_str **被复制串(指针)**
 * @return 执行结果
 * @note
 */
status_t StringCopy(string_t* dest_str, string_t* src_str) {
	/// ### 1 释放目标串的buffer###
	if (dest_str->buffer) {
		free(dest_str->buffer);
	}

	/// ### 2 目标串的buffer分配内存###
	/// &emsp; **if** 内存分配失败 :\n
	/// &emsp;&emsp; 返回NON_ALLOCATED
	if (!(dest_str->buffer = (char*)malloc(src_str->length + 1))) {
		return NON_ALLOCATED;
	}

	/// &emsp; 目标串buffer调用memset置0\n
	memset(dest_str->buffer, 0, sizeof(char) * (src_str->length + 1));

	/// ###3 填充buffer内容, 设置length###
	for (int i = 0; i < src_str->length; i++) {
		dest_str->buffer[i] = src_str->buffer[i];
	}

	dest_str->length = src_str->length;


	return OK;
}


/*!
 * <h1>是否为空字符串</h1>
 * @param str 字符串
 * @return 结果
 */
int StringEmpty(string_t* str) {
	return str->length == 0;
}


/*!
 * <h1>字符串比较</h1>
 * @param str1 **字符串1(指针)**
 * @param str2 **字符串2(指针)**
 * @return **比较结果**
 * @note
 */
int StringCompare(string_t* str1, string_t* str2) {
	/// ### 1 依次遍历两个字符串, 每趟对两个遍历字符进行比较###
	for (int i = 0; i < str1->length && i < str2->length; i++) {
		if (str1->buffer[i] != str2->buffer[i]) {
			return str1->buffer[i] - str2->buffer[i];
		}
	}

	/// ### 2 如果过程1没有得出结果, 比较长度###
	return str1->length - str2->length;
}


/*!
 * <h1>字符串长度</h1>
 * @param str 字符串
 * @return 长度
 */
int StringLength(string_t* str) {
	return str->length;
}


/*!
 * <h1>字符串清空</h1>
 * @param str **字符串**
 * @return **执行结果**
 */
status_t StringClear(string_t* str) {
	/// ###1 释放buffer###
	if (str->buffer) {
		free(str->buffer);
		str->buffer = NULL;
	}

	/// ###2 length置0###
	str->length = 0;

	return OK;
}


/*!
 * <h1>字符串拼接</h1>
 * @param resulting_string **结果串**
 * @param str1 **字符串1**
 * @param str2 **字符串2**
 * @return 执行结果
 * @note
 */
status_t StringConcat(string_t* resulting_string, string_t* str1, string_t* str2) {

	/// ### 1 释放结果串的buffer###
	if (resulting_string->buffer) {
		free(resulting_string->buffer);
	}

	/// ### 2 结果串的buffer分配内存###
	if (!(resulting_string->buffer = (char*)malloc(str1->length + str2->length + 1))) {
		return NON_ALLOCATED;
	}

	memset(resulting_string->buffer, 0, sizeof(char) * (str1->length + str2->length + 1));

	/// ###3 对结果串依次填充两个字符串###
	/// - 两个循环遍历, 执行字符填充
	for (int i = 0; i < str1->length; i++) {
		resulting_string->buffer[i] = str1->buffer[i];
	}

	for (int i = 0; i < str2->length; i++) {
		resulting_string->buffer[str1->length + i] = str2->buffer[i];
	}

	/// - 设置结果串的length
	resulting_string->length = str1->length + str2->length;

	return OK;
}


/*!
 * <h1>字符串子串</h1>
 * @param str **字符串**
 * @param sub_str **子串**
 * @param offset **字符串偏移量**
 * @param sub_str_len **子串长度**
 * @return **执行结果**
 * @note
 */
status_t StringSubStr(string_t* str, string_t* sub_str, int offset, int sub_str_len) {

	/// ###1 边界条件判断###
	/// &emsp; **if** 若干边界条件错误 :\n
	/// &emsp;&emsp; 返回OVERFLOW
	if (offset < 0 || offset > str->length ||
		sub_str_len < 0 || sub_str_len > str->length - offset + 1)
	{
		return OVERFLOW;
	}

	/// ###2 释放子串sub_str->buffer###
	/// &emsp; 释放sub_str->buffer
	if (sub_str->buffer) {
		free(sub_str->buffer);
	}

	/// ###3 空子串处理###
	/// &emsp; **if** 子串长度为0\n
	/// &emsp;&emsp; buffer为NULL, length为0\n
	/// &emsp;&emsp; 返回OK\n
	if (sub_str_len == 0) {
		sub_str->buffer = NULL;
		sub_str->length = 0;

		return OK;
	}

	/// ###4 构造子串###
	/// - 分配子串buffer内存
	/// &emsp; **if** 内存分配失败 :\n
	/// &emsp;&emsp; 返回OVERFLOW
	sub_str->buffer = (char*)malloc(sub_str_len);
	if (sub_str->buffer == NULL) {
		return OVERFLOW;
	}

	/// - 子串buffer每个字符赋值\n
	/// &emsp; **for loop** 字符串buffer[offset ... offset + sub_str_len - 1] :\n
	/// &emsp;&emsp; sub_str->buffer[i] <= str->buffer[offset + i]\n
	for (int i = 0; i < sub_str_len; i++) {
		sub_str->buffer[i] = str->buffer[offset + i];
	}

	/// - 更新子串length\n
	sub_str->length = sub_str_len;

	return OK;
}


/*!
 * <h1>字符串插入</h1>
 * @param str **被插入的字符串**
 * @param index **插入位置**(该位置前)
 * @param insert_str **待插入字符**
 * @return 执行结果
 * @note
 */
status_t StringInsert(string_t* str, int index, string_t* insert_str) {

	/// ###1 非法插入位置处理###
	/// &emsp; 返回OVERFLOW
	if (index < 0 || index > str->length) {
		return OVERFLOW;
	}

	/// ###2 待插入字符串为空串处理###
	/// &emsp; 直接返回OK
	if (insert_str->length == 0) {
		return OK;
	}

	/// ###3 重新分配内存###
	/// &emsp; 使用realloc重新对被插入字符串分配内存\n
	/// &emsp;&emsp; 新申请的字符串长度: str->length + insert_str->length\n
	/// &emsp;&emsp; **if** 申请内存失败 :\n
	/// &emsp;&emsp;&emsp; 返回NON_ALLOCATED\n
	int new_length = str->length + insert_str->length;
	str->buffer = (char*)realloc(str->buffer, sizeof(char) * (new_length + 1));
	if (str->buffer == NULL) {
		return NON_ALLOCATED;
	}

	/// ###4 执行插入###
	/// - **移动被插入字符串的插入位置后侧(包含)所有字符**\n
	/// &emsp;索引[index ... str->length - 1], 一共str->length - index个字符,\n
	/// &emsp;向后侧移动insert_str->length个位置
	int i = str->length - 1;
	for (; i >= index; i--) {
		str->buffer[i + insert_str->length] = str->buffer[i];
	}

	/// - **使用待插入字符串赋值**\n
	/// &emsp; **for loop** 遍历insert_str :\n
	/// &emsp;&emsp; insert_str向str相应位置赋值\n
	for (i = 0; i < insert_str->length; i++) {
		str->buffer[index + i] = insert_str->buffer[i];
	}

	/// ###5 更新被插入字符串的length
	str->length = new_length;

	return OK;
}


/*!
 * **字符串暴力匹配(BF)**
 * @param str **目标串**
 * @param pattern **模式串**
 * @param offset **目标串偏移量**
 * @return **目标串的匹配索引**
 * @note
 * 字符串暴力匹配(BF)
 * ----------------
 * ----------------
 * ###1 目标串的匹配索引初始化为-1###
 */
int StringBruteForceSearch(string_t* str, string_t* pattern, int offset) {

	/// ###1 目标串的匹配索引初始化为-1###
	int match_index = -1;

	/// ###2 执行BF算法###
	/// &emsp; **for loop** 遍历目标串(starting_index为每次失配后, 下一趟匹配目标串的起始索引, 初始化为offset) :\n
	for (int starting_index = offset; starting_index <= str->length - pattern->length; starting_index++) {
		/// &emsp;&emsp; 模式串索引0开始\n
		int pattern_index = 0;

		/// &emsp;&emsp; **while** 模式串遍历未结束 :\n
		while (pattern_index < pattern->length) {
			/// &emsp;&emsp;&emsp; **if** 目标串遍历字符 不匹配 模式串遍历字符 :\n
			/// &emsp;&emsp;&emsp;&emsp; 跳出循环\n
			if (str->buffer[starting_index + pattern_index] != pattern->buffer[pattern_index]) {
				break;
			}

			/// &emsp;&emsp;&emsp; 模式串索引加1(向后移动1位)
			pattern_index++;
		}

		/// &emsp;&emsp; **if** 模式串遍历结束 :\n
		/// &emsp;&emsp;&emsp; 目标串匹配索引为starting_index\n
		/// &emsp;&emsp;&emsp; 跳出循环\n
		if (pattern_index == pattern->length) {
			match_index = starting_index;
			break;
		}
	}

	/// ###3 返回目标串匹配索引###
	return match_index;
}


/*!
 * @brief **KMP算法求next数组**
 * @param pattern **模式串**
 * @param pattern_len **模式串长度**
 * @param next **next数组**(int二级指针)
 * @return 执行结果
 * @note
 * KMP算法求next数组
 * ----------------
 * ----------------
 * ```
 * "这不是后退, 这只是换个合适的位置, 再一次进攻"
 * ```
 * ----------------
 *
 * 求next数组的意义: 发掘模式串的内在信息, 当模式串在某个位置(i)的字符失配时, \n
 * 不再从模式串首字符重新开始匹配, 而是从位置next[i]开始
 * ###1 初始化index/starting_index/next[0]###
 * - **index**\n
 * &emsp; 模式串进行匹配的索引, 初始化为**0**\n
 * - **starting_index**\n
 * &emsp; 模式串在某个索引位置的字符失配后, 重新开始进行匹配的索引, 初始化为**-1**\n
 * - **next[0]**\n
 * &emsp; 设置为-1\n
 * ###2 递归构造next数组 ###
 * &emsp; **while** 遍历模式串 :\n
 * &emsp;&emsp; **if** starting_index != -1 (非起始字符匹配过程) :\n
 * &emsp;&emsp;&emsp; **if** pattern[index]和pattern[starting_index]相同 (此时需要进行两侧区域扩展):\n
 * &emsp;&emsp;&emsp;&emsp; index加1(向后移动1位)\n
 * &emsp;&emsp;&emsp;&emsp; starting_index加1(向后移动1位)\n
 * &emsp;&emsp;&emsp;&emsp; 更新next数组index索引位置的值为starting_index(扩展完成)\n
 * ```
 * 示例:
 * pattern[index]和pattern[starting_index], 左右两侧的相同字符串区域扩展
 *
 * a b c d 5 6 a b c d 7
 * a b   ...
 *     ^   ... a b
 *     |           ^
 *     |           |
 * starting_index  |
 *               index
 *
 * 此时:
 *  index == 8 (右侧区域遍历至索引8)
 *  starting_index == 2 (左侧区域遍历至索引2)
 *
 * 执行:
 *  判断pattern[8]是否等于pattern[2]:
 *    相同(都为'c') --> 走if( == )分支:
 *      index++ -> 9,
 *      starting_index++ -> 3
 *      更新next[index] => next[9] = 3 (如果在模式串位置9失配, 下一次匹配点直接从3开始)
 *
 * 执行结果:
 *  a b c d 5 6 a b c d 7
 *  a b c   ...
 *        ^ ... a b c
 *        |           ^
 *        |           |
 *   starting_index   |
 *                  index
 *
 * ```
 * &emsp;&emsp;&emsp; **else** (两侧区域收缩)\n
 * &emsp;&emsp;&emsp;&emsp; 令starting_index = next[starting_index]\n
 * ```
 * 示例:
 * pattern[index]和pattern[starting_index], 左右两侧的相同字符串区域扩展
 *
 * a b c d 5 6 a b c d c y b e r d a s h a b c d 5 6 a b c e
 * a b c d 5 6 a b c   ...
 *                   ^               ... a b c d 5 6 a b c
 *                   |                                     ^
 *                   |                                     |
 *             starting_index                              |
 *                                                       index
 *
 * 此时:
 *  index == 28 (右侧区域遍历至索引28)
 *  starting_index == 9 (左侧区域遍历至索引9)
 *
 * 执行:
 *  判断pattern[28]是否等于pattern[9]:
 *    不同 --> 走else分支:
 *      将next[starting_index]赋给starting_index
 *
 * 执行结果:
 * a b c d 5 6 a b c d c y b e r d a s h a b c d 5 6 a b c e
 * a b c d 5 6 a b c   ...
 *       ^           ^               ... a b c d 5 6 a b c
 *       |           |                                     ^
 *       |           |                                     |
 *  starting_index                                         |
 *                                                       index
 * ```
 * &emsp;&emsp; **else**(起始字符匹配) \n
 * &emsp;&emsp;&emsp; index加1(向后移动1位)\n
 * &emsp;&emsp;&emsp; starting_index加1(向后移动1位)\n
 * &emsp;&emsp;&emsp; 更新next数组index索引位置的值为starting_index\n
 * ```
 * 当模式串字符pattern[1]失配时, 下一趟必然从pattern[0]开始重新进行匹配,
 * 因此可确定next[1] = 0
 * 令next[0] = X; next[1] = next[0] + 1 => 得next[0] = X = -1
 * 此处逻辑可以和上面的pattern[index] == pattern[starting_index]分支逻辑做代码合并
 * ```
 */
status_t KMPNext(const char* pattern, int pattern_len, int** next) {

    // ----- 1 初始化index/starting_index/next[0] -----
	int index = 0;
	int starting_index = -1;

	(*next)[0] = starting_index;

	// ----- 2 递归构造next数组 -----
	while (index < pattern_len) {   // 遍历模式串

		if (starting_index != -1) {    // 非起始字符匹配过程
			if (pattern[index] == pattern[starting_index]) {    // 此时需要进行两侧区域扩展
                // 示例:
                // pattern[index]和pattern[starting_index], 左右两侧的相同字符串区域扩展
                //
                // a b c d 5 6 a b c d 7
                // a b
                //     ^        a b
                //     |           ^
                //     |           |
                // starting_index  |
                //               index
                //
                // 此时:
                //  index == 8 (右侧区域遍历至索引8)
                //  starting_index == 2 (左侧区域遍历至索引2)
                //
                // 执行:
                //  判断pattern[8]是否等于pattern[2]:
                //    相同(都为'c') --> 走if( == )分支:
                //      index++ -> 9,
                //      starting_index++ -> 3
                //      更新next[index] => next[9] = 3 (如果在模式串位置9失配, 下一次匹配点直接从3开始)
                //
                // 执行结果:
                //  a b c d 5 6 a b c d 7
                //  a b c
                //        ^     a b c
                //        |           ^
                //        |           |
                //   starting_index   |
                //                  index
				index++;
				starting_index++;
				(*next)[index] = starting_index;
			} else {
                // 示例:
                // pattern[index]和pattern[starting_index], 左右两侧的相同字符串区域扩展
                //
                // a b c d 5 6 a b c d c y b e r d a s h a b c d 5 6 a b c e
                // a b c d 5 6 a b c
                //                   ^                   a b c d 5 6 a b c
                //                   |                                     ^
                //                   |                                     |
                //             starting_index                              |
                //                                                       index
                //
                // 此时:
                //  index == 28 (右侧区域遍历至索引28)
                //  starting_index == 9 (左侧区域遍历至索引9)
                //
                // 执行:
                //  判断pattern[28]是否等于pattern[9]:
                //    不同 --> 走else分支:
                //      将next[starting_index]赋给starting_index
                //
                // 执行结果:
                // a b c d 5 6 a b c d c y b e r d a s h a b c d 5 6 a b c e
                // a b c d 5 6 a b c
                //       ^           ^                   a b c d 5 6 a b c
                //       |           |                                     ^
                //       |           |                                     |
                //  starting_index                                         |
                //                                                       index
				starting_index = (*next)[starting_index];
			}
		} else {    // 起始字符匹配
			index++;
			starting_index++;
			(*next)[index] = starting_index;
		}
	}

	return OK;
}


/*!
 * @brief **字符串KMP匹配**
 * @param str **目标串**
 * @param pattern **模式串**
 * @param offset **目标串偏移量**
 * @return **目标串匹配索引**
 * @note
 * 字符串KMP匹配
 * ------------
 * ------------
 * ```
 * "
 * Knuth-Morris-Pratt字符串查找算法（简称为KMP算法）,
 *
 * 由高德纳和沃恩·普拉特（英语：Vaughan Pratt）在1974年构思,
 *
 * 同年詹姆斯·H·莫里斯（英语：James H. Morris）也独立地设计出该算法,
 *
 * 最终三人于1977年联合发表
 * "
 * ```
 * ------------
 */
int StringKMPSearch(string_t* str, string_t* pattern, int offset) {

	/// ###1 分配next数组内存###
	/// &emsp; **if** 分配内存失败 :\n
	/// &emsp;&emsp; 返回NON_ALLOCATED\n
	int* next = (int*)malloc((pattern->length + 1) * sizeof(int));
	if (next == NULL) {
		return NON_ALLOCATED;
	}

	/// &emsp; memset置0\n
	memset(next, 0, sizeof(int) * (pattern->length + 1));

	/// ###2 求模式串next数组###
	/// &emsp; 调用KMPNext函数求next数组\n
	/// &emsp; **if** 调用失败 :\n
	/// &emsp;&emsp; 返回错误码\n
	status_t status = KMPNext(pattern->buffer, pattern->length, &next);
	if (status != OK) {
		return status;
	}

	/// ###3 使用next数组找模式串的匹配位置(的索引)###
	int pattern_index = 0;  // 模式串索引
	int str_index = offset; // 目标串索引

	/// &emsp; **while** 目标串和模式串中, 某个串未遍历完 :\n
	while (pattern_index < pattern->length && str_index < str->length) {
		/// &emsp;&emsp; **if** 模式串索引字符 == 目标串索引的字符\n
		/// &emsp;&emsp;&emsp; 模式串索引and目标串索引, 则向后移1位\n
		if (pattern->buffer[pattern_index] == str->buffer[str_index]) {
			pattern_index++;
			str_index++;
		}
		else {
			/// &emsp;&emsp; **else**(模式串索引字符 != 目标串索引的字符): \n
			/// &emsp;&emsp;&emsp; **if** 模式串索引0字符失配 :\n
			/// &emsp;&emsp;&emsp;&emsp; 目标串索引向后移1位\n
			if (pattern_index == 0) {
				str_index++;
			}
			else {
				/// &emsp;&emsp;&emsp; **else**(模式串索引非0字符失配) :\n
				/// &emsp;&emsp;&emsp;&emsp; 从模式串的next[pattern_index]开始执行下一趟匹配\n
				pattern_index = next[pattern_index];
			}
		}
	}

	free(next);

	int match_pos;

	///###4 求目标串匹配索引###
	///&emsp; **if** 模式串匹配索引 < 模式串长度 :\n
	///&emsp;&emsp; 目标串匹配索引为-1(没有匹配点)\n
	///&emsp; **else**\n
	///&emsp;&emsp; 目标串匹配索引为str_index - pattern_len\n
	if (pattern_index < pattern->length) {
		match_pos = -1; // 不匹配
	}
	else {
		match_pos = str_index - pattern->length; // 算出目标串中匹配的第一个字符的(在目标串中的)位置
	}

	return match_pos;
}


