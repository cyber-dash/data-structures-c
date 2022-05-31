//
// Created by cyberdash@163.com on 2021/12/13.
//

#ifndef CYBER_DASH_SQLIST_H
#define CYBER_DASH_SQLIST_H


#define LIST_INIT_SIZE  100
#define LISTINCRMENT    10

#define ElemType int

typedef enum Status { OK, ERROR, NON_ALLOCATED } Status;

typedef struct {
    ElemType* elem;
    int length;
    int listsize;
}SqList;


Status InitList_Sq(SqList* L);

Status ListInsert_Sq(SqList* L, int i, ElemType e);

Status ListDelete_Sq(SqList* L, int i, ElemType *e);

int LocateElem_Sq(SqList* L, ElemType e,
                  int (*compare)(ElemType, ElemType));

void MergeList_Sq(SqList* La, SqList *Lb, SqList *Lc);

void PrintList_Sq(SqList* L);


#endif // CYBER_DASH_SQLIST_H
