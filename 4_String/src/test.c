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


static void inline PrintStr(cyber_dash_string_t* cyber_dash_string) {
	if (cyber_dash_string == NULL || cyber_dash_string->length <= 0) {
		return;
	}

	printf("%.*s\n", cyber_dash_string->length, cyber_dash_string->str);
}


void test_StringCopy() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                      Test StringCopy                      |\n");
    printf("|                        测试字符串复制                       |\n");

	cyber_dash_string_t T = { .str = NULL, .length = 0};
    cyber_dash_string_t S = { .str = NULL, .length = 0};

    // char str[50] = "hello cyberdash!";
    char str[50] = "你好";
    StringAssign(&S, str, strlen(str));

    T.str = malloc(128);
    T.length = 128;

    StringCopy(&T, &S);

	PrintStr(&T);

    printf("|-----------------------------------------------------------|\n\n");
}


void test_StringCompare() {
    printf("\n");
    printf("|------------------------ CyberDash ------------------------|\n");
    printf("|                    Test StringCompare                      |\n");
    printf("|                        测试字符串比较                       |\n");

	cyber_dash_string_t S1 = { .str = NULL, .length = 0};
    cyber_dash_string_t S2 = { .str = NULL, .length = 0};
    cyber_dash_string_t S3 = { .str = NULL, .length = 0};
    cyber_dash_string_t S4 = { .str = NULL, .length = 0};

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
	cyber_dash_string_t S1, S2, T;

    memset(&S1, 0, sizeof(cyber_dash_string_t));
    memset(&S2, 0, sizeof(cyber_dash_string_t));
    memset(&T, 0, sizeof(cyber_dash_string_t));

    char str1[50] = "hello cyberdash,";
    char str2[50] = "hello Mr. Yuan.";
    StringAssign(&S1, str1, strlen(str1));
    StringAssign(&S2, str2, strlen(str2));

    StringConcat(&T, &S1, &S2);

	PrintStr(&T);
}


void test_SubString() {
	cyber_dash_string_t Sub, S;

    memset(&S, 0, sizeof(cyber_dash_string_t));
    memset(&Sub, 0, sizeof(cyber_dash_string_t));

    char str[50] = "hello cyberdash,";
    StringAssign(&S, str, strlen(str));

    StringSubString(&Sub, &S, 7, 9);

	PrintStr(&Sub);
}


void test_Insert() {
	cyber_dash_string_t S, T;

    memset(&S, 0, sizeof(cyber_dash_string_t));
    memset(&T, 0, sizeof(cyber_dash_string_t));

    char str1[50] = "hello dash";
    char str2[50] = "cyber";
    StringAssign(&S, str1, strlen(str1));
    StringAssign(&T, str2, strlen(str2));

	Insert(&S, 7, &T);

	PrintStr(&S);
}


void test_Index() {
	cyber_dash_string_t S, T;

    memset(&S, 0, sizeof(cyber_dash_string_t));
    memset(&T, 0, sizeof(cyber_dash_string_t));

    char str1[50] = "hello cyberdash";
    char str2[50] = "cyberdash";
    StringAssign(&S, str1, strlen(str1));
    StringAssign(&T, str2, strlen(str2));

	printf("S: ");
	PrintStr(&S);
	printf("T: ");
	PrintStr(&T);

	printf("index: %d\n", BruteForce(&S, &T, 2));
	printf("index find by kmp: %d\n", KMP(&S, &T, 2));
}
