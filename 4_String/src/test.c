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


static void inline PrintStr(string_t* cyber_dash_string) {
	if (cyber_dash_string == NULL || cyber_dash_string->length <= 0) {
		return;
	}

	printf("%.*s\n", cyber_dash_string->length, cyber_dash_string->buffer);
}


void test_StringCopy() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                      Test StringCopy                      |\n");
    printf("|                        测试字符串复制                       |\n");

	string_t dest_str = { .buffer = NULL, .length = 0};
    string_t src_str = { .buffer = NULL, .length = 0};

    // char buffer[50] = "hello cyberdash!";
    char str[50] = "你好";
    StringAssign(&src_str, str, strlen(str));

    dest_str.buffer = malloc(128);
    dest_str.length = 128;

    StringCopy(&dest_str, &src_str);

	PrintStr(&dest_str);

    printf("|-----------------------------------------------------------|\n\n");
}


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


void test_StringConCat() {
	string_t S1, S2, T;

    memset(&S1, 0, sizeof(string_t));
    memset(&S2, 0, sizeof(string_t));
    memset(&T, 0, sizeof(string_t));

    char str1[50] = "hello cyberdash,";
    char str2[50] = "hello Mr. Yuan.";
    StringAssign(&S1, str1, strlen(str1));
    StringAssign(&S2, str2, strlen(str2));

    StringConcat(&T, &S1, &S2);

	PrintStr(&T);
}


void test_SubString() {
	string_t Sub, S;

    memset(&S, 0, sizeof(string_t));
    memset(&Sub, 0, sizeof(string_t));

    char str[50] = "hello cyberdash,";
    StringAssign(&S, str, strlen(str));

    StringSubString(&Sub, &S, 7, 9);

	PrintStr(&Sub);
}


void TestStringInsert() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                    Test StringCompare                     |\n");
    printf("|                        测试字符串比较                       |\n");

	string_t str;
    string_t insert_str;

    memset(&str, 0, sizeof(string_t));
    memset(&insert_str, 0, sizeof(string_t));

    char str1[50] = "Hello Dash";
    char str2[50] = "Cyber";

    StringAssign(&str, str1, strlen(str1));
    StringAssign(&insert_str, str2, strlen(str2));

	Insert(&str, 6, &insert_str);

	PrintStr(&str);

    printf("|-----------------------------------------------------------|\n\n");
}


void TestStringSearch() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                 Test StringSearch BF & KMP                |\n");
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
	PrintStr(&str);
	printf("pattern: ");
	PrintStr(&pattern);

	printf("index: %d\n", BruteForce(&str, &pattern, 2));
	printf("index find by kmp: %d\n", KMP(&str, &pattern, 2));

    printf("|-----------------------------------------------------------|\n\n");
}
