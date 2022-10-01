/*!
 * @file static_search_table.c
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
#include "static_search_table.h"


/*!
 * @brief **静态搜索表初始化**
 * @param static_search_table 静态搜索表
 * @param elements 元素数组
 * @param length 元素个数
 * @return 执行结果
 * @note
 * 静态搜索表初始化
 * --------------
 * --------------
 *
 * --------------
 *
 * 注意: 索引从1开始(区别于数组索引从0开始)
 *
 * ----------------
 * ### 1 空搜索表处理 ###
 * &emsp; **if** 静态搜索表为NULL : \n
 * &emsp;&emsp; 返回ERROR \n
 * ### 2 静态搜索表初始化 ###
 * ### 3 静态搜索表各元素赋值 ###
 * &emsp; **for loop** 从后向前遍历静态搜索表: \n
 * &emsp;&emsp; static_search_table->elements[i] <== elements[i - 1] \n
 */
status_t StaticSearchTableInit(static_search_table_t* static_search_table, elem_t* elements, int length) {

    // ----- 1 空搜索表处理 -----
    if (static_search_table == NULL) {  // if 静态搜索表为NULL
        return ERROR;   // 返回ERROR
    }

    // ----- 2 静态搜索表初始化 -----
    static_search_table->elements = (elem_t*)malloc(sizeof(elem_t) * (length + 1));
    static_search_table->length = length;

    // ----- 3 静态搜索表各元素赋值 -----
    for (int i = 1; i <= length; i++) { // for loop 从后向前遍历静态搜索表
        static_search_table->elements[i] = elements[i - 1]; // static_search_table->elements[i] <== elements[i - 1]
    }

    return OK;
}


/*!
 * @brief **静态搜索表打印**
 * @param static_search_table 静态搜索表(指针)
 * @note
 * 静态搜索表打印
 * ------------
 * ------------
 *
 * ------------
 * **if** 空表 :\n
 * &emsp; 打印"空静态表"\n
 * **else** (非空表): \n
 * &emsp; **for loop** 遍历静态表各元素 : \n
 * &emsp;&emsp; 打印遍历元素的信息\n
 */
void StaticSearchTablePrint(static_search_table_t* static_search_table) {

    if (static_search_table == NULL || static_search_table->length == 0) {  // if 空表
        printf("空静态表"); // 打印"空静态表"
    } else {    // else 非空表
        printf("静态表:\n");
        for (int i = 1; i <= static_search_table->length; i++) {    // for loop 从后向前遍历静态表
            // 打印遍历元素的信息
            printf("{ key:%d, value:%.1lf }",
                   static_search_table->elements[i].key,
                   static_search_table->elements[i].value);

            if (i != static_search_table->length) {
                printf(", ");
            }
        }
    }

    printf("\n\n");
}


/*!
 * @brief **静态搜索表顺序搜索**
 * @param static_search_table 静态搜索表(指针)
 * @param key 待搜索关键码
 * @return 索引(如果没有元素则为0)
 * @note
 * 静态搜索表顺序搜索
 * ----------------
 * ----------------
 *
 * ----------------
 *
 * elements[0]作为哨兵
 *
 * ----------------
 * - 待搜索关键码赋给静态搜索表首元素的key\n
 * - 从静态搜索表最后一位开始向前遍历搜索\n
 */
int StaticSearchTableSeqSearch(static_search_table_t* static_search_table, KEY key) {

    // 待搜索关键码赋给静态搜索表首元素的key
    static_search_table->elements[0].key = key; // 哨兵

    // 从静态搜索表最后一位开始向前遍历搜索
    int i = static_search_table->length;
    while (!EQUAL(static_search_table->elements[i].key, key)) {
        i--;
    }

    return i;
}


/*!
 * @brief **静态搜索表二分查找**
 * @param static_search_table 静态搜索表(指针)
 * @param key 关键码
 * @return 索引(如果没有元素则为0)
 * 静态搜索表二分查找
 * ----------------
 * ----------------
 *
 * ----------------
 *
 * 注意: 索引从1开始(区别于数组索引从0开始)
 *
 * ----------------
 * ### 1 设置左右边界 ###
 * 左边界left: 1, 右边界right: 静态表length
 * ### 2 二分分治法进行搜索 ###
 * **while loop** left <= right :\n
 * &emsp; 取中间位置mid = (left + right) / 2;\n
 * &emsp; **if** mid位置元素关键码等于key :\n
 * &emsp;&emsp; 返回mid\n
 * &emsp; **else if** key小于mid位置元素关键码 :\n
 * &emsp;&emsp; right = mid - 1;(下一趟查找mid左侧区域)\n
 * &emsp; **else** (key大于mid位置元素关键码) :\n
 * &emsp;&emsp; left = mid + 1;(下一趟查找mid右侧区域)\n
 */
int StaticSearchTableBinarySearch(static_search_table_t* static_search_table, KEY key) {

    // ----- 1 设置左右边界 -----
    int left = 1;
    int right = static_search_table->length;

    // ----- 2 二分分治法进行搜索 -----
    while (left <= right) {
        int mid = (left + right) / 2;   // 取中间位置

        if (EQUAL(key, static_search_table->elements[mid].key)) {   // mid位置元素关键码等于key
            return mid; // 返回mid
        } else if (LESS_THAN(key, static_search_table->elements[mid].key)) {    // key小于mid位置元素关键码
            right = mid - 1;    // 下一趟查找mid左侧区域
        } else {    // key大于mid位置元素关键码
            left = mid + 1;     // 下一趟查找mid右侧区域
        }
    }

    return 0;
}
