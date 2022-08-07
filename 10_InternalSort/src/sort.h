/*!
 * @file sort.h
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 内部排序头文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#ifndef CYBER_DASH_SORT_H
#define CYBER_DASH_SORT_H


#define FALSE   0   //!< 逻辑非
#define TRUE    1   //!< 逻辑是

#define NUM_0_ASCII_CODE 48 //!< 字符'0'的ASC码
#define NUM_1_ASCII_CODE 49 //!< 字符'1'的ASC码

#define MAX_DIGIT_NUMBER 8                  //!< 关键字项数的最大值
#define RADIX_10 10                         //!< 10进制基数值

#define MAX_SEQ_LIST_SIZE 20     //!< 顺序表最大长度

typedef int BUCKETS[RADIX_10];  //!< 10进制基数排序桶数组
typedef char DIGIT_TYPE;        //!< 10进制数位值类型

typedef int key_t;    //!< 顺序表关键字类型
typedef char info_t;  //!< 其他数据类型


/*! @brief 顺序表结点 */
typedef struct {
    key_t key;      //!< 关键字项
    info_t info;    //!< 其他数据项
} seq_list_node_t;


/*! @brief 顺序表 */
typedef struct {
    int length;         //!< 顺序表长度
    seq_list_node_t elements[MAX_SEQ_LIST_SIZE + 1]; //!< elements[0]闲置或用作哨兵单元
} seq_list_t;


/*! @brief 静态链表结点结构体 */
typedef struct {
    DIGIT_TYPE key[MAX_DIGIT_NUMBER];   //!< 关键字
    info_t info;                        //!< 其他数据项
    int next;                           //!< 下一结点的索引
} static_linked_list_node_t;


/*! @brief 基数排序的静态链表 */
typedef struct {
    static_linked_list_node_t elements[MAX_SEQ_LIST_SIZE];    //!< 元素的静态链表, elements[0]为头结点(不保存元素)
    int number_of_digit;                                //!< 基数关键字个数
    int length;                                      //!< 静态链表长度
} radix_static_linked_list_t;


// 插入排序
void InsertSort(seq_list_t* seq_list);

// 折半插入排序
void BinaryInsertSort(seq_list_t* seq_list);

// 选择排序
void SelectSort(seq_list_t* seq_list);

// 冒泡排序
void BubbleSort(seq_list_t* seq_list);

// 希尔排序
void ShellSort(seq_list_t* seq_list, int* gaps, int gaps_length);

// 快速排序
void QuickSort(seq_list_t* seq_list);

// 堆排序
void HeapSort(seq_list_t* seq_list);

// 归并排序
void MergeSort(seq_list_t* seq_list);

// 基数排序
void RadixSort(radix_static_linked_list_t* static_linked_list);


#endif // CYBER_DASH_SORT_H
