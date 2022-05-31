/*!
 * Created by cyberdash@163.com on 2021/12/13.
 */

#ifndef CYBER_DASH_STRING_H
#define CYBER_DASH_STRING_H

typedef enum Status { OK, ERROR, OVERFLOW } Status;

typedef struct {
    char *ch;
    int length;
} HString;

Status StrAssign(HString *T, char *chars);

int StrLength(HString *T);

int StrCompare(HString *S, HString *T);

Status ClearString(HString *S);

Status ConCat(HString *T, HString *S1, HString *S2);

Status SubString(HString *Sub, HString *S, int pos, int len);

int Index(HString *S, HString *T, int pos);

int Index_KMP(HString *S, HString *T, int pos);

Status StrCopy(HString *T, HString *S);

int StrEmpty(HString *S);

Status Insert(HString *S, int pos, HString *T);

#endif //CYBER_DASH_STRING_H
