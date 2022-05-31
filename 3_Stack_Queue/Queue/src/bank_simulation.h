//
// Created by cyberdash@163.com on 2022/2/16.
//

#ifndef CYBER_DASH_BANK_SIMULATION_H
#define CYBER_DASH_BANK_SIMULATION_H


typedef struct {
    int OccurTime;      // 事件发生时刻
    int NType;          // 事件类型, 0表示到达事件, 1至4表示四个窗口的离开事件
}Event, ElemType;       // 事件类型, 有序链表LinkList的数据元素类型

// typedef LinkList    EventList;   // 事件链表类型, 定义为有序链表

#endif // CYBER_DASH_BANK_SIMULATION_H
