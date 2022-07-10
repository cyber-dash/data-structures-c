/*!
 * @file test.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  矩阵 测试用例
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "test.h"
#include <stdio.h>


void TestAddAndReplaceElem() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                    Test AddAndReplaceElem                   \n");
    printf("                       测试新增(替换)函数                       \n\n\n");

    sparse_matrix_t tsMatrix;
    CreateSMatrix(&tsMatrix, 50, 40);

    AddAndReplaceElem(&tsMatrix, 1, 1, 9);
    AddAndReplaceElem(&tsMatrix, 49, 38, 19);
    AddAndReplaceElem(&tsMatrix, 1, 2, 11);
    AddAndReplaceElem(&tsMatrix, 6, 7, 432);
    AddAndReplaceElem(&tsMatrix, 6, 22, 5490);
    AddAndReplaceElem(&tsMatrix, 2, 1, 4);
    AddAndReplaceElem(&tsMatrix, 49, 39, 64);

    PrintSMatrix(tsMatrix);

    printf("|-------------------------------------------------------------|\n");
}


void TestTransposeSMatrix() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                    Test TransposeSMatrix                    \n");
    printf("                           测试转置                           \n\n\n");

    sparse_matrix_t tsMatrix;
    CreateSMatrix(&tsMatrix, 50, 40);

    AddAndReplaceElem(&tsMatrix, 1, 1, 9);
    AddAndReplaceElem(&tsMatrix, 49, 38, 19);
    AddAndReplaceElem(&tsMatrix, 1, 2, 11);
    AddAndReplaceElem(&tsMatrix, 6, 7, 432);
    AddAndReplaceElem(&tsMatrix, 6, 22, 5490);
    AddAndReplaceElem(&tsMatrix, 2, 1, 4);
    AddAndReplaceElem(&tsMatrix, 49, 39, 64);

    printf("\n转置前: \n");
    PrintSMatrix(tsMatrix);

    sparse_matrix_t tsMatrix2;
    TransposeSMatrix(tsMatrix, &tsMatrix2);

    printf("\n转置后: \n");
    PrintSMatrix(tsMatrix2);

    printf("|-------------------------------------------------------------|\n");
}


void TestFastTransposeSMatrix() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                  Test FastTransposeSMatrix                  \n");
    printf("                          测试快速转置                         \n\n\n");

    sparse_matrix_t tsMatrix;
    CreateSMatrix(&tsMatrix, 50, 40);

    AddAndReplaceElem(&tsMatrix, 1, 1, 9);
    AddAndReplaceElem(&tsMatrix, 49, 38, 19);
    AddAndReplaceElem(&tsMatrix, 1, 2, 11);
    AddAndReplaceElem(&tsMatrix, 6, 7, 432);
    AddAndReplaceElem(&tsMatrix, 6, 22, 5490);
    AddAndReplaceElem(&tsMatrix, 2, 1, 4);
    AddAndReplaceElem(&tsMatrix, 49, 39, 64);

    printf("\n转置前: \n");
    PrintSMatrix(tsMatrix);

    sparse_matrix_t tsMatrix2;
    FastTransposeSMatrix(tsMatrix, &tsMatrix2);

    printf("\n转置后: \n");
    PrintSMatrix(tsMatrix2);

    printf("|-------------------------------------------------------------|\n");
}
