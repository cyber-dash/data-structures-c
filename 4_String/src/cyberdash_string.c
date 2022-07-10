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
#include "cyberdash_string.h"


Status StringAssign(cyber_dash_string_t* cyber_dash_string, char* src_str, unsigned int str_len) {

	if (cyber_dash_string->str) {
		free(cyber_dash_string->str);
	}

	if (str_len == 0) {
        cyber_dash_string->str = NULL;
        cyber_dash_string->length = 0;
        return OK;
	}

    if (!(cyber_dash_string->str = (char*)malloc(str_len))) {
        return NON_ALLOCATED;
    }

    for (int i = 0; i < str_len; i++) {
        cyber_dash_string->str[i] = src_str[i];
    }

    cyber_dash_string->length = str_len;

	return OK;
}


Status StringCopy(cyber_dash_string_t* target_string, cyber_dash_string_t* src_string) {
	for (int i = 0; i < StringLength(target_string) && i < StringLength(src_string); i++) {
        target_string->str[i] = src_string->str[i];
	}

    target_string->length = src_string->length;

	return OK;
}


int StringEmpty(cyber_dash_string_t* cyber_dash_string) {
	return cyber_dash_string->length == 0;
}


int StringCompare(cyber_dash_string_t* string1, cyber_dash_string_t* string2) {
	for (int i = 0; i < string1->length && i < string2->length; i++) {
		if (string1->str[i] != string2->str[i]) {
			return string1->str[i] - string2->str[i];
		}
	}

	return string1->length - string2->length;
}


int StringLength(cyber_dash_string_t* cyber_dash_string) {
	return cyber_dash_string->length;
}


Status StringClear(cyber_dash_string_t* cyber_dash_string) {
	if (cyber_dash_string->str) {
		free(cyber_dash_string->str);
        cyber_dash_string->str = NULL;
	}

    cyber_dash_string->length = 0;

	return OK;
}


Status StringConcat(cyber_dash_string_t* target_string,
                    cyber_dash_string_t* src_string1,
                    cyber_dash_string_t* src_string2)
{
	if (target_string->str) {
		free(target_string->str);
	}

	if (!(target_string->str = (char *) malloc(src_string1->length + src_string2->length))) {
		return OVERFLOW;
	}

	for (int i = 0; i < src_string1->length; i++) {
        target_string->str[i] = src_string1->str[i];
	}

	for (int i = 0; i < src_string2->length; i++) {
        target_string->str[src_string1->length + i] = src_string2->str[i];
	}

    target_string->length = src_string1->length + src_string2->length;

	return OK;
}


// todo:
Status StringSubString(cyber_dash_string_t* sub_string, cyber_dash_string_t* src_string, int pos, int len) {
	int i;

	if (pos < 1 || pos >= src_string->length || len < 0 || len > src_string->length - pos + 1) {
		return ERROR;
	}

	if (sub_string->str) {
		free(sub_string->str);
	}

	if (len == 0) {
        sub_string->str = NULL;
        sub_string->length = 0;
	} else {
        sub_string->str = (char *) malloc(len);
		if (sub_string->str == NULL) {
			return OVERFLOW;
		}

		for (i = 0; i <= len; i++) {
            sub_string->str[i] = src_string->str[pos + i - 1];
		}

        sub_string->length = len;
	}

	return OK;
}

Status Insert(cyber_dash_string_t *S, int pos, cyber_dash_string_t *T)
{
	int i;

    if (pos < 1 || pos > S->length + 1) {
	    return ERROR;
    }

    if (T->length) {
	    S->str = (char *) realloc(S->str, S->length + T->length);
	    if (S->str == NULL) {
		    return OVERFLOW;
	    }

	    for (i = S->length - 1; i >= pos - 1; --i) {
		    S->str[i + T->length] = S->str[i];
	    }

	    for (i = 0; i < T->length; i++) {
		    S->str[pos + i - 1] = T->str[i];
	    }

	    S->length += T->length;
    }

    return OK;
}

int BruteForce(cyber_dash_string_t *S, cyber_dash_string_t *T, int pos)
{
    int i, j;

    i = pos;
    j = 0;

    while (i < StringLength(S) && j <= StringLength(T)) {
	    if (S->str[i] == T->str[j]) {
		    i++; j++;
	    } else {
		    i = i - j + 1;
		    j = 0;
	    }
    }

    if (j <= StringLength(T)) {
	    return i - StringLength(T);
    }

    return 0;
}

static void get_next(cyber_dash_string_t *T, int next[])
{
	int i = 1;
	int j = 0;

	next[1] = 0;

	while (i < StringLength(T)) {
		if (j == 0 || T->str[i] == T->str[j]) {
			i++;
            j++;
			if (T->str[i] != T->str[j]) {
				next[i] = j;
			} else {
				next[i] = next[j];
			}
		} else {
			j = next[j];
		}
	}
}


int KMP(cyber_dash_string_t *S, cyber_dash_string_t *T, int pos)
{
	int i = pos, j = 0;
	int* next = malloc(StringLength(T));

	get_next(T, next);

	while (i < StringLength(S) && j <= StringLength(T)) {
		if (j == 0 || S->str[i] == T->str[j]) {
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

