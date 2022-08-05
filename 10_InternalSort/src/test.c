/*!
 * @file test.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 内部排序测试源文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdio.h>
#include <stdlib.h>
#include "test.h"
#include "time.h"


/*!
 * 顺序表打印函数
 * @param seq_list 顺序表(指针)
 * @param seq_list_length 顺序表长度
 * @note
 * 其实本可以传seq_list_t*类型参数, 现在的传参方式是为了各位改成操作数组:-)
 */
void SeqListOutput(seq_list_node_t* seq_list, int seq_list_length) {
    for (int i = 1; i <= seq_list_length; i++) {
        printf("%d ", seq_list[i].key);
    }
    printf("\n");
}


/*!
 * <h1>基数数组打印函数</h1>
 * @param static_linked_list **静态链表**(指针)
 * @param static_linked_list_length **静态链表长度**
 * @note
 */
void RadixArrayOutput(static_linked_list_node_t* static_linked_list, int static_linked_list_length) {
    /// 遍历静态链表, 打印keys
    int index = 0;
    for (int i = 0; i < static_linked_list_length; i++) {
        index = static_linked_list[index].next;         //!< index更新为下一索引
        printf("%s ", static_linked_list[index].key);
    }
    printf("\n");
}


void TestBubbleSort() {
    printf("\n");
    printf("|------------------------- CyberDash -------------------------|\n");
    printf("|                       Test Insert Sort                      |\n");
    printf("|                          测试冒泡排序                         |\n\n");

    key_t keys[8] = { 3, 1, 4, 1, 5, 9, 2, 6 };

    // 长度为8的线性表seq_list
    seq_list_t seq_list;
    seq_list.length = 8;

    // 将keys数组各项值赋值到线性表seq_list
    for (int i = 1; i <= seq_list.length; i++) {
        seq_list.elements[i].key = keys[i - 1];
        seq_list.elements[i].info = '\0';
    }

    printf("冒泡排序前:\n");
    SeqListOutput(seq_list.elements, seq_list.length);

    BubbleSort(&seq_list);

    printf("冒泡排序后:\n");
    SeqListOutput(seq_list.elements, seq_list.length);

    printf("|-------------------------------------------------------------|\n\n");
}


void TestInsertSort() {
    printf("\n");
    printf("|------------------------- CyberDash -------------------------|\n");
    printf("|                       Test Insert Sort                      |\n");
    printf("|                          测试插入排序                         |\n\n\n");

    key_t keys[8] = { 3, 1, 4, 1, 5, 9, 2, 6 };

    // 长度为8的线性表seq_list
    seq_list_t seq_list;
    seq_list.length = 8;

    // 将keys数组各项值赋值到线性表seq_list
    for (int i = 1; i <= seq_list.length; i++) {
        seq_list.elements[i].key = keys[i - 1];
        seq_list.elements[i].info = '\0';
    }


    printf("插入排序前:\n");
    SeqListOutput(seq_list.elements, seq_list.length);

    InsertSort(&seq_list);

    printf("插入排序后:\n");
    SeqListOutput(seq_list.elements, seq_list.length);

    printf("|-------------------------------------------------------------|\n\n");
}


void TestBinaryInsertSort() {
    printf("\n");
    printf("|------------------------- CyberDash -------------------------|\n");
    printf("|                    Test BinaryInsert Sort                   |\n");
    printf("|                        测试折半插入排序                       |\n\n");

    key_t keys[8] = { 3, 1, 4, 1, 5, 9, 2, 6 };

    // 长度为8的线性表seq_list
    seq_list_t seq_list;
    seq_list.length = 8;

    // 将keys数组各项值赋值到线性表seq_list
    for (int i = 1; i <= seq_list.length; i++) {
        seq_list.elements[i].key = keys[i - 1];
        seq_list.elements[i].info = '\0';
    }

    printf("折半插入排序前:\n");
    SeqListOutput(seq_list.elements, seq_list.length);

    BinaryInsertSort(&seq_list);

    printf("折半插入排序后:\n");
    SeqListOutput(seq_list.elements, seq_list.length);


    printf("|-------------------------------------------------------------|\n\n");
}


void TestSelectSort() {
    printf("\n");
    printf("|------------------------- CyberDash -------------------------|\n");
    printf("|                       Test Select Sort                      |\n");
    printf("|                          测试选择排序                         |\n\n");

    key_t keys[8] = { 3, 1, 4, 1, 5, 9, 2, 6 };

    // 长度为8的线性表seq_list
    seq_list_t seq_list;
    seq_list.length = 8;

    // 将keys数组各项值赋值到线性表seq_list
    for (int i = 1; i <= seq_list.length; i++) {
        seq_list.elements[i].key = keys[i - 1];
        seq_list.elements[i].info = '\0';
    }

    printf("选择排序前:\n");
    SeqListOutput(seq_list.elements, seq_list.length);

    SelectSort(&seq_list);

    printf("选择排序后:\n");
    SeqListOutput(seq_list.elements, seq_list.length);

    printf("|-------------------------------------------------------------|\n\n");
}


void TestShellSort() {
    printf("\n");
    printf("|------------------------- CyberDash -------------------------|\n");
    printf("|                       Test Select Sort                      |\n");
    printf("|                          测试希尔排序                         |\n\n");

    key_t keys[8] = { 3, 1, 4, 1, 5, 9, 2, 6 };

    // 长度为8的线性表seq_list
    seq_list_t seq_list;
    seq_list.length = 8;

    // 将keys数组各项值赋值到线性表seq_list
    for (int i = 1; i <= seq_list.length; i++) {
        seq_list.elements[i].key = keys[i - 1];
        seq_list.elements[i].info = '\0';
    }

    int gaps[3] = { 3, 2, 1 };
    int gaps_count = 3;

    printf("希尔排序前:\n");
    SeqListOutput(seq_list.elements, 8);

    ShellSort(&seq_list, gaps, gaps_count);

    printf("希尔排序后:\n");
    SeqListOutput(seq_list.elements, 8);

    printf("|-------------------------------------------------------------|\n\n");
}


void TestQuickSort() {
    printf("\n");
    printf("|------------------------- CyberDash -------------------------|\n");
    printf("|                       Test Quick Sort                       |\n");
    printf("|                          测试快速排序                         |\n\n");

    key_t keys[8] = { 3, 1, 4, 1, 5, 9, 2, 6 };

    // 长度为8的线性表seq_list
    seq_list_t seq_list;
    seq_list.length = 8;

    // 将keys数组各项值赋值到线性表seq_list
    for (int i = 1; i <= seq_list.length; i++) {
        seq_list.elements[i].key = keys[i - 1];
        seq_list.elements[i].info = '\0';
    }

    printf("快速排序前:\n");
    SeqListOutput(seq_list.elements, seq_list.length);

    QuickSort(&seq_list);   // 执行快速排序

    printf("快速排序后:\n");
    SeqListOutput(seq_list.elements, seq_list.length);

    printf("|-------------------------------------------------------------|\n\n");
}


void TestHeapSort() {
    printf("\n");
    printf("|------------------------- CyberDash -------------------------|\n");
    printf("|                       Test Heap Sort                        |\n");
    printf("|                          测试堆排序                          |\n\n");

    key_t keys[8] = { 3, 1, 4, 1, 5, 9, 2, 6 };

    // 长度为8的线性表seq_list
    seq_list_t seq_list;
    seq_list.length = 8;

    // 将keys数组各项值赋值到线性表seq_list
    for (int i = 1; i <= seq_list.length; i++) {
        seq_list.elements[i].key = keys[i - 1];
        seq_list.elements[i].info = '\0';
    }

    printf("堆排序前:\n");
    SeqListOutput(seq_list.elements, seq_list.length);

    HeapSort(&seq_list);

    printf("堆排序后:\n");
    SeqListOutput(seq_list.elements, seq_list.length);

    printf("|-------------------------------------------------------------|\n\n");
}


void TestMergeSort() {
    printf("\n");
    printf("|------------------------- CyberDash -------------------------|\n");
    printf("|                       Test Merge Sort                       |\n");
    printf("|                          测试归并排序                         |\n\n");

    key_t keys[8] = { 3, 1, 4, 1, 5, 9, 2, 6 };

    // 长度为8的线性表seq_list
    seq_list_t seq_list;
    seq_list.length = 8;

    // 将keys数组各项值赋值到线性表seq_list
    for (int i = 1; i <= seq_list.length; i++) {
        seq_list.elements[i].key = keys[i - 1];
        seq_list.elements[i].info = '\0';
    }

    printf("排序前:\n");
    SeqListOutput(seq_list.elements, seq_list.length);

    MergeSort(&seq_list);

    printf("排序后:\n");
    SeqListOutput(seq_list.elements, seq_list.length);

    printf("|-------------------------------------------------------------|\n\n");
}


/*!
 * @brief <h1>测试基数排序</h1>
 * @note
 */
void TestRadixSort() {
    printf("\n");
    printf("|------------------------- CyberDash -------------------------|\n");
    printf("|                       Test Radix Sort                       |\n");
    printf("|                          测试基数排序                         |\n\n");

    /// ### 1 初始化静态链表 ###
    radix_static_linked_list_t radix_static_linked_list;

    /// - 5位数值正整数
    radix_static_linked_list.number_of_digit = 5;  // 元素位数
    /// - 9个数(静态链表长度9)
    radix_static_linked_list.length = 9;        // 静态链表长度

    /// - 静态链表表头初始化
    static_linked_list_node_t element_zero;
    element_zero.key[0] = 0;
    element_zero.key[1] = 0;
    element_zero.key[2] = 0;
    element_zero.key[3] = 0;
    element_zero.key[4] = 0;
    element_zero.next = 1;

    radix_static_linked_list.elements[0] = element_zero;

    srand((unsigned)time(NULL));

    /// ### 2 随机构造基数排序静态链表 ###
    /// &emsp; **for loop** 静态链表长度 : \n
    for (int i = 1; i <= radix_static_linked_list.length; i++) {
        /// &emsp;&emsp; 声明当前静态链表元素\n
        static_linked_list_node_t node;

        /// &emsp;&emsp; **for loop** 元素位数 :\n
        /// &emsp;&emsp;&emsp; 首位随机赋值'1' - '9' \n
        /// &emsp;&emsp;&emsp; 第一个越界位赋值'\0'(字符串结束字符) \n
        /// &emsp;&emsp;&emsp; 其他位随机赋值'0' - '9' \n
        for (int j = 0; j <= radix_static_linked_list.number_of_digit; j++) {
            if (j == 0) {
                node.key[j] = NUM_1_ASCII_CODE + (rand() % 9);
            } else if (j == radix_static_linked_list.number_of_digit) {
                node.key[j] = 0;
            } else {
                node.key[j] = NUM_0_ASCII_CODE + (rand() % 10);
            }
        }

        /// &emsp;&emsp; next指向下一个元素, 如果是最后一个元素next则指向0
        if (i != radix_static_linked_list.length) {
            node.next = i + 1;
        } else {
            node.next = 0;
        }

        /// &emsp;&emsp; 将当前元素赋给静态链表elements[i]
        radix_static_linked_list.elements[i] = node;
    }

    /// ### 4 排序前静态链表打印 ###
    printf("排序前:\n");
    RadixArrayOutput((static_linked_list_node_t*)&radix_static_linked_list.elements,
                     radix_static_linked_list.length);

    /// ### 5 调用RadixSort执行基数排序 ###
    RadixSort(&radix_static_linked_list);

    /// ### 6 排序后静态链表打印 ###
    printf("排序后:\n");
    RadixArrayOutput((static_linked_list_node_t*)&radix_static_linked_list.elements,
                     radix_static_linked_list.length);

    printf("|-------------------------------------------------------------|\n\n");
}
