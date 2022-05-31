
#include <string.h>
#include <malloc.h>
#include "cyberdash_string.h"

Status StrAssign(HString *T, char *chars)
{
	int i, len = 0;

	if (T->ch) {
		free(T->ch);
	}

	for (len = 0; *(chars + len) != '\0'; ++len);

	if (len == 0) {
		T->ch = NULL;
		T->length = 0;
	} else {
		if (!(T->ch = (char *) malloc(len))) {
			return OVERFLOW;
		}

		for (i = 0; i < len; i++) {
			T->ch[i] = chars[i];
		}

		T->length = len;
	}

	return OK;
}


Status StrCopy(HString *T, HString *S)
{
	int i = 0;

	while (i < StrLength(T) && i < StrLength(S)) {
		T->ch[i] = S->ch[i];
		i++;
	}

	T->length = S->length;

	return OK;
}

int StrEmpty(HString *S)
{
	return S->length == 0;
}

int StrCompare(HString *S, HString *T)
{
	int i = 0;

	for (i = 0; i < S->length && i < T->length; i++) {
		if (S->ch[i] != T->ch[i]) {
			return S->ch[i] - T->ch[i];
		}
	}

	return S->length - T->length;
}

int StrLength(HString *S)
{
	return S->length;
}

Status ClearString(HString *S)
{
	if (S->ch) {
		free(S->ch);
		S->ch = NULL;
	}

	S->length = 0;

	return OK;
}

Status ConCat(HString *T, HString *S1, HString *S2)
{
	int i;

	if (T->ch) {
		free(T->ch);
	}

	if (!(T->ch = (char *) malloc(S1->length + S2->length))) {
		return OVERFLOW;
	}

	for (i = 0; i < S1->length; i++) {
		T->ch[i] = S1->ch[i];
	}

	for (i = 0; i < S2->length; i++) {
		T->ch[S1->length + i] = S2->ch[i];
	}

	T->length = S1->length + S2->length;

	return OK;
}

Status SubString(HString *Sub, HString *S, int pos, int len)
{
	int i;

	if (pos < 1 || pos >= S->length || len < 0 || len > S->length - pos + 1) {
		return ERROR;
	}

	if (Sub->ch) {
		free(Sub->ch);
	}

	if (len == 0) {
		Sub->ch = NULL;
		Sub->length = 0;
	} else {
		Sub->ch = (char *) malloc(len);
		if (Sub->ch == NULL) {
			return OVERFLOW;
		}

		for (i = 0; i <= len; i++) {
			Sub->ch[i] = S->ch[pos + i - 1];
		}

		Sub->length = len;
	}

	return OK;
}

Status Insert(HString *S, int pos, HString *T)
{
	int i;

    if (pos < 1 || pos > S->length + 1) {
	    return ERROR;
    }

    if (T->length) {
	    S->ch = (char *) realloc(S->ch, S->length + T->length);
	    if (S->ch == NULL) {
		    return OVERFLOW;
	    }

	    for (i = S->length - 1; i >= pos - 1; --i) {
		    S->ch[i + T->length] = S->ch[i];
	    }

	    for (i = 0; i < T->length; i++) {
		    S->ch[pos + i - 1] = T->ch[i];
	    }

	    S->length += T->length;
    }

    return OK;
}

int Index(HString *S, HString *T, int pos)
{
    int i, j;

    i = pos;
    j = 0;

    while (i < StrLength(S) && j <= StrLength(T)) {
	    if (S->ch[i] == T->ch[j]) {
		    i++; j++;
	    } else {
		    i = i - j + 1;
		    j = 0;
	    }
    }

    if (j <= StrLength(T)) {
	    return i - StrLength(T);
    }

    return 0;
}

static void get_next(HString *T, int next[])
{
	int i = 1;
	int j = 0;

	next[1] = 0;

	while (i < StrLength(T)) {
		if (j == 0 || T->ch[i] == T->ch[j]) {
			i++; j++;
			if (T->ch[i] != T->ch[j]) {
				next[i] = j;
			} else {
				next[i] = next[j];
			}
		} else {
			j = next[j];
		}
	}
}

int Index_KMP(HString *S, HString *T, int pos)
{
	int i = pos, j = 0;
	int *next = malloc(StrLength(T));

	get_next(T, next);

	while (i < StrLength(S) && j <= StrLength(T)) {
		if (j == 0 || S->ch[i] == T->ch[j]) {
			i++;
			j++;
		} else {
			j = next[j];
		}
	}

	if (j <= StrLength(T)) {
		return i - StrLength(T);
	}

	return 0;
}

