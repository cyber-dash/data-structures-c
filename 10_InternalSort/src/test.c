//
// Created by cyberdash@163.com on 2021/3/14.
//

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
    printf("------------------------- CyberDash -------------------------\n");
    printf("                       Test Bubble Sort                      \n");
    printf("                         测试冒泡排序                         \n\n\n");

    key_t array[6] = {1, 4, 2, 8, 5, 7 };
    seq_list_t seq_list;
    seq_list.length = 6;
    for (int i = 1; i <= seq_list.length; i++) {
        seq_list_node_t seq_list_node;
        seq_list_node.key = array[i - 1];
        seq_list_node.info = '\0';
        seq_list.elements[i] = seq_list_node;
    }

    printf("排序前:\n");
    SeqListOutput(seq_list.elements, 6);

    BubbleSort(&seq_list);

    printf("排序后:\n");
    SeqListOutput(seq_list.elements, 6);
    printf("|-------------------------------------------------------------|\n");
}


void TestInsertSort() {
    printf("\n");
    printf("|------------------------- CyberDash -------------------------|\n");
    printf("|                       Test Insert Sort                      |\n");
    printf("|                          测试插入排序                         |\n\n\n");

    key_t array[6] = {1, 4, 2, 8, 5, 7 };
    seq_list_t seq_list;
    seq_list.length = 6;
    for (int i = 1; i <= seq_list.length; i++) {
        seq_list_node_t seq_list_node;
        seq_list_node.key = array[i - 1];
        seq_list_node.info = '\0';
        seq_list.elements[i] = seq_list_node;
    }

    printf("排序前:\n");
    SeqListOutput(seq_list.elements, 6);

    InsertSort(&seq_list);

    printf("排序后:\n");
    SeqListOutput(seq_list.elements, 6);

    printf("|-------------------------------------------------------------|\n");
}


void TestBInsertSort() {
    printf("\n");
    printf("|------------------------- CyberDash -------------------------|\n");
    printf("|                      Test BInsert Sort                      |\n");
    printf("|                        测试折半插入排序                         |\n\n\n");

    key_t array[6] = {1, 4, 2, 8, 5, 7 };
    seq_list_t seq_list;
    seq_list.length = 6;
    for (int i = 1; i <= seq_list.length; i++) {
        seq_list_node_t seq_list_node;
        seq_list_node.key = array[i - 1];
        seq_list_node.info = '\0';
        seq_list.elements[i] = seq_list_node;
    }

    printf("排序前:\n");
    SeqListOutput(seq_list.elements, 6);

    BInsertSort(&seq_list);

    printf("排序后:\n");
    SeqListOutput(seq_list.elements, 6);


    printf("|-------------------------------------------------------------|\n");
}


void TestSelectSort() {
    printf("\n");
    printf("|------------------------- CyberDash -------------------------|\n");
    printf("|                       Test Select Sort                      |\n");
    printf("|                          测试选择排序                         |\n\n\n");

    key_t array[6] = {1, 4, 2, 8, 5, 7 };
    seq_list_t sqList;
    sqList.length = 6;
    for (int i = 1; i <= sqList.length; i++) {
        seq_list_node_t redType;
        redType.key = array[i - 1];
        redType.info = '\0';
        sqList.elements[i] = redType;
    }

    printf("排序前:\n");
    SeqListOutput(sqList.elements, 6);

    SelectSort(&sqList);

    printf("排序后:\n");
    SeqListOutput(sqList.elements, 6);

    printf("|-------------------------------------------------------------|\n");
}


void TestShellSort() {
    printf("\n");
    printf("|------------------------- CyberDash -------------------------|\n");
    printf("|                       Test Select Sort                      |\n");
    printf("|                          测试希尔排序                         |\n\n\n");

    key_t array[8] = { 3, 1, 4, 1, 5, 9, 2, 6 };
    seq_list_t seq_list;
    seq_list.length = 8;
    for (int i = 1; i <= seq_list.length; i++) {
        seq_list_node_t elem;
        elem.key = array[i - 1];
        elem.info = '\0';
        seq_list.elements[i] = elem;
    }

    printf("排序前:\n");
    SeqListOutput(seq_list.elements, 8);

    int dlta[3] = { 3, 2, 1 };
    ShellSort(&seq_list, dlta, 3);

    printf("排序后:\n");
    SeqListOutput(seq_list.elements, 8);

    printf("|-------------------------------------------------------------|\n");
}


void TestQuickSort() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                       Test Quick Sort                       \n");
    printf("                          测试快速排序                         \n\n\n");
    key_t array[6] = {1, 4, 2, 8, 5, 7 };

    seq_list_t sqList;
    sqList.length = 6;
    for (int i = 1; i <= sqList.length; i++) {
        seq_list_node_t redType;
        redType.key = array[i - 1];
        redType.info = '\0';
        sqList.elements[i] = redType;
    }

    printf("排序前:\n");
    SeqListOutput(sqList.elements, 6);

    QuickSort(&sqList);

    printf("排序后:\n");
    SeqListOutput(sqList.elements, 6);

    printf("-------------------------------------------------------------\n");
}


void TestHeapSort() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                       Test Heap Sort                       \n");
    printf("                          测试堆排序                         \n\n\n");

    key_t array[8] = { 3, 1, 4, 1, 5, 9, 2, 6 };

    seq_list_t seq_list;
    seq_list.length = 8;

    for (int i = 1; i <= seq_list.length; i++) {
        seq_list_node_t seq_list_node;
        seq_list_node.key = array[i - 1];
        seq_list_node.info = '\0';
        seq_list.elements[i] = seq_list_node;
    }

    printf("排序前:\n");
    SeqListOutput(seq_list.elements, seq_list.length);

    HeapSort(&seq_list);

    printf("排序后:\n");
    SeqListOutput(seq_list.elements, seq_list.length);

    printf("-------------------------------------------------------------\n");

    printf("-------------------------------------------------------------\n");
}


void TestMergeSort() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                       Test Merge Sort                       \n");
    printf("                          测试归并排序                         \n\n\n");
    key_t array[6] = {1, 4, 2, 8, 5, 7 };

    seq_list_t sqList;
    sqList.length = 6;
    for (int i = 1; i <= sqList.length; i++) {
        seq_list_node_t redType;
        redType.key = array[i - 1];
        redType.info = '\0';
        sqList.elements[i] = redType;
    }

    printf("排序前:\n");
    SeqListOutput(sqList.elements, 6);

    MergeSort(&sqList);

    printf("排序后:\n");
    SeqListOutput(sqList.elements, 6);

    printf("-------------------------------------------------------------\n");
}


void TestRadixSort() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                       Test Radix Sort                       \n");
    printf("                         测试基数排序                          \n\n\n");

    radix_static_linked_list_t radix_static_linked_list;

    radix_static_linked_list.key_count = 5; // 元素位数
    radix_static_linked_list.length = 10;   // 静态链表长度

    // radix_static_linked_list.elements[0]初始化
    static_linked_list_node_t element_zero;
    element_zero.keys[0] = 0;
    element_zero.keys[1] = 0;
    element_zero.keys[2] = 0;
    element_zero.keys[3] = 0;
    element_zero.next = 1;
    radix_static_linked_list.elements[0] = element_zero;

    srand((unsigned)time(NULL));

    // 构造基数排序静态链表
    for (int i = 1; i <= radix_static_linked_list.length; i++) {
        static_linked_list_node_t static_linked_list_node;
        for (int j = 0; j <= radix_static_linked_list.key_count; j++) {
            if (j == 0) {
                static_linked_list_node.keys[j] = 49 + (rand() % 9);       // 第一位, '1' - '9'
            } else if (j == radix_static_linked_list.key_count) {
                static_linked_list_node.keys[j] = 0;                       // 置零位, '\0'
            } else {
                static_linked_list_node.keys[j] = 49 + (rand() % 10) - 1;  // 其他位, '0' - '9'
            }
        }

        if (i != radix_static_linked_list.length) {
            static_linked_list_node.next = i + 1;
        } else {
            static_linked_list_node.next = 0;
        }

        radix_static_linked_list.elements[i] = static_linked_list_node;
    }

    printf("排序前:\n");
    RadixArrayOutput(&radix_static_linked_list.elements, radix_static_linked_list.length);

    RadixSort(&radix_static_linked_list);

    printf("排序后:\n");
    RadixArrayOutput(&radix_static_linked_list.elements, radix_static_linked_list.length);

    printf("-------------------------------------------------------------\n");
}
