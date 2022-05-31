
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cyberdash_string.h"

#include "test.h"

static void inline PrintStr(HString *S)
{
	if (S == NULL || S->length <= 0) {
		return;
	}

	printf("%.*s\n", S->length, S->ch);
}

void test_StringCopy()
{
	HString T, S;

memset(&T, 0, sizeof(HString));
memset(&S, 0, sizeof(HString));

	StrAssign(&S, "hello cyberdash!");

T.ch = malloc(128);
T.length = 128;

	StrCopy(&T, &S);

	PrintStr(&T);
}

void test_StringCompare()
{
	HString S1, S2, S3, S4;

memset(&S1, 0, sizeof(HString));
memset(&S2, 0, sizeof(HString));
memset(&S3, 0, sizeof(HString));
memset(&S4, 0, sizeof(HString));

	StrAssign(&S1, "hello cyberdash");
	StrAssign(&S2, "hello cyberdash");
	StrAssign(&S3, "hello cyberdash and hello Mr. Yuan");
	StrAssign(&S4, "hi cyberdash");

	printf("S1 compare to S2: %d\n", StrCompare(&S1, &S2));
	printf("S1 compare to S3: %d\n", StrCompare(&S1, &S3));
	printf("S2 compare to S3: %d\n", StrCompare(&S2, &S3));
	printf("S1 compare to S4: %d\n", StrCompare(&S1, &S4));
}

void test_StringConCat()
{
	HString S1, S2, T;

memset(&S1, 0, sizeof(HString));
memset(&S2, 0, sizeof(HString));
memset(&T, 0, sizeof(HString));

	StrAssign(&S1, "hello cyberdash,");
	StrAssign(&S2, "hello Mr. Yuan.");

	ConCat(&T, &S1, &S2);

	PrintStr(&T);
}

void test_SubString()
{
	HString Sub, S;

memset(&S, 0, sizeof(HString));
memset(&Sub, 0, sizeof(HString));

	StrAssign(&S, "hello cyberdash,");

	SubString(&Sub, &S, 7, 9);

	PrintStr(&Sub);
}

void test_Insert()
{
	HString S, T;

memset(&S, 0, sizeof(HString));
memset(&T, 0, sizeof(HString));

	StrAssign(&S, "hello dash");
	StrAssign(&T, "cyber");

	Insert(&S, 7, &T);

	PrintStr(&S);
}

void test_Index()
{
	HString S, T;

memset(&S, 0, sizeof(HString));
memset(&T, 0, sizeof(HString));

	StrAssign(&S, "hello cyberdash");
	StrAssign(&T, "cyberdash");

	printf("S: ");
	PrintStr(&S);
	printf("T: ");
	PrintStr(&T);

	printf("index: %d\n", Index(&S, &T, 2));
	printf("index find by kmp: %d\n", Index_KMP(&S, &T, 2));
}


