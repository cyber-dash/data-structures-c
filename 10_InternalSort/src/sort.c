//
// Created by cyberdash@163.com(抖音: cyberdash_yuan) on 2021/3/10.
//

#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include<stdbool.h>


/*!
 * 小于
 * @param key1
 * @param key2
 * @return
 */
int LowerThan(KeyType key1, KeyType key2) {
    if (key1 < key2) {
        return 1;
    }

    return 0;
}


int LowerEqual(KeyType key1, KeyType key2) {
    if (key1 <= key2) {
        return 1;
    }

    return 0;
}


void swap(RedType* item1, RedType* item2) {

    RedType tmp = *item1;
    *item1 = *item2;
    *item2 = tmp;
}


//在L.r[i..L.Length]中选择key最小的记录
int SelectMinKey(seq_list_t* L, int i) {
    if (i == L->length) {
        return i;
    }

    int minPos = i;
    KeyType minValue = L->r[i].key;
    for (int j = i + 1; j <= L->length; j++) {
        if (L->r[j].key < minValue) {
            minPos = j;
            minValue = L->r[j].key;
        }
    }

    return minPos;
}


/*!
 * @brief 直接插入排序
 * @param L 待排数组
 */
void InsertSort(seq_list_t* L)
{
    //对顺序表L作直接插入排序
    for (int i = 2; i <= L->length; ++i)
    {
        if (LowerThan(L->r[i].key, L->r[i - 1].key)) { // ("<"，需将L.r[i]插入有序子表)

            // 交换 L->r[i]与L->r[i - 1]
            L->r[0] = L->r[i];                  // (复制为哨兵)
            L->r[i] = L->r[i - 1];

            int j;
            for (j = i - 1; LowerThan(L->r[0].key, L->r[j].key); --j)
            {
                L->r[j + 1] = L->r[j];                //记录后移
            }
            L->r[j + 1] = L->r[0];                  //插入到正确位置
        }
    }
} // InsertSort


// @brief 折半插入排序
// @param list 待排数组
void BInsertSort(seq_list_t* list)
{
    for (int i = 2; i <= list->length; ++i)
    {
        list->r[0] = list->r[i];                        //将L->r[i]暂存到L->r[0]

        int low = 1;
        int high = i - 1;

        while (low <= high)
        {                                             //在r[low..high]中折半查找有序插入的位置
            int m = (low + high) / 2;                       //折半

            if (LowerThan(list->r[0].key, list->r[m].key)) {
                high = m - 1;                             //插入点在低半区
            } else {
                low = m + 1;                              //插入点在高半区
            }
        }

        for (int j = i - 1; j >= high + 1; --j) {
            list->r[j + 1] = list->r[j];                  //记录后移
        }
        list->r[high + 1] = list->r[0];                 //插入
    }
} // BInsertSort


/*
// @brief 2-路插入排序
// @param SL 待排数组
void TwoInsertSort(SLinkListType *SL){

}
*/


// @brief 表插入排序
// @param SL 待排数组
void TableInsertSort(SLinkListType *SL)
{
  SL->r[0].rc.key = MAX;                          //0号位表头结点，存最大整数值MAX
  SL->r[0].next = 1;
  SL->r[1].next = 0;

  int i = 0, q = 0, p = 0;
  for(i=2; i<=SL->length; i++){
    q = 0;
    p = SL->r[q].next;
    while(LowerEqual(SL->r[p].rc.key, SL->r[i].rc.key)){
      q = p;
      p = SL->r[q].next;
    }
    SL->r[q].next = i;
    SL->r[i].next = p;
  }
}//TableInsertSort

// @brief 重排记录过程
// @param SL 待排数组
void Arrange(SLinkListType *SL)
{
  int q = 0;
  int i = 0;
  //根据静态链表SL中各结点的指针值调整记录位置，使得SL中记录按关键字非递减
  //减有序排列
  int p = SL->r[0].next;                          //p指示第一个记录的当前位置

  for(i = 1; i < SL->length; ++i){                //SL.r[1..i-1]中记录已按关键字有序排列
                                                  //第i个记录的在SL中的当前位置应不小于i
    while(p < i){
      p = SL->r[p].next;                          //找到第i个记录，并用p指示其在SL中当前位置
    }
    q = SL->r[p].next;                            //q指示尚未调整的表尾
    if(p != i){
      swap(&SL->r[p], &SL->r[i], sizeof(SL->r[p]));//交换记录,使第i个记录到位
      SL->r[i].next = p;                          //指向被移走的记录,使得以后可由while循环找回
    }
    p = q;                                        //p指示尚未调整的表尾,为找第i+1个记录作准备
  }
}//Arrange


// @brief 希尔插入排序
// @param L 待排数组
// @param SL 增量
void ShellInsert(seq_list_t *L, int dk)
{
  //对顺序表L作一趟希尔插入排序，本算法是和一趟直接插入排序相比，作了以下修改：
  //    1，前后记录位置的增量是dk，而不是1；
  //    2，r[0]只是暂存单元，不是哨兵。当j<=0时，插入位置已找到。
  for (int i = dk + 1; i <= L->length; ++i)
  {
    if (LowerThan(L->r[i].key, L->r[i - dk].key))    //需将L.r[i]插入有序增量子表
    {
      L->r[0] = L->r[i];                      //暂存在L.r[0]
      int j;
      for (j = i - dk; j > 0 && LowerThan(L->r[0].key, L->r[j].key); j -= dk)
      {
        L->r[j + dk] = L->r[j];               //记录后移，查找插入位置
      }
      L->r[j + dk] = L->r[0];                 //插入
    }
  }
}// ShellInsert


// @brief 希尔排序
// @param L 待排数组
// @param dlta 排序增量序列
// @param t 序列长度
void ShellSort(seq_list_t *L, int dlta[], int t)
{
  int k;
  // 按增量序列dlta[0..t-1]对顺序表L作希尔排序。
  for (k = 0; k < t; ++k)
  {
    ShellInsert(L, dlta[k]);                    //一趟增量为dlta[k]的插入排序
  }
} // ShellSort


 // @brief 起泡排序(冒泡排序)
 // @param L 待排数组
void BubbleSort(seq_list_t* L)
{
    int i;
    int j;
    RedType tmp;
    bool status;
    for (i = 0; i < L->length; ++i)
    {
        status = true;
        for (j = 0; j < L->length - i - 1; j++)
        {
            if (LowerThan(L->r[j + 1].key, L->r[j].key))
            {
                swap(&(L->r[j + 1]), &(L->r[j]));
                status = false;
            }
        }
        if (status)
        {
            break;
        }
    }
} // BubbleSort


// @brief 快排 获取枢纽位置 算法10.6a 改良前
// @param L 待排数组
// @param low 表左端
// @param high 表右端
// @return 新的枢纽位置
int Partition_a(seq_list_t* L, int low, int high) {
    int pivotkey;

    //变换顺序表L中子表r[low,high]的记录，枢轴记录到位，并返回其所在位置，此时
    //在它之前（后）的记录均不大（小）于它。
    pivotkey = L->r[low].key;                   //用子表第一个记录作枢轴记录

    while (low < high) {                            //从表的两端交替地向中间扫描
        while (low < high && (*L).r[high].key >= pivotkey) {
            high--;
        }

        // swap(&(*L).r[high], &(*L).r[low], sizeof(&(*L).r[high]));//将比枢轴记录小的记录交换到低端
        swap(&L->r[high], &L->r[low]);//将比枢轴记录小的记录交换到低端

        while (low < high && L->r[low].key <= pivotkey) {
            low++;
        }

        // swap(&(*L).r[high], &(*L).r[low], sizeof(&(*L).r[high]));//将比枢轴记录大的记录交换到高端
        swap(&L->r[high], &L->r[low]);//将比枢轴记录大的记录交换到高端
    }

    return low;                                   //返回枢轴所在位置
}//Partition

// @brief 快排 获取枢纽位置 算法10.6b 改良后
// @param L 待排数组
// @param low 表左端
// @param high 表右端
// @return 新的枢纽位置
int Partition(seq_list_t* L, int low, int high)
{
    int pivotkey;

    //变换顺序表L中子表r[low,high]的记录，枢轴记录到位，并返回其所在位置，此时
    //在它之前（后）的记录均不大（小）于它。
    L->r[0] = L->r[low];                    //用子表第一个记录作枢轴记录
    pivotkey = L->r[low].key;                 //枢轴记录关键字

    while (low < high)
    { //从表的两端交替地向中间扫描
        while (low < high && L->r[high].key > pivotkey)
        {
            high--;
        }

        L->r[low] = L->r[high];               //将比枢轴记录小的记录交换到低端

        while (low < high && L->r[low].key <= pivotkey)
        {
            low++;
        }

        L->r[high] = L->r[low];               //将比枢轴记录大的记录交换到高端
    }

    L->r[low] = L->r[0];                    //枢轴记录到位

    return low;                                 //返回枢轴所在位置
} // Partition

// @brief 递归形式的快速排序
// @param L 待排数组
// @param low 表左端
// @param high 表右端
void QSort(seq_list_t* L, int low, int high)
{
    int pivotloc;

    if (low < high)
    {                                          //长度大于1
        pivotloc = Partition(L, low, high);      //将(*L).r[row..high]一分为二

        QSort(L, 1, pivotloc - 1);              //对低子表递归排序，pivotloc是枢轴位置
        QSort(L, pivotloc + 1, high);           //对高子表递归排序
    }
}// QSort

// @brief 快速排序入口
// @param L 待排数组
void QuickSort(seq_list_t* L)
{
    QSort(L, 1, (*L).length);
}// QuickSort


// @brief 简单选择排序
// @param L 待排数组
void SelectSort(seq_list_t* L)
{
    int i;
    int j;

    //对顺序表L作简单选择排序
    for (i = 1; i < L->length; ++i) {           //选择第i小的记录，并交换到位
        j = SelectMinKey(L, i);                   //在L.r[i..L.Length]中选择key最小的记录

        if (i != j)
        {
            swap(&(L->r[i]), &(L->r[j])); //与第i个记录交换
        }
    }
} // SelectSort


// @brief 迭代建立大顶堆
// @param H 堆数据
// @param index 结点值
// @param heap_size 堆最大长度
void HeapAdjust(HeapType* H, int index, int heap_size)
{

    /*
    RedType rc;
    rc = H->r[index];

    for (int child_idx = 2 * index; child_idx <= heap_size; child_idx *= 2) {              //沿key较大的孩子结点向下筛选
        if (child_idx < heap_size && LowerThan(H->r[child_idx].key, H->r[child_idx + 1].key))
        {
            child_idx++;                                      // j为key较大的记录的下标
        }

        if (!LowerThan(rc.key, H->r[child_idx].key))
        {
            break;                                    // rc应插入在位置s上
        }

        H->r[index] = H->r[child_idx];
        index = child_idx;
    }

    H->r[index] = rc;                               //插入
     */

    for (int child_idx = 2 * index; child_idx <= heap_size; child_idx *= 2) {              //沿key较大的孩子结点向下筛选
        if (child_idx < heap_size && LowerThan(H->r[child_idx].key, H->r[child_idx + 1].key))
        {
            child_idx++;                                      // j为key较大的记录的下标
        }

        if (!LowerThan(H->r[index].key, H->r[child_idx].key))
        {
            break;                                    // rc应插入在位置s上
        }

        RedType tmp = H->r[index];
        H->r[index] = H->r[child_idx];
        H->r[child_idx] = tmp;
    }

} // HeapAdjust


// @brief 堆排序
// @param H 堆数据
void HeapSort(HeapType* H)
{
    //对顺序表H进行堆排序
    for (int i = H->length / 2; i > 0; --i) {         //把H.r[1..H.length]建成大顶堆
        HeapAdjust(H, i, H->length);
    }

    for (int i = H->length; i > 1; --i)
    {
        swap(&H->r[1], &H->r[i]);
        HeapAdjust(H, 1, i - 1);
    }
} // HeapSort


// @brief 两个有序表归并为一个有序表
// @param SR 有序表
// @param TR 返回的有序表
// @param i SR起始位置
// @param m SR归并中点
// @param n SR终止位置
void Merge(RedType SR[], RedType TR[], int i, int m, int n)
{
    int j;
    int k;
    //将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n]
    for (j = m + 1, k = i; i <= m && j <= n; ++k) {            //将SR中记录由小到大地并入TR
        if (LowerEqual(SR[i].key, SR[j].key))
        {
            TR[k] = SR[i++];
        }
        else
        {
            TR[k] = SR[j++];
        }
    }

    while (i <= m) {                                          //将剩余的SR[i..m]复制到TR
        TR[k++] = SR[i++];
    }
    while (j <= n) {                                         //将剩余的SR[j..n]复制到TR
        TR[k++] = SR[j++];
    }
} // Merge

// @brief 归并排序
// @param SR 有序表
// @param TR1 返回的有序表
// @param s SR起始位置
// @param t SR终止位置
void MSort(RedType SR[], RedType TR1[], int s, int t)
{
    int m;
    RedType TR2[MAXSIZE + 1];
    // 将SR[s..t]归并排序为TR1[s..t]
    if (s == t)
    {
        TR1[s] = SR[s];
    }
    else
    {
        m = (s + t) / 2;                                      //将SR[s..t]平分为SR[s..m]和SR[m+1..t]
        MSort(SR, TR2, s, m);                                 //递归地将SR[s..m]归并为有序的TR2[s..m]
        MSort(SR, TR2, m + 1, t);                             //递归地将SR[m+1..t]归并为有序的TR2[m+1..t]
        Merge(TR2, TR1, s, m, t);                             //将R[s..m]和TR2[m+1..t]归并到TR1[s..t]
    }
} // MSort

// @brief 归并排序入口
// @param L 待排数组
void MergeSort(seq_list_t* L)
{
    //对顺序表L作归并排序
    MSort(L->r, L->r, 1, L->length);
} // MergeSort


int ord(char* keys, int pos, int keyNum) {
    int idx = keyNum - pos - 1;
    int num = (int)keys[idx] - 48;
    return num;
}


// @brief 基数排序 分配算法
// @param r 静态链表的结点域
// @param i 第i趟
// @param f 队列头
// @param e 队列尾
// void Distribute(static_linked_list_node_t r[], int i, ArrType f, ArrType e)
void Distribute(static_linked_list_t* slList, int i, ArrType f, ArrType e)
{
    static_linked_list_node_t* r = slList->r;
	//静态链表L的r域中记录已按(keys[0],...,keys[i-1])有序
	//本算法按第i个关键字keys[i]建立RADIX个子表，使同一子表中记录的keys[i]相同
	//f[0..RADIX-1]和e[0..RADIX-1]分别指向各子表中第一个和最后一个记录
	for (int j = 0; j < RADIX; j++)                              //各子表初始化为空表
	{
		f[j] = 0;
		e[j] = 0;
	}

	for (int p = r[0].next; p; p = r[p].next)
	{
		int j = ord(r[p].keys, i, slList->key_cnt);         // ord将记录中第i个关键字映射到[0..RADIX-1]

		if (!f[j])               // 如果对头元素为空, p入队, 为队头
		    f[j] = p;                     
		else
		    r[e[j]].next = p;    // 队尾增加元素

		e[j] = p;                // 将p所指的结点插入第j个子表中
	}
}//Distribute

// @brief 基数排序 收集算法
// @param r 静态链表的结点域
// @param i 第i趟
// @param f 队列头
// @param e 队列尾
void Collect(static_linked_list_node_t r[], int i, ArrType f, ArrType e) {
    int j;
    // 本算法按keys[i]自小至大地将f[0..RADIX-1]所指各子表依次连接成一个链表
    //e[0..RADIX-1]为各子表的尾指针
    for (j = 0; !f[j]; j = succ(j));           //找第一个非空子表，succ为求后继函数

    r[0].next = f[j];                                           // r[0].next指向第一个非空子表中第一个结点
    int t = e[j];

    while (j < RADIX) {
        for (j = succ(j); j < RADIX && !f[j]; j = succ(j)); //寻找下一个非空子表
        if (j == RADIX) {   // todo: 验证书上有错
            break;
        }

        if (f[j]) {                            //链接两个非空子表
            r[t].next = f[j];
            t = e[j];
        }
    }

    r[t].next = 0;                                        // t指向最后一个非空子表中的最后一个结点
}//Collect


int succ(idx) {
    return idx + 1;
}


// @brief 基数排序
// @param L 待排数组
void RadixSort(static_linked_list_t *L)
{
    ArrType f;
    ArrType e;
    //L是采用静态链表表示的顺序表
    //对L作基数排序，使得L成为按关键字自小到大的有序静态链表，L.r[0]为头结点。
    for (int i = 0; i < L->length; ++i) {
        L->r[i].next = i + 1;
    }
    L->r[L->length].next = 0;           //将L改造为静态链表
    for (int i = 0; i < L->key_cnt; ++i) //按最低位优先依次对各关键字进行分配和收集
    {
        Distribute(L, i, f, e);      //第i趟分配
        Collect(L->r, i, f, e);      //第i趟收集
    }
}


/*
void swap(void *v1, void *v2, size_t size)
{
  void *v3 = malloc(size);
  if (v3 != 0)
  {
    memmove(v3, v1, size);
    memmove(v1, v2, size);
    memmove(v2, v3, size);
    free(v3);
  }
} // refer:https://stackoverflow.com/questions/50559106/universal-array-element-swap-in-c?noredirect=1&lq=1
*/