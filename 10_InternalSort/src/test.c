//
// Created by cyberdash@163.com on 2021/3/14.
//

#include "test.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"


void ArrayOutput(seq_list_node_t* arr, int arr_size) {
    for (int i = 1; i <= arr_size; i++) {
        printf("%d ", arr[i].key);
    }
    printf("\n");
}


void RadixArrayOutput(static_linked_list_node_t* arr, int length) {
    int idx = 0;
    for (int i = 0; i < length; i++) {
        idx = arr[idx].next;
        printf("%s ", arr[idx].keys);
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
        seq_list_node_t redType;
        redType.key = array[i - 1];
        redType.info = '\0';
        seq_list.elements[i] = redType;
    }

    printf("排序前:\n");
    ArrayOutput(seq_list.elements, 6);

    BubbleSort(&seq_list);

    printf("排序后:\n");
    ArrayOutput(seq_list.elements, 6);
    printf("|-------------------------------------------------------------|\n");
}


void TestInsertSort() {
    printf("\n");
    printf("|------------------------- CyberDash -------------------------|\n");
    printf("|                       Test Insert Sort                      |\n");
    printf("|                          测试插入排序                         |\n\n\n");

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
    ArrayOutput(sqList.elements, 6);

    InsertSort(&sqList);

    printf("排序后:\n");
    ArrayOutput(sqList.elements, 6);

    printf("|-------------------------------------------------------------|\n");
}


void TestBInsertSort() {
    printf("\n");
    printf("|------------------------- CyberDash -------------------------|\n");
    printf("|                      Test BInsert Sort                      |\n");
    printf("|                        测试折半插入排序                         |\n\n\n");

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
    ArrayOutput(sqList.elements, 6);

    BInsertSort(&sqList);

    printf("排序后:\n");
    ArrayOutput(sqList.elements, 6);


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
    ArrayOutput(sqList.elements, 6);

    SelectSort(&sqList);

    printf("排序后:\n");
    ArrayOutput(sqList.elements, 6);

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
    ArrayOutput(seq_list.elements, 8);

    int dlta[3] = { 3, 2, 1 };
    ShellSort(&seq_list, dlta, 3);

    printf("排序后:\n");
    ArrayOutput(seq_list.elements, 8);

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
    ArrayOutput(sqList.elements, 6);

    QuickSort(&sqList);

    printf("排序后:\n");
    ArrayOutput(sqList.elements, 6);

    printf("-------------------------------------------------------------\n");
}


void TestHeapSort() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                       Test Heap Sort                       \n");
    printf("                          测试堆排序                         \n\n\n");
    key_t array[8] = {3, 1, 4, 1, 5, 9, 2, 6 };

    seq_list_t seq_list;
    seq_list.length = 8;
    for (int i = 1; i <= seq_list.length; i++) {
        seq_list_node_t elem;
        elem.key = array[i - 1];
        elem.info = '\0';
        seq_list.elements[i] = elem;
    }

    printf("排序前:\n");
    ArrayOutput(seq_list.elements, seq_list.length);

    HeapSort(&seq_list);

    printf("排序后:\n");
    ArrayOutput(seq_list.elements, seq_list.length);

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
    ArrayOutput(sqList.elements, 6);

    MergeSort(&sqList);

    printf("排序后:\n");
    ArrayOutput(sqList.elements, 6);

    printf("-------------------------------------------------------------\n");
}


void TestRadixSort() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                       Test Radix Sort                       \n");
    printf("                         测试基数排序                          \n\n\n");

    static_linked_list_t slList;

    // key_cnt和length可以自由调整(非0)
    slList.key_cnt = 5;   // 几位
    slList.length = 10;   // 几个数

    static_linked_list_node_t zeroSlCell;
    zeroSlCell.keys[0] = 0;
    zeroSlCell.keys[1] = 0;
    zeroSlCell.keys[2] = 0;
    zeroSlCell.keys[3] = 0;
    zeroSlCell.next = 1;
    slList.elements[0] = zeroSlCell;

    srand((unsigned)time(NULL));

    for (int i = 1; i <= slList.length; i++) {
      static_linked_list_node_t slCell;
      for (int j = 0; j <= slList.key_cnt; j++) {
        if (j == 0) {
          slCell.keys[j] = 49 + (rand() % 9);       // 第一位, '1' - '9'
        } else if (j == slList.key_cnt) {
          slCell.keys[j] = 0;                       // 置零位, '\0'
        } else {
          slCell.keys[j] = 49 + (rand() % 10) - 1;  // 其他位, '0' - '9'
        }
      }

      if (i != slList.length) {
          slCell.next = i + 1;
      } else {
          slCell.next = 0;
      }

      slList.elements[i] = slCell;
    }

    printf("排序前:\n");
    RadixArrayOutput(&slList.elements, slList.length);

    RadixSort(&slList);

    printf("排序后:\n");
    RadixArrayOutput(&slList.elements, slList.length);

    printf("-------------------------------------------------------------\n");
}
