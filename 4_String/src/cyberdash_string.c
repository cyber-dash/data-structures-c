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


Status StringAssign(string_t* str, const char* src_chars, int str_len) {

	if (str->buffer) {
		free(str->buffer);
	}

	if (str_len == 0) {
        str->buffer = NULL;
        str->length = 0;
        return OK;
	}

    if (!(str->buffer = (char*)malloc(str_len))) {
        return NON_ALLOCATED;
    }

    for (int i = 0; i < str_len; i++) {
        str->buffer[i] = src_chars[i];
    }

    str->length = str_len;

	return OK;
}


Status StringCopy(string_t* target_string, string_t* src_string) {
	for (int i = 0; i < StringLength(target_string) && i < StringLength(src_string); i++) {
        target_string->buffer[i] = src_string->buffer[i];
	}

    target_string->length = src_string->length;

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


Status StringClear(string_t* str) {
	if (str->buffer) {
		free(str->buffer);
        str->buffer = NULL;
	}

    str->length = 0;

	return OK;
}


Status StringConcat(string_t* target_string,
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
Status StringSubString(string_t* sub_string, string_t* src_string, int pos, int len) {
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

Status Insert(string_t *S, int pos, string_t *T)
{
	int i;

    if (pos < 1 || pos > S->length + 1) {
	    return ERROR;
    }

    if (T->length) {
	    S->buffer = (char *) realloc(S->buffer, S->length + T->length);
	    if (S->buffer == NULL) {
		    return OVERFLOW;
	    }

	    for (i = S->length - 1; i >= pos - 1; --i) {
		    S->buffer[i + T->length] = S->buffer[i];
	    }

	    for (i = 0; i < T->length; i++) {
		    S->buffer[pos + i - 1] = T->buffer[i];
	    }

	    S->length += T->length;
    }

    return OK;
}

int BruteForce(string_t *S, string_t *T, int pos)
{
    int i, j;

    i = pos;
    j = 0;

    while (i < StringLength(S) && j <= StringLength(T)) {
	    if (S->buffer[i] == T->buffer[j]) {
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

