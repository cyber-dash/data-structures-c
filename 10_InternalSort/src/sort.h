//
// Created by cyberdash@163.com(抖音: cyberdash_yuan) on 2021/3/10.
//

#ifndef CYBER_DASH_SORT_H
#define CYBER_DASH_SORT_H


/*----顺序链表的数据类型----*/
# define MAXSIZE 20     // 顺序表的最大长度


typedef int KeyType;    //定义关键字类型为整数类型
typedef char InfoType;  //其他数据类型

typedef struct {
    KeyType key;        //关键字项
    InfoType otherinfo; //其他数据项
}RedType;// Red or Rcd?

typedef struct {
    KeyType key;        //关键字项
    InfoType otherinfo; //其他数据项
} seq_list_node_t;

typedef struct {
    RedType r[MAXSIZE + 1]; // r[0]闲置或用作哨兵单元
    int length;         //顺序表长度
} seq_list_t;
/*----顺序链表的数据类型----*/


/*----静态链表的数据类型----*/
# define MAX 100       //静态链表容量
# define SIZE 100       //静态链表容量
typedef struct
{
    seq_list_node_t rc;         //记录项
    int next;           //指针项
}SLNode;                //表结点类型

typedef struct
{
    SLNode r[SIZE];     //0号单元为表头结点
    int length;         //链表当前长度
}SLinkListType;         //静态链表类型
/*----静态链表的数据类型----*/


typedef seq_list_t HeapType; // 堆采用顺序表存储表示

/*----基数排序链表的数据类型----*/
#define MAX_NUM_OF_KEY 8          //关键字项数的最大值 
#define RADIX 10              //关键字基数，此时是十进制整数的基数 
#define MAX_SPACE 10000

typedef char KeysType;

typedef struct
{
    KeysType keys[MAX_NUM_OF_KEY];      //关键字 
    InfoType otherinfo;                 //其他数据项
    int next;
}static_linked_list_node_t;                                // 静态链表的结点类型

typedef struct
{
    static_linked_list_node_t r[MAX_SPACE];                //静态链表的可利用空间，r[0]为头结点
    int key_cnt;                         //记录的当前关键字个数
    int length;                         //静态链表当前长度
} static_linked_list_t;                                //静态链表类型

typedef int ArrType[RADIX];             //指针数组类型 

/*----基数排序链表的数据类型----*/


void InsertSort(seq_list_t* L);

void BInsertSort(seq_list_t* list);

void TInsertSort(SLinkListType* L);

void ShellInsert(seq_list_t* L, int dk);

void ShellSort(seq_list_t* L, int dlta[], int t);

void SelectSort(seq_list_t* L);

void BubbleSort(seq_list_t* L);

void QuickSort(seq_list_t* L);

void HeapSort(HeapType* H);

void MergeSort(seq_list_t* L);

void RadixSort(static_linked_list_t* L);

#endif //CYBER_DASH_SORT_H
