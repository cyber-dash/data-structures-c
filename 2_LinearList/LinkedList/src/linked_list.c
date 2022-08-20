/*!
 * @file linked_list.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 单链表头文件
 * @version 1.0.0
 * @date 2022-07-10
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"


/*!
 * @brief <h1>链表创建<h1>
 * @param linked_list_head **链表头结点**(指针)
 * @param elements **数据项数组**
 * @param elem_count **数据项数量**
 * @return **执行结果**
 * @note
 *
 * - 链表头结点分配内存 \n
 * &emsp; **if** 内存分配失败 : \n
 * &emsp;&emsp; 返回NON_ALLOCATED \n
 * - 链表头节点next设置为NULL \n
 * - 遍历数据项数组并插入链表结点
 * &emsp; **for loop** 遍历数据项数组(从后向前) : \n
 * &emsp;&emsp; 分配当前链表结点内存 \n
 * &emsp;&emsp; **if** 内存分配失败 : \n
 * &emsp;&emsp;&emsp; 返回NON_ALLOCATED \n
 * &emsp;&emsp; 当前数据项elements[i]赋给当前链表结点的data \n
 * &emsp;&emsp; 链表头的next指向当前链表结点 \n
 */
status_t LinkedListCreate(linked_node_t** linked_list_head, ELEM_TYPE* elements, int elem_count) {
    *linked_list_head = (linked_node_t*)malloc(sizeof(linked_node_t)); // 链表头结点分配内存
    if (!(*linked_list_head)) {
        return NON_ALLOCATED;
    }

    (*linked_list_head)->next = NULL;

    for (int i = elem_count - 1; i >= 0; i--) {
        linked_node_t* linked_node = (linked_node_t*)malloc(sizeof(linked_node_t)); // 新结点分配内存
        if (!linked_node) {
            return NON_ALLOCATED;
        }

        linked_node->data = elements[i];            // elements[i]赋给新结点数据项
        linked_node->next = (*linked_list_head)->next; // 新结点next赋值
        (*linked_list_head)->next = linked_node;       // linked_list_head->next指向新结点
    }

    return OK;
}


/*!
 * @brief <h1>链表获取某位置的结点数据</h1>
 * @param linked_list_head **链表头结点**(指针)
 * @param pos **位置**
 * @param elem **保存结点数据项的变量**(指针)
 * @return **执行结果**
 * @note
 *
 * - 初始化遍历指针cur和起始位置cur_post(从1开始, 区别于数组的从0开始) \n
 * - 遍历链表至位置pos \n
 * &emsp; **while** 未遍历至位置pos : \n
 * &emsp;&emsp; cur指向后一个结点 \n
 * &emsp;&emsp; cur_pos加1 \n
 * - 边界条件判断 \n
 * **if** 遍历指针cur指向NULL 或者 cur_pos大于pos : \n
 * &emsp; 返回NON_EXISTENT(不存在该位置的元素) \n
 * - 将位置pos的元素的data赋给参数elem指向的变量
 */
status_t LinkedListGetElem(linked_list_t linked_list_head, int pos, ELEM_TYPE* elem) {
    linked_node_t* cur = linked_list_head->next;
    int cur_pos = 1;

    while (cur && cur_pos < pos) {
        cur = cur->next;
        cur_pos++;
    }

    // 位置pos的结点不存在, 返回NON_EXISTENT
    if (!cur || cur_pos > pos) {
        return NON_EXISTENT;
    }

    *elem = cur->data; // 将位置pos的数据项赋给*elem

    return OK;
}


/*!
 * @brief <h1>链表插入</h1>
 * @param linked_list_head **链表头结点**(指针)
 * @param pos **位置**(在这个位置前执行插入)
 * @param elem **待插入的数据项**
 * @return **执行结果**
 * @note
 *
 * - 初始化指针cur和insert_pos_predecessor \n
 * &emsp; cur用来遍历, 找到插入位置的前一节点, insert_pos_predecessor用来找该节点的位置 \n
 * - 找到插入位置 \n
 * &emsp; **while** cur不为NULL 或者 尚未遍历完整个链表 \n
 * &emsp;&emsp; cur指向下一个结点 \n
 * &emsp;&emsp; insert_pos_predecessor加1 \n
 * - 处理没有插入位置的情况 \n
 * &emsp; **if** 插入位置不存在 \n
 * &emsp;&emsp; 返回ERROR \n
 * - 执行插入 \n
 * &emsp; 分配结点内存 \n
 * &emsp; **if** 内存分配失败 : \n
 * &emsp;&emsp; 返回NON_ALLOCATED \n
 * &emsp; 插入节点设置data和next \n
 * &emsp; cur->next指向插入节点 \n
 */
status_t LinkedListInsert(linked_list_t linked_list_head, int pos, ELEM_TYPE elem) {
    linked_node_t* cur = linked_list_head;    // 插入完成后, 插入结点的前一结点(指针), 初始化指向链表头结点
    int insert_pos_predecessor = 0; // 插入位置的前一位置, 初始化为0

    // 遍历到插入位置的前一位置
    while(!cur || insert_pos_predecessor < pos - 1) {
        cur = cur->next;
        insert_pos_predecessor++;
    }

    // 如果插入位置不存在, 返回ERROR
    if (!cur || insert_pos_predecessor > pos - 1) {
        return ERROR;
    }

    linked_node_t* insert_node = (linked_node_t*)malloc(sizeof(linked_node_t)); // 插入结点分配内存
    if (!insert_node) {
        return NON_ALLOCATED;
    }

    insert_node->data = elem;
    insert_node->next = cur->next;
    cur->next = insert_node;

    return OK;
}


/*!
 * 链表删除结点
 * @param linked_list_head 链表头结点(指针)
 * @param pos 位置
 * @param elem 被删除结点数据项的保存变量(指针)
 * @return 是否成功
 */
status_t LinkedListDelete(linked_list_t linked_list_head, int pos, ELEM_TYPE* elem) {
    linked_node_t* delete_node_predecessor = linked_list_head;    // 待删除结点前一结点(指针), 初始化指向链表头结点
    int delete_pos_predecessor = 0; // 待删除结点前一结点的位置, 初始化为0

    // 遍历到待删除结点的前一结点
    while(!(delete_node_predecessor->next) || delete_pos_predecessor < pos - 1) {
        delete_node_predecessor = delete_node_predecessor->next;
        delete_pos_predecessor++;
    }

    // 位置pos的结点不存在, 返回NON_EXISTENT
    if (!(delete_node_predecessor->next) || delete_pos_predecessor > pos - 1) {
        return NON_EXISTENT;
    }

    linked_node_t* delete_node = delete_node_predecessor->next; // delete_node指向待删除结点
    delete_node_predecessor->next = delete_node->next;
    *elem = delete_node->data;

    free(delete_node);  // 释放结点
    delete_node = NULL; // 避免野指针

    return OK;
}


/*!
 * 合并两个有序链表
 * @param list_a_head a链表头结点(指针)
 * @param list_b_head b链表头结点(指针)
 * @param merged_list_head 合并链表头结点(二级指针)
 * @return 合并结果
 */
status_t LinkedListMergeTwoSortedList(linked_list_t list_a_head, linked_list_t list_b_head, linked_list_t* merged_list_head) {

    linked_node_t* a_cur = list_a_head->next;
    linked_node_t* b_cur = list_b_head->next;

    *merged_list_head = list_a_head;
    linked_node_t* cur = list_a_head;

    while (a_cur && b_cur) {
        if (a_cur->data <= b_cur->data) {
            cur->next = a_cur;
            cur = a_cur;
            a_cur = a_cur->next;
        } else {
            cur->next = b_cur;
            cur = b_cur;
            b_cur = b_cur->next;
        }
    }

    if (a_cur) {
        cur->next = a_cur;
    }

    return OK;
}

/*!
 * 打印链表
 * @param linked_list_head 链表指针
 */
void LinkedListPrint(linked_list_t linked_list_head) {
    for (linked_node_t* cur = linked_list_head->next; cur != NULL; cur = cur->next) {
        printf("%d ", cur->data);
    }

    printf("\n");
}
