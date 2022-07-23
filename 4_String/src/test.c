/*!
 * @file test.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  串 测试用例
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdio.h>
#include <stdlib.h>
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
 * @brief 测试字符串复制
 * @note
 */
void TestStringCopy() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                      Test StringCopy                      |\n");
    printf("|                        测试字符串复制                       |\n");

	string_t dest_str = { .buffer = NULL, .length = 0};
    string_t src_str = { .buffer = NULL, .length = 0};

    char buffer[50] = "hello cyberdash!";
    StringAssign(&src_str, buffer, strlen(buffer));

    dest_str.buffer = malloc(128);
    dest_str.length = 128;

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

	string_t S1 = { .buffer = NULL, .length = 0};
    string_t S2 = { .buffer = NULL, .length = 0};
    string_t S3 = { .buffer = NULL, .length = 0};
    string_t S4 = { .buffer = NULL, .length = 0};

    char str1[50] = "hello cyberdash!";
    char str2[50] = "hello cyberdash!";
    char str3[50] = "hello cyberdash and hello Mr. Yuan";
    char str4[50] = "hi cyberdash";

    StringAssign(&S1, str1, strlen(str1));
    StringAssign(&S2, str2, strlen(str2));
    StringAssign(&S3, str3, strlen(str3));
    StringAssign(&S4, str4, strlen(str4));

	printf("S1 compare to S2: %d\n", StringCompare(&S1, &S2));
	printf("S1 compare to S3: %d\n", StringCompare(&S1, &S3));
	printf("S2 compare to S3: %d\n", StringCompare(&S2, &S3));
	printf("S1 compare to S4: %d\n", StringCompare(&S1, &S4));

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

	string_t str1;
    string_t str2;
    string_t resulting_str;

    memset(&str1, 0, sizeof(string_t));
    memset(&str2, 0, sizeof(string_t));
    memset(&resulting_str, 0, sizeof(string_t));

    char chars1[50] = "hello cyberdash,";
    char chars2[50] = "hello Mr. Yuan.";
    StringAssign(&str1, chars1, strlen(chars1));
    StringAssign(&str2, chars2, strlen(chars2));

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

    char chars[50] = "hello cyberdash,";
    StringAssign(&str, chars, strlen(chars));

    int offset = 6;
    int sub_str_len = 9;

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

    //###1 初始化字符串&待插入字符串 ###
	string_t str;
    string_t insert_str;

    memset(&str, 0, sizeof(string_t));
    memset(&insert_str, 0, sizeof(string_t));

    char chars[50] = "Hello Dash";
    char insert_chars[50] = "Cyber";

    StringAssign(&str, chars, strlen(chars));
    StringAssign(&insert_str, insert_chars, strlen(insert_chars));

    // ###2 调用StringInsert执行插入###
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

    char str_chars[50] = "123 cyberdash 456";
    char pattern_chars[50] = "cyberdash";

    StringAssign(&str, str_chars, strlen(str_chars));
    StringAssign(&pattern, pattern_chars, strlen(pattern_chars));

	printf("str: ");
    StringPrint(&str);
	printf("pattern: ");
    StringPrint(&pattern);

	printf("index: %d\n", StringBruteForceSearch(&str, &pattern, 2));
	printf("index find by kmp: %d\n", StringKMPSearch(&str, &pattern, 2));

    printf("|-----------------------------------------------------------|\n\n");
}
