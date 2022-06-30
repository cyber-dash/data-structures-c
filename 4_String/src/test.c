#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cyberdash_string.h"

#include "test.h"


static void inline PrintStr(cyber_dash_string_t *S) {
	if (S == NULL || S->length <= 0) {
		return;
	}

	printf("%.*s\n", S->length, S->str);
}


void test_StringCopy() {
	cyber_dash_string_t T, S;

    memset(&T, 0, sizeof(cyber_dash_string_t));
    memset(&S, 0, sizeof(cyber_dash_string_t));

    char str[50] = "hello cyberdash!";
    StringAssign(&S, str, strlen(str));

    T.str = malloc(128);
    T.length = 128;

    StringCopy(&T, &S);

	PrintStr(&T);
}


void test_StringCompare() {
	cyber_dash_string_t S1, S2, S3, S4;

    memset(&S1, 0, sizeof(cyber_dash_string_t));
    memset(&S2, 0, sizeof(cyber_dash_string_t));
    memset(&S3, 0, sizeof(cyber_dash_string_t));
    memset(&S4, 0, sizeof(cyber_dash_string_t));

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
