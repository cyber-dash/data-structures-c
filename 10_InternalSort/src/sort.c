/*!
 * @file sort.c
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 内部排序源文件
 * @version 1.0.0
 * @date 2022-07-04
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "sort.h"


/*!
 * <h1>小于</h1>
 * @param key1 **关键字1**
 * @param key2 **关键字2**
 * @return **结果**
 * @note
 */
int LessThan(key_t key1, key_t key2) {
    if (key1 < key2) {
        return 1;
    }

    return 0;
}


/*!
 * <h1>小于等于</h1>
 * @param key1 **关键字1**
 * @param key2 **关键字2**
 * @return **结果**
 * @note
 */
int LessThanOrEqual(key_t key1, key_t key2) {
    if (key1 <= key2) {
        return 1;
    }

    return 0;
}


/*!
 * <h1>交换函数</h1>
 * @param item1 **元素1**
 * @param item2 **元素2**
 * @note
 */
void Swap(seq_list_node_t* item1, seq_list_node_t* item2) {
    seq_list_node_t tmp = *item1;
    *item1 = *item2;
    *item2 = tmp;
}


/*!
 * <h1>在线性表索引index(包含)之后的元素中选出key最小的元素的索引</h1>
 * @param seq_list **线性表**
 * @param index **索引**
 * @return **最小元素的索引**
 * @note
 */
int SelectMinKey(seq_list_t* seq_list, int index) {

    /// ### 1 索引范围检查 ###
    /// &emsp; **if** index等于线性表长度 :\n
    /// &emsp;&emsp; 只剩下一个元素, 因此该元素即为最小, 返回index\n
    if (index == seq_list->length) {
        return index;
    }

    /// ### 2 遍历并查找元素###
    /// &emsp; 变量min_key_index初始化为index
    /// &emsp; 变量min_key初始化为对应元素的key
    int min_key_index = index;
    key_t min_key = seq_list->elements[index].key;

    /// &emsp; **for loop** index后面的所有元素 : \n
    for (int i = index + 1; i <= seq_list->length; i++) {

        /// &emsp;&emsp; **if** 当前元素的key 小于 min_key :\n
        /// &emsp;&emsp;&emsp; 更新min_key_index和min_key
        if (seq_list->elements[i].key < min_key) {
            min_key_index = i;
            min_key = seq_list->elements[i].key;
        }
    }

    return min_key_index;
}


/*!
 * @brief <h1>插入排序</h1>
 * @param seq_list 待排线性表
 * @note
 */
void InsertSort(seq_list_t* seq_list) {
    //对顺序表L作直接插入排序
    for (int i = 2; i <= seq_list->length; i++) {
        // ("<"，需将seq_list.elements[i]插入有序子表)
        if (LessThan(seq_list->elements[i].key, seq_list->elements[i - 1].key)) {

            // 交换 seq_list->elements[i]与seq_list->elements[i - 1]
            seq_list->elements[0] = seq_list->elements[i];                  // (复制为哨兵)
            seq_list->elements[i] = seq_list->elements[i - 1];

            int j;
            for (j = i - 1; LessThan(seq_list->elements[0].key, seq_list->elements[j].key); --j)
            {
                seq_list->elements[j + 1] = seq_list->elements[j];                //记录后移
            }
            seq_list->elements[j + 1] = seq_list->elements[0];                  //插入到正确位置
        }
    }
}


/*!
 * \brief <h1>折半插入排序<h1>
 * \param seq_list 待排序线性表
 */
void BinaryInsertSort(seq_list_t* seq_list) {
    for (int i = 2; i <= seq_list->length; i++) {
        seq_list->elements[0] = seq_list->elements[i];  //将seq_list->elements[i]暂存到seq_list->elements[0]

        int low = 1;
        int high = i - 1;

        while (low <= high) {
            int mid = (low + high) / 2;                       //折半

            if (LessThan(seq_list->elements[0].key, seq_list->elements[mid].key)) {
                high = mid - 1;                             //插入点在低半区
            } else {
                low = mid + 1;                              //插入点在高半区
            }
        }

        for (int j = i - 1; j >= high + 1; --j) {
            seq_list->elements[j + 1] = seq_list->elements[j];                  //记录后移
        }

        seq_list->elements[high + 1] = seq_list->elements[0];                 //插入
    }
}


/*!
 * <h1>按照间隔gap进行希尔插入排序</h1>
 * @param seq_list **顺序表**(指针)
 * @param gap 间隔
 */
void ShellInsert(seq_list_t* seq_list, int gap) {
    for (int i = gap + 1; i <= seq_list->length; i++) {
        if (LessThan(seq_list->elements[i].key, seq_list->elements[i - gap].key)) {
            seq_list->elements[0] = seq_list->elements[i];
            int j;
            for (j = i - gap; j > 0 && LessThan(seq_list->elements[0].key, seq_list->elements[j].key); j -= gap) {
                seq_list->elements[j + gap] = seq_list->elements[j];
            }
            seq_list->elements[j + gap] = seq_list->elements[0];
        }
    }
}


/*!
 * 希尔排序
 * @param seq_list 线性表(指针)
 * @param gaps 间隔数组
 * @param gap_count 间隔数组长度
 */
void ShellSort(seq_list_t* seq_list, int* gaps, int gap_count) {
    for (int i = 0; i < gap_count; ++i) {
        ShellInsert(seq_list, gaps[i]);
    }
}


/*!
 * @brief <h1>冒泡排序</h1>
 * @param seq_list **线性表**(指针)
 * @note
 * 注意: 索引从1开始
 */
void BubbleSort(seq_list_t* seq_list) {
    /// **for loop** length - 1 次: \n
    for (int i = 0; i < seq_list->length; i++) {
        /// &emsp; 在本趟冒泡前设置变量用来检查是否已经有序
        int is_sorted = TRUE;

        for (int j = 1; j < seq_list->length - i; j++) {
            if (LessThan(seq_list->elements[j + 1].key, seq_list->elements[j].key)) {
                Swap(seq_list->elements + j + 1, seq_list->elements + j);
                is_sorted = FALSE;
            }
        }

        if (is_sorted == TRUE) {
            break;
        }
    }
}


/*!
 * 快速排序划分函数
 * @param seq_list 线性表(指针)
 * @param low 下界
 * @param high 上界
 * @return 划分位置
 */
int Partition(seq_list_t* seq_list, int low, int high) {

    int pivot_key = seq_list->elements[low].key;

    while (low < high) {
        while (low < high && seq_list->elements[high].key >= pivot_key) {
            high--;
        }

        Swap(seq_list->elements + high, seq_list->elements + low);

        while (low < high && seq_list->elements[low].key <= pivot_key) {
            low++;
        }

        Swap(seq_list->elements + high, seq_list->elements + low);
    }

    return low;
}


/*!
 * 快速排序划分函数
 * @param seq_list 线性表(指针)
 * @param low 下界
 * @param high 上界
 * @return 划分位置
 */
int Partition2(seq_list_t* seq_list, int low, int high) {
    int pivot_key;

    //变换顺序表L中子表r[low,high]的记录，枢轴记录到位，并返回其所在位置，此时
    //在它之前（后）的记录均不大（小）于它。
    seq_list->elements[0] = seq_list->elements[low];                    //用子表第一个记录作枢轴记录
    pivot_key = seq_list->elements[low].key;                 //枢轴记录关键字

    while (low < high)
    { //从表的两端交替地向中间扫描
        while (low < high && seq_list->elements[high].key > pivot_key) {
            high--;
        }

        seq_list->elements[low] = seq_list->elements[high];               //将比枢轴记录小的记录交换到低端

        while (low < high && seq_list->elements[low].key <= pivot_key) {
            low++;
        }

        seq_list->elements[high] = seq_list->elements[low];               //将比枢轴记录大的记录交换到高端
    }

    seq_list->elements[low] = seq_list->elements[0];                    //枢轴记录到位

    return low;                                 //返回枢轴所在位置
}


/*!
 * 快速排序(递归)
 * @param seq_list 顺序表(指针)
 * @param left 表左侧位置
 * @param right 表右侧位置
 */
void QuickSortRecursive(seq_list_t* seq_list, int left, int right) {
    if (left >= right) {
        return;
    }

    // 划分出分治点位置
    int pivot = Partition2(seq_list, left, right);

    QuickSortRecursive(seq_list, 1, pivot - 1);        //!< 左侧递归执行QuickSortRecursive
    QuickSortRecursive(seq_list, pivot + 1, right);    //!< 右侧递归执行QuickSortRecursive
}


/*!
 * @brief 顺序表快速排序
 * @param seq_list 顺序表(指针)
 */
void QuickSort(seq_list_t* seq_list) {
    int starting_index = 1; //!< 顺序表的起始索引为1(区别于数组0)

    QuickSortRecursive(seq_list, starting_index, seq_list->length);
}


/*!
 * @brief 简单选择排序
 * @param seq_list 待排数组
 */
void SelectSort(seq_list_t* seq_list) {
    for (int i = 1; i < seq_list->length; i++) {
        int j = SelectMinKey(seq_list, i);  //!< 在seq_list->elements[ i ... seq_list->length ]中选择key最小的记录

        if (i != j) {
            Swap(seq_list->elements + i, seq_list->elements + j); //与第i个记录交换
        }
    }
}


/*!
 * 大顶堆SiftDown
 * @param heap 顺序表结构(通常可以是数组)
 * @param index 位置索引
 * @param heap_size 堆size
 */
void MaxHeapSiftDown(seq_list_t* heap, int index, int heap_size)
{
    for (int child_index = 2 * index; child_index <= heap_size; index = child_index, child_index *= 2) {
        if (child_index < heap_size && LessThan(heap->elements[child_index].key, heap->elements[child_index + 1].key)) {
            child_index++;
        }

        if (!LessThan(heap->elements[index].key, heap->elements[child_index].key)) {
            break;
        }

        Swap(heap->elements + index, heap->elements + child_index);
    }
}


/*!
 * 堆排序
 * @param heap 顺序表结构(通常可以是数组)
 * @note
 * 通常heap可以使用数组
 */
void HeapSort(seq_list_t* heap)
{
    // 对数组heap->elements[1 ... heap->length]建立大顶堆
    for (int i = heap->length / 2; i > 0; i--) {
        MaxHeapSiftDown(heap, i, heap->length);
    }

    for (int i = heap->length; i > 1; --i) {
        Swap(&heap->elements[1], &heap->elements[i]);
        MaxHeapSiftDown(heap, 1, i - 1);
    }
}


// @brief 两个有序表归并为一个有序表
// @param SR 有序表
// @param TR 返回的有序表
// @param i SR起始位置
// @param m SR归并中点
// @param n SR终止位置
void Merge(seq_list_node_t SR[], seq_list_node_t TR[], int i, int m, int n)
{
    int j;
    int k;
    //将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n]
    for (j = m + 1, k = i; i <= m && j <= n; ++k) {            //将SR中记录由小到大地并入TR
        if (LessThanOrEqual(SR[i].key, SR[j].key))
        {
            TR[k] = SR[i++];
        }
        else
        {
            TR[k] = SR[j++];
        }
    }

    while (i <= m) {                                          //将剩余的SR[i..m]复制到TR
        TR[k++] = SR[i++];
    }
    while (j <= n) {                                         //将剩余的SR[j..n]复制到TR
        TR[k++] = SR[j++];
    }
}


// todo: 写的不太好, 重写
void MergeSortRecursive(seq_list_node_t* SR, seq_list_node_t* TR1, int left, int right)
{
    seq_list_node_t TR2[MAX_SIZE + 1];
    // 将SR[left..right]归并排序为TR1[left..right]
    if (left == right) {
        TR1[left] = SR[left];
    } else {
        int mid = (left + right) / 2;                                      //将SR[left..right]平分为SR[left..mid]和SR[mid+1..right]
        MergeSortRecursive(SR, TR2, left, mid);                                 //递归地将SR[left..mid]归并为有序的TR2[left..mid]
        MergeSortRecursive(SR, TR2, mid + 1, right);                             //递归地将SR[mid+1..right]归并为有序的TR2[mid+1..right]
        Merge(TR2, TR1, left, mid, right);                             //将R[left..mid]和TR2[mid+1..right]归并到TR1[left..right]
    }
}


void MergeSort(seq_list_t* L)
{
    //对顺序表L作归并排序
    MergeSortRecursive(L->elements, L->elements, 1, L->length);
}


/*!
 * 获取keys第
 * @param keys
 * @param i
 * @param digit_num
 * @return
 */
int ord(char* keys, int i) {
    // int index = digit_num - i - 1;
    int num = (int)keys[i] - NUM_0_ASCII_CODE;

    return num;
}


/*!
 * @brief 基数排序分配元素入桶
 * @param static_linked_list 静态链表(指针)
 * @param place_of_digit 位数
 * @param digit_bucket_heads 数位(0 - 9)桶的首元素(队头)
 * @param digit_bucket_tails 数位(0 - 9)桶的尾元素(队尾)
 * @note
 * place_of_digit/位数, 个位: 1, 十位: 2, 百位: 3 ...
 * 每个桶是一个队列,
 * digit_bucket_heads[0 ... 9]和digit_queue_tails[0 ... 9]分别指向各桶(队列)的第一个元素(队头)和最后一个元素(队尾)
 */
void DistributeIntoBuckets(radix_static_linked_list_t* static_linked_list,
                           int place_of_digit,
                           BUCKETS digit_bucket_heads,
                           BUCKETS digit_bucket_tails)
{
    static_linked_list_node_t* elements = static_linked_list->elements;
    int digit_index = static_linked_list->digit_number - place_of_digit;


    // 0 - 9对应的各子表初始化为空表
    for (int j = 0; j < RADIX_10; j++) {
        digit_bucket_heads[j] = 0;
        digit_bucket_tails[j] = 0;
	}

	for (int elements_index = elements[0].next; elements_index != 0; elements_index = elements[elements_index].next) {

        // 获取第i个关键字对应的数字
        int digit = ord(static_linked_list->elements[elements_index].keys, digit_index);

        if (!digit_bucket_heads[digit]) {    // 如果digit所在队列的队头元素为空, elements_index入队
            digit_bucket_heads[digit] = elements_index; // elements_index设为队头
        } else {    // 如果digit所在队列的队头元素不为空, 队尾元素对应的elements数组元素的next, 指向elements_index(即加入队尾)
            elements[digit_bucket_tails[digit]].next = elements_index;    // 队尾增加元素
        }

        digit_bucket_tails[digit] = elements_index;  // 更新队尾数组digit_queue_tails
	}
}


/*!
 * 基数排序收集桶
 * @param elements 元素数组
 * @param digit_bucket_heads 数位(0 - 9)桶的首元素(队头)
 * @param digit_bucket_tails 数位(0 - 9)桶的尾元素(队尾)
 * @note
 * digit]自小至大, 将digit_queue_heads[0 ... 9]所指各桶, 依次连接成一个链表
 */
void CollectBuckets(static_linked_list_node_t* elements,
                    BUCKETS digit_bucket_heads,
                    BUCKETS digit_bucket_tails)
{

    // 找第一个非空子表
    int digit = 0;
    while (digit_bucket_heads[digit] == 0) {
        digit++;
    }

    elements[0].next = digit_bucket_heads[digit];       //!< elements[0].next指向第一个非空桶的第1个结点
    int digit_bucket_tail = digit_bucket_tails[digit];  //!< 第1个桶的最后1个元素的elements数组索引

    while (digit < RADIX_10) {

        // 寻找下一个非空桶
        digit++;    // 第1个非空桶的下一个桶
        while (digit < RADIX_10 && digit_bucket_heads[digit] == 0) {
            digit++;
        }

        // 找不到非空桶, 退出
        if (digit == RADIX_10) {
            break;
        }

        elements[digit_bucket_tail].next = digit_bucket_heads[digit];   // 上一个桶的最后一个元素的next, 指到下一个桶的head
        digit_bucket_tail = digit_bucket_tails[digit];  // digit_bucket_tail指向新的非空桶的tail
    }

    elements[digit_bucket_tail].next = 0;   // elements[digit_bucket_tail].next指向0(代表所有桶Collection结束)
}


/*!
 * 基数排序
 * @param static_linked_list 待排序静态链表
 */
void RadixSort(radix_static_linked_list_t* static_linked_list) {
    int digit_queue_heads[10];
    int digit_queue_tails[10];

    // 初始化static_linked_list
    for (int i = 0; i < static_linked_list->length; ++i) {
        static_linked_list->elements[i].next = i + 1;
    }

    static_linked_list->elements[static_linked_list->length].next = 0; // 最后一个元素的next指向0

    // 按最低位优先(右侧起始), 依次对各关键字进行分桶和收集
    for (int i = 1; i <= static_linked_list->digit_number; i++) {

        //!< 以从右起第i位作为基数分桶
        DistributeIntoBuckets(static_linked_list, i, digit_queue_heads, digit_queue_tails);

        //!< 对分完的桶, 进行收集
        CollectBuckets(static_linked_list->elements, digit_queue_heads, digit_queue_tails);
    }
}
