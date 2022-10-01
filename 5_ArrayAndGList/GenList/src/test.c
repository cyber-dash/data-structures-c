/*!
 * @file test.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  广义表测试源代码
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"


/*!
 * @brief **广义表深度测试**
 * @note
 * 广义表深度测试
 * ------------
 * ------------
 * ###1 构造广义表###
 * &emsp; 使用字符串"(A,(),(B,(C)))", 调用GenLIstCreateByStr构造广义表
 * ###2 求广义表的深度###
 */
void TestGenListDepth() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                      Test GenListDepth                      \n");
    printf("                        测试广义表的深度                        \n\n\n");

    // ----- 1 构造广义表 -----
    // 使用字符串"(A,(),(B,(C)))", 调用GenLIstCreateByStr构造广义表
    gen_list_t gen_list = NULL;

    char input_gen_list_str[100] = "(A,(),(B,(C)))";
    GenListCreateByStr(&gen_list, input_gen_list_str, (int)strlen(input_gen_list_str));

    char* gen_list_str = (char*)malloc(100 * sizeof(char));
    GenListToString(gen_list, gen_list_str, 100);

    // 2 求广义表的深度
    int depth = GenListDepthRecursive(gen_list);

    printf("广义表%s的深度: %d\n", gen_list_str, depth);

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}


/*!
 * @brief **广义表复制测试**
 * @note
 * 广义表复制测试
 * ------------
 * ------------
 * ###1 构造广义表###
 * &emsp; 使用字符串"(A,(),(B,(C)))", 调用GenLIstCreateByStr构造广义表
 * ###2 复制广义表###
 * &emsp; 调用CopyGenList将gen_list复制到new_gen_list
 */
void TestGenListCopy() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                       Test GenListCopy                      \n");
    printf("                        测试广义表的复制                        \n\n\n");

    // ----- 1 构造广义表 -----
    // 使用字符串"(A,(),(B,(C)))", 调用GenLIstCreateByStr构造广义表
    gen_list_t gen_list = NULL;
    char input_gen_list_str[100] = "(A,(),(B,(C)))";
    GenListCreateByStr(&gen_list, input_gen_list_str, (int)strlen(input_gen_list_str));

    char* gen_list_str = (char*)malloc(100 * sizeof(char));
    GenListToString(gen_list, gen_list_str, 100);
    printf("广义表: %s\n\n", gen_list_str);

    // ----- 2 复制广义表 -----
    // 调用CopyGenList将gen_list复制到new_gen_list
    gen_list_t new_gen_list = NULL;
    GenListCopyRecursive(&new_gen_list, gen_list);

    char* new_gen_list_str = (char*)malloc(100 * sizeof(char));
    GenListToString(new_gen_list, new_gen_list_str, 100);
    printf("复制的广义表: %s\n", new_gen_list_str);

    printf("-------------------- 抖音: cyberdash_yuan --------------------\n");
}
