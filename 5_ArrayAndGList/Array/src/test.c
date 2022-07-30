/*!
 * @file test.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief  矩阵测试源文件
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
    printf("                    Test SparseMatrixAddAndReplaceElem                   \n");
    printf("                       测试新增(替换)函数                       \n\n\n");

    sparse_matrix_t tsMatrix;
    SparseMatrixCreate(&tsMatrix, 50, 40);

    SparseMatrixAddAndReplaceElem(&tsMatrix, 1, 1, 9);
    SparseMatrixAddAndReplaceElem(&tsMatrix, 49, 38, 19);
    SparseMatrixAddAndReplaceElem(&tsMatrix, 1, 2, 11);
    SparseMatrixAddAndReplaceElem(&tsMatrix, 6, 7, 432);
    SparseMatrixAddAndReplaceElem(&tsMatrix, 6, 22, 5490);
    SparseMatrixAddAndReplaceElem(&tsMatrix, 2, 1, 4);
    SparseMatrixAddAndReplaceElem(&tsMatrix, 49, 39, 64);

    SparseMatrixPrint(tsMatrix);

    printf("|-------------------------------------------------------------|\n");
}


void TestTransposeSMatrix() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                    Test SparseMatrixTranspose                    \n");
    printf("                           测试转置                           \n\n\n");

    sparse_matrix_t tsMatrix;
    SparseMatrixCreate(&tsMatrix, 50, 40);

    SparseMatrixAddAndReplaceElem(&tsMatrix, 1, 1, 9);
    SparseMatrixAddAndReplaceElem(&tsMatrix, 49, 38, 19);
    SparseMatrixAddAndReplaceElem(&tsMatrix, 1, 2, 11);
    SparseMatrixAddAndReplaceElem(&tsMatrix, 6, 7, 432);
    SparseMatrixAddAndReplaceElem(&tsMatrix, 6, 22, 5490);
    SparseMatrixAddAndReplaceElem(&tsMatrix, 2, 1, 4);
    SparseMatrixAddAndReplaceElem(&tsMatrix, 49, 39, 64);

    printf("\n转置前: \n");
    SparseMatrixPrint(tsMatrix);

    sparse_matrix_t tsMatrix2;
    SparseMatrixTranspose(tsMatrix, &tsMatrix2);

    printf("\n转置后: \n");
    SparseMatrixPrint(tsMatrix2);

    printf("|-------------------------------------------------------------|\n");
}


void TestFastTransposeSMatrix() {
    printf("\n");
    printf("------------------------- CyberDash -------------------------\n");
    printf("                  Test SparseMatrixFastTranspose                  \n");
    printf("                          测试快速转置                         \n\n\n");

    sparse_matrix_t tsMatrix;
    SparseMatrixCreate(&tsMatrix, 50, 40);

    SparseMatrixAddAndReplaceElem(&tsMatrix, 1, 1, 9);
    SparseMatrixAddAndReplaceElem(&tsMatrix, 49, 38, 19);
    SparseMatrixAddAndReplaceElem(&tsMatrix, 1, 2, 11);
    SparseMatrixAddAndReplaceElem(&tsMatrix, 6, 7, 432);
    SparseMatrixAddAndReplaceElem(&tsMatrix, 6, 22, 5490);
    SparseMatrixAddAndReplaceElem(&tsMatrix, 2, 1, 4);
    SparseMatrixAddAndReplaceElem(&tsMatrix, 49, 39, 64);

    printf("\n转置前: \n");
    SparseMatrixPrint(tsMatrix);

    sparse_matrix_t tsMatrix2;
    SparseMatrixFastTranspose(tsMatrix, &tsMatrix2);

    printf("\n转置后: \n");
    SparseMatrixPrint(tsMatrix2);

    printf("|-------------------------------------------------------------|\n");
}
