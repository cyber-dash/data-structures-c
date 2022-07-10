/*!
 * @file test.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 内部排序 测试用例
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */
#include "test.h"
#include "stdio.h"
#include "stdlib.h"
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
 * 基数数组打印函数
 * @param static_linked_list 静态链表(指针)
 * @param static_linked_list_length 静态链表
 */
void RadixArrayOutput(static_linked_list_node_t* static_linked_list, int static_linked_list_length) {
    int index = 0;  //!< 起始遍历的数组索引为0
    for (int i = 0; i < static_linked_list_length; i++) {
        index = static_linked_list[index].next;         //!< index更新为下一索引
        printf("%s ", static_linked_list[index].keys);
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


void TestRadixSort() {
    printf("\n");
    printf("|------------------------- CyberDash -------------------------|\n");
    printf("|                       Test Radix Sort                       |\n");
    printf("|                          测试基数排序                         |\n\n");

    radix_static_linked_list_t radix_static_linked_list;

    radix_static_linked_list.digit_number = 5; // 元素位数
    radix_static_linked_list.length = 10;   // 静态链表长度

    // radix_static_linked_list.elements[0]初始化
    static_linked_list_node_t element_zero;
    element_zero.keys[0] = 0;
    element_zero.keys[1] = 0;
    element_zero.keys[2] = 0;
    element_zero.keys[3] = 0;
    element_zero.keys[4] = 0;
    element_zero.next = 1;
    radix_static_linked_list.elements[0] = element_zero;

    srand((unsigned)time(NULL));

    // 构造基数排序静态链表
    for (int i = 1; i <= radix_static_linked_list.length; i++) {
        static_linked_list_node_t node;
        for (int j = 0; j <= radix_static_linked_list.digit_number; j++) {
            if (j == 0) {   //!< 第1位, 0 - 9随机赋值
                node.keys[j] = NUM_1_ASCII_CODE + (rand() % 9);   //!< 第一位, '1' - '9'
            } else if (j == radix_static_linked_list.digit_number) {   //!<
                node.keys[j] = 0;                                //!< 置零位, '\0'
            } else {
                node.keys[j] = NUM_0_ASCII_CODE + (rand() % 10); //!< 其他位, '0' - '9'
            }
        }

        if (i != radix_static_linked_list.length) {
            node.next = i + 1;
        } else {
            node.next = 0;
        }

        radix_static_linked_list.elements[i] = node;
    }

    printf("排序前:\n");
    RadixArrayOutput((static_linked_list_node_t*)&radix_static_linked_list.elements,
                     radix_static_linked_list.length);

    RadixSort(&radix_static_linked_list);

    printf("排序后:\n");
    RadixArrayOutput((static_linked_list_node_t*)&radix_static_linked_list.elements,
                     radix_static_linked_list.length);

    printf("|-------------------------------------------------------------|\n\n");
}
