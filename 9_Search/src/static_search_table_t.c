/*!
 * @file static_search_table_t.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 静态查找源文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "static_search_table_t.h"


/*!
 * <h1>静态搜索表初始化</h1>
 * @param static_search_table **静态搜索表**
 * @param elements **元素数组**
 * @param length **元素个数**
 * @return **执行结果**
 * @note
 */
status_t StaticSearchTableInit(static_search_table_t* static_search_table, elem_t* elements, int length) {

    /// ###1 空搜索表处理 ###
    /// &emsp; **if** 静态搜索表为NULL : \n
    /// &emsp;&emsp; 返回ERROR \n
    if (static_search_table == NULL) {
        return ERROR;
    }

    /// ### 2 静态搜索表初始化 ###
    static_search_table->elements = (elem_t*)malloc(sizeof(elem_t) * (length + 1));
    static_search_table->length = length;

    /// ### 3 静态搜索表各元素赋值 ###
    /// &emsp; **for loop* 静态搜索表长度: \n
    /// &emsp;&emsp; static_search_table->elements[i] <== elements[i - 1]
    for (int i = 1; i <= length; i++) {
        static_search_table->elements[i] = elements[i - 1];
    }

    return OK;
}


/*!
 * @brief <h1>静态搜索表打印</h1>
 * @param static_search_table **静态搜索表**(指针)
 * @note
 */
void StaticSearchTablePrint(static_search_table_t* static_search_table) {

    /// **if** 空表 :\n
    /// &emsp; 打印"空静态表"\n
    if (static_search_table == NULL || static_search_table->length == 0) {
        printf("空静态表");
    } else {

        /// **else** (非空表): \n
        printf("静态表:\n");
        /// &emsp; **for loop** 遍历静态表各元素 : \n
        for (int i = 1; i <= static_search_table->length; i++) {
            /// &emsp;&emsp; 打印遍历元素的信息\n
            printf("{ key:%d, value:%.1lf }", static_search_table->elements[i].key, static_search_table->elements[i].value);
            if (i != static_search_table->length) {
                printf(", ");
            }
        }
    }

    printf("\n\n");
}


/*!
 * @brief <h1>静态搜索表顺序搜索</h1>
 * @param static_search_table **静态搜索表**(指针)
 * @param key **待搜索关键码**
 * @return 索引(如果没有元素则为0)
 * @note
 */
int StaticSearchTableSeqSearch(static_search_table_t* static_search_table, KEY key) {

    /// ### 1 待搜索关键码赋给静态搜索表首元素的key###
    static_search_table->elements[0].key = key; // 哨兵

    /// ### 2 从静态搜索表最后一位开始向前遍历搜索###
    int i = static_search_table->length;
    while (!EQUAL(static_search_table->elements[i].key, key)) {
        i--;
    }

    return i;
}


/*!
 * @brief <h1>静态搜索表二分查找</h1>
 * @param static_search_table **静态搜索表**(指针)
 * @param key **关键码**
 * @return 索引(如果没有元素则为0)
 */
int StaticSearchTableBinarySearch(static_search_table_t* static_search_table, KEY key) {

    /// ### 1 设置左右边界 ###
    int left = 1;
    int right = static_search_table->length;

    /// ### 2 二分分治法进行搜索 ###
    while (left <= right) {
        int mid = (left + right) / 2;

        if (EQUAL(key, static_search_table->elements[mid].key)) {
            return mid;
        } else if (LESS_THAN(key, static_search_table->elements[mid].key)) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return 0;
}
