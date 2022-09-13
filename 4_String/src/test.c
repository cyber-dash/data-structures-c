/*!
 * @file test.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 字符串测试源文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdio.h>
#include <string.h>
#include "cyberdash_string.h"
#include "test.h"


/*!
 * <h1>字符串打印</h1>
 * @param str 字符串
 * @note
 */
static void inline StringPrint(string_t* str) {
    /// ###1 空字符串处理###
    /// &emsp; 直接返回
	if (str == NULL || str->length <= 0) {
		return;
	}

    /// ### 2 调用printf ###
	printf("%.*s\n", str->length, str->buffer);
}


/*!
 * @brief <h1>测试字符串复制</h1>
 * @note
 */
void TestStringCopy() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                      Test StringCopy                      |\n");
    printf("|                        测试字符串复制                       |\n");

    /// ###1 被复制串和复制串初始化###
	string_t dest_str = { .buffer = NULL, .length = 0};
    string_t src_str = { .buffer = NULL, .length = 0};

    /// &emsp; 被复制串"Hello cyberdash!"
    char chars[50] = "Hello cyberdash!";
    StringAssign(&src_str, chars, (int)strlen(chars));

    /// ###2 执行复制###
    StringCopy(&dest_str, &src_str);

    StringPrint(&dest_str);

    printf("|-----------------------------------------------------------|\n\n");
}


/*!
 * @brief <h1>测试字符串比较</h1>
 * @note
 */
void TestStringCompare() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                    Test StringCompare                      |\n");
    printf("|                        测试字符串比较                       |\n");

    /// ###1 初始化4个字符串###
	string_t str1 = { .buffer = NULL, .length = 0};
    string_t str2 = { .buffer = NULL, .length = 0};
    string_t str3 = { .buffer = NULL, .length = 0};
    string_t str4 = { .buffer = NULL, .length = 0};

    char chars1[50] = "Hello cyberdash!";
    char chars2[50] = "Hello cyberdash!";
    char chars3[50] = "Hello cyberdash and hello Mr. Yuan";
    char chars4[50] = "Hi cyberdash";

    StringAssign(&str1, chars1, (int)strlen(chars1));
    StringAssign(&str2, chars2, (int)strlen(chars2));
    StringAssign(&str3, chars3, (int)strlen(chars3));
    StringAssign(&str4, chars4, (int)strlen(chars4));

    /// ###2 做比较并打印结果###
	printf("str1 compare to str2: %d\n", StringCompare(&str1, &str2));
	printf("str1 compare to str3: %d\n", StringCompare(&str1, &str3));
	printf("str2 compare to str3: %d\n", StringCompare(&str2, &str3));
	printf("str1 compare to str4: %d\n", StringCompare(&str1, &str4));

    printf("|-----------------------------------------------------------|\n\n");
}


/*!
 * @brief <h1>测试字符串拼接</h1>
 * @note
 */
void TestStringConcat() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                     Test StringConcat                     |\n");
    printf("|                        测试字符串拼接                       |\n");

    /// ###1 初始化2个字符串###
	string_t str1;
    string_t str2;
    string_t resulting_str;

    memset(&str1, 0, sizeof(string_t));
    memset(&str2, 0, sizeof(string_t));
    memset(&resulting_str, 0, sizeof(string_t));

    char chars1[50] = "hello cyberdash,";
    char chars2[50] = "hello Mr. Yuan.";
    StringAssign(&str1, chars1, (int)strlen(chars1));
    StringAssign(&str2, chars2, (int)strlen(chars2));

    /// ###2 执行拼接###
    StringConcat(&resulting_str, &str1, &str2);

    StringPrint(&resulting_str);

    printf("|-----------------------------------------------------------|\n\n");
}


/*!
 * @brief <h1>测试字符串子串</h1>
 * @note
 */
void TestStringSubStr() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                     Test StringSubStr                     |\n");
    printf("|                        测试字符串子串                       |\n");

	string_t sub_str;
    string_t str;

    memset(&str, 0, sizeof(string_t));
    memset(&sub_str, 0, sizeof(string_t));

    /// ###1 初始化字符串###
    /// &emsp; "hello cyberdash,"
    char chars[50] = "hello cyberdash,";
    StringAssign(&str, chars, (int)strlen(chars));

    int offset = 6;
    int sub_str_len = 9;

    /// ###2 求子串###
    /// &emsp; 原始字符串偏移量6, 子串长度9
    StringSubStr(&str, &sub_str, offset, sub_str_len);

    StringPrint(&sub_str);

    printf("|-----------------------------------------------------------|\n\n");
}


/*!
 * @brief <h1>测试字符串插入</h1>
 * @note
 */
void TestStringInsert() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                     Test StringInsert                     |\n");
    printf("|                        测试字符串插入                       |\n");

    /// ###1 初始化字符串&待插入字符串 ###
	string_t str;
    string_t insert_str;

    memset(&str, 0, sizeof(string_t));
    memset(&insert_str, 0, sizeof(string_t));

    char chars[50] = "Hello Dash";
    char insert_chars[50] = "Cyber";

    printf("插入\"%s\"到\"%s\"中间:\n\n", insert_chars, chars);

    StringAssign(&str, chars, (int)strlen(chars));
    StringAssign(&insert_str, insert_chars, (int)strlen(insert_chars));

    /// ###2 调用StringInsert执行插入###
    StringInsert(&str, 6, &insert_str);

    StringPrint(&str);

    printf("|-----------------------------------------------------------|\n\n");
}


/*!
 * @brief <h1>测试字符串匹配(BF算法 & KMP算法)</h1>
 * @note
 */
void TestStringSearch() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|            Test StringSearch BF & StringKMPSearch         |\n");
    printf("|                   测试字符串搜索BF & KMP算法                 |\n");

	string_t str;
    string_t pattern;

    memset(&str, 0, sizeof(string_t));
    memset(&pattern, 0, sizeof(string_t));

    /// ###1 初始化目标串和模式串###
    /// &emsp; 目标串: "123 cyberdash cyber 456"\n
    /// &emsp; 模式串: "cyberdash cyber"\n
    char str_chars[50] = "123 cyberdash cyber 456";
    char pattern_chars[50] = "cyberdash cyber";

    StringAssign(&str, str_chars, (int)strlen(str_chars));
    StringAssign(&pattern, pattern_chars, (int)strlen(pattern_chars));

	printf("目标串: ");
    StringPrint(&str);
	printf("模式串: ");
    StringPrint(&pattern);

    /// ###2 使用BF和KMP进行匹配###
    /// - BF匹配, 目标串偏移量2\n
    /// - KMP匹配, 目标串偏移量2\n
	printf("BF算法查找匹配索引: %d\n", StringBruteForceSearch(&str, &pattern, 2));
	printf("KMP算法查找匹配索引: %d\n", StringKMPSearch(&str, &pattern, 2));

    printf("|-----------------------------------------------------------|\n\n");
}
