
# 👀这份代码是干什么的

实现计算机专业数据结构📒通用教材中的示例代码，使其从伪代码转变为可执行的程序，方便初学者运行和调试。

# 🤖 为什么要使用这份代码?

学习数据结构是比较痛苦的，因为这门课的内容都比较抽象，但是通过使用我们的代码，将抽象的内容实现出来，并可以运行出正确的结果，相信会对你理解数据结构和算法提供帮助。❤️

我们的代码是经过cyberdash团队严格审核的，每一行代码都仔细推敲。通过学习本项目，你可以获得📖

- 优雅的编程规范，参照谷歌的代码风格，让你养成优秀的编程习惯
- 标准的变量命名方式，每一个变量都经过深思熟虑，告别命名焦虑
- 完全开源，可直接使用的数据结构
- 简单的程序结构，小白也能看懂
- 清晰的目录结构，每一种数据结构都是单独项目
- 配套的课程更新中...


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

# 🌵 项目结构
| 编号 | 章节 | 重点内容 |
| ---- | ---- | ------- |
| 2    | [线性表](/2_LinearList/) | [线性表的顺序表示](/2_LinearList/SeqList/src/seq_list.c)  [线性表的链式表示](/2_LinearList/LinkedList/src/linked_list.c) |
| 3    | [栈和队列](/3_Stack_Queue/) | [栈](/3_Stack_Queue/Stack/src/seq_stack.c)  [顺序队列](/3_Stack_Queue/Queue/src/seq_queue.c)  [链式队列](/3_Stack_Queue/Queue/src/link_queue.c) |
| 4    | [串](/4_String/)         |                |
| 5    | [数组和广义表](/5_ArrayAndGList/) | [数组的表示与实现](/5_ArrayAndGList/Array/src/array.c)  [广义表的表示与实现](/5_ArrayAndGList/GList/src/gen_list.c) |
| 6    | [树和二叉树](/6_Tree/)            | [二叉树](/6_Tree/src/binary_tree.c) [赫夫曼树](/6_Tree/src/huffman_tree.c)                                         |
| 7    | [图](/7_Graph/)                  | [搜索算法](/7_Graph/src/algorithm.c) [并查集](/7_Graph/src/disjoint_set.c)   [邻接矩阵](/7_Graph/src/matrix_graph.c) |
| 9    | [查找](/9_Search/)               | [静态查找](/9_Search/src/static_search_table_t.c)                                                                 |
| 10   | [内部排序](/10_InternalSort/)    |                                                                                                                 |
| 11     |[外部排序](/11_ExternalSort/)   |[败者树](/11_ExternalSort/src/loser_tree.c#L10)                                                                      |


# 👨‍👩‍👦‍👦 关于我们

我们是拥有十多年开发经验的开发工程师, 长期就职于各传统与互联网大厂.
目前在做计算机考研相关的内容, 如果想更多了解我们，欢迎关注抖音：cyberdash_yuan

🙋‍♀️ Y_Dash(元哥)

用过很多语言, 做过很多项目, 从底层到应用层, 安全/服务/社区/IoT/...
写代码能剪裁kernel, 吹拉谈唱能去欧洲做展会讲解, 从外太空到内XX, 五花八门什么都略懂一些

💪 G_Dash(磊哥)

10多年安全/系统工程师, 专注C/Linux/网络/安全, 某互联网基础架构部资深工程师, 元哥身后稳如磐石的男人

🤸 L_Dash

Geek, 资深摸鱼大师（bushi... 喜欢一切技术(但不精通

# 📣 感谢支持

如果你喜欢我们的项目，欢迎点击右上角的star，你的支持是我们持续更新的动力！

# 📒 参考
| |  |
| ------------- | - |
| 🧘‍♀️ **《数据结构c语言版》 严蔚敏** | 计算机专业最普遍的教材，数据结构考研参考书籍 |
| ⚛️ **Google Style Guides** | 谷歌的开源代码规范，本项目参考此规范编写 |