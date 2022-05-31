//
// Created by cyberdash@163.com on 2022/1/19.
//

#include "stdlib.h"
#include "HuffmanTree.h"


void Select(HuffmanTree HT, int lastIndex, int* s1, int* s2);


//todo: temp
/*
void HuffmanCoding(HuffmanTree HT, HuffmanCode *HC, int *w, int n) {
    // w存放n个字符的权值(均>0), 构造赫夫曼树HT, 并求出n个字符的赫夫曼编码HC.
    if (n <= 1) return;
    int m = 2 * n - 1;  // m个节点
    HT = (HuffmanTree)malloc((m + 1)*sizeof(HTNode));      // 0号单元未用

    int i;
    HTNode *p;
    for (p = HT + 1, i = 1; i <= n; ++i, ++p, ++w) {    // 从数组索引1开始, 讲n个字符对应的节点初始化
        p->weight = *w;
        p->parent = 0;
        p->lchild = 0;
        p->rchild = 0;
    }

    for (; i <= m; ++i, ++p)  { // 讲剩余的节点初始化(权值设置为0)
        p->weight = 0;
        p->parent = 0;
        p->lchild = 0;
        p->rchild = 0;
    }

    for (i = n + 1; i <= m; ++i) {  // 建赫夫曼树
        // 在HT[1...i-1]选择parent为0且weight最小的两个结点, 其序号分别为s1和s2
        int s1;
        int s2;
        Select(HT, i - 1, &s1, &s2);

        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }

    // ----从叶子到根逆向求每个字符的赫夫曼编码----
    HC = (HuffmanCode)malloc((n+1)*sizeof(char*));  // todo:
    char *cd = (char*)malloc(n*sizeof(char));       // 分配n个字符编码的头指针向量
    cd[n - 1] = 0;

    for (int i = 1; i <= n; ++i) {
        int start = n - 1;
        for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent) {    // 从叶子到根逆向求编码
            if (HT[f].lchild == c)
                cd[--start] = "0";
            else
                cd[--start] = "1";
        }
        HC[i] = (char*)malloc((n - start) * sizeof(char));    // 为第i个字符编码分配空间
        strcpy(HC[i], &cd[start]);          // 从cd复制编码(串)到HC
    }

    printf("%s\n", cd);

    free(cd);
}
*/


void Select(HuffmanTree HT, int lastIndex, int* s1, int* s2) {
    if (lastIndex < 2) {
        return;
    }
    int minWeight = 0;
    int secMinWeight = 0;

    if (HT[1].weight >= HT[2].weight) {
        *s1 = 2;
        *s2 = 1;
        minWeight = HT[2].weight;
        secMinWeight = HT[1].weight;
    } else {
        *s1 = 1;
        *s2 = 2;
        minWeight = HT[1].weight;
        secMinWeight = HT[2].weight;
    }

    if (lastIndex == 2) {
        return;
    }

    for (int i = 3; i <= lastIndex; i++) {
        int curWeight = HT[i].weight;
        if (curWeight < minWeight) {
            *s2 = *s1;
            *s1 = i;
            secMinWeight = minWeight;
            minWeight = curWeight;
        } else if (curWeight < secMinWeight) {
            *s2 = i;
            secMinWeight = curWeight;
        }
    }
}
