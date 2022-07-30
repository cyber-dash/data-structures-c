
# 👀数据结构(C语言)教材/教程的代码实现

 - 通用于各类数据结构与算法(C语言)教材
 - 可直接运行调试，没有伪代码不能运行的烦恼
 - 代码注释完整，可生成网页版/PDF文档，效果丰富
 - CyberDash团队持续化的维护

# 🌵 包含知识点
| 编号 | 章节 | 重点内容 |
| ---- | ---- | ------- |
| 2    | [线性表](/2_LinearList/) | [顺序表](/2_LinearList/SeqList/src/seq_list.c)  [单链表](/2_LinearList/LinkedList/src/linked_list.c) |
| 3    | [栈和队列](/3_Stack_Queue/) | [栈](/3_Stack_Queue/Stack/src/seq_stack.c)  [循环队列](/3_Stack_Queue/Queue/src/circular_queue.c)  [链式队列](/3_Stack_Queue/Queue/src/link_queue.c) |
| 4    | [字符串](/4_String/)         | [BF匹配算法]() [KMP匹配算法]()               |
| 5    | [多维数组和广义表](/5_ArrayAndGList/) | [多维数组](/5_ArrayAndGList/Array/src/array.c)  [广义表](/5_ArrayAndGList/GList/src/gen_list.c) |
| 6    | [树](/6_Tree/)            | [二叉树](/6_Tree/src/binary_tree.c) [赫夫曼树](/6_Tree/src/huffman_tree.c)                                         |
| 7    | [图](/7_Graph/)                  |  [邻接矩阵图](/7_Graph/src/matrix_graph.c) [深度优先遍历]() [广度优先遍历]() [Prim最小生成树]() [Kruskal最小生成树]() [Dijkstra最短路径]() [Bellman-Ford最短路径]() [Floyd最短路]() [并查集](/7_Graph/src/disjoint_set.c) [最小优先队列]()  |
| 9    | [查找](/9_Search/)               | [静态表顺序查找](/9_Search/src/static_search_table_t.c) [静态表二分查找]()                                                                 |
| 10   | [内部排序](/10_InternalSort/)    | [冒泡排序]() [插入排序]() [选择排序]() [快速排序]() [归并排序]() [堆排序]() [基数排序]() []()                                                                                                                 |
| 11     |[外部排序](/11_ExternalSort/)   |[败者树](/11_ExternalSort/src/loser_tree.c#L10)                                                                      |


# 🤖 这份代码能帮你解决什么问题

对很多人来说, 学习数据结构过程是比较煎熬的, 因为这门课的内容对初学者比较抽象, 一部分人即便经过一段时间学习，可是由于理解不深刻或者对编程语言的陌生，
仍然难以实操, 学习的结果不尽如人意。很多人急切的需要一份代码，帮助自己学习数据结构。

这个项目，正是为了解决这些问题而写。

它格式规范, 能正确运行，注释丰富，可以作为**学习**、**理解知识**、**做作业**、**课程设计**和**复习**的参考资料。


# 🚀从此刻开始

## 💾 下载本项目

如何使用git? 你可以参考这个: [git使用方法](/docs/git.md)

```bash
git clone https://gitee.com/cyberdash/data-structure-c.git
```

## cmake 编译

```bash
cmake -G "Makefiles"
```

# 👨‍👩‍👦‍👦 关于我们

CyberDash团队主要成员是3名北邮硕士研究生，我们是拥有多年开发经验的开发工程师, 曾就职于若干外企/互联网大厂/国内知名企业.
如果想更多了解我们，欢迎关注抖音：cyberdash_yuan

🙋‍♀️ Y_Dash(元哥)

做过很多项目, 经历比较丰富，从底层到应用层, 安全/服务/社区/IoT/...
CyberDash抖音号所有视频的主要出镜人

💪 G_Dash(磊哥)

10多年安全/系统工程师, 专注C/Linux/网络/安全, 某互联网基础架构部资深工程师, 元哥身后稳如磐石的男人

🤸 L_Dash

Geek, 资深摸鱼大师（bushi... 喜欢一切技术, 喜欢研究各种新鲜事物

# 📣 感谢支持

如果你喜欢我们的项目，欢迎点击右上角的star，你的支持是我们持续更新的动力！

# 📒 参考
| |  |
| ------------- | - |
| 🧘‍♀️ **《数据结构c语言版》 严蔚敏** | 计算机专业最普遍的教材，数据结构考研参考书籍 |
| ⚛️ **Google Style Guides** | 谷歌的开源代码规范，本项目参考此规范编写 |