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
 * <h1>在顺序表索引index(包含)之后的元素中选出key最小的元素的索引</h1>
 * @param seq_list **顺序表**
 * @param index **索引**
 * @return **最小元素的索引**
 * @note
 */
int SelectMinKey(seq_list_t* seq_list, int index) {

    /// ### 1 索引范围检查 ###
    /// &emsp; **if** index等于顺序表长度 :\n
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
 * @param seq_list **顺序表**
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
 * \param seq_list 待排序顺序表
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
void ShellInsertSort(seq_list_t* seq_list, int gap) {
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
 * @brief <h1>希尔排序</h1>
 * @param seq_list **顺序表**(指针)
 * @param gaps **间隔数组**
 * @param gap_count **间隔数组长度**
 */
void ShellSort(seq_list_t* seq_list, int* gaps, int gap_count) {
    for (int i = 0; i < gap_count; ++i) {
        ShellInsertSort(seq_list, gaps[i]);
    }
}


/*!
 * @brief <h1>冒泡排序</h1>
 * @param seq_list **顺序表**(指针)
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
 * @param seq_list 顺序表(指针)
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
 * @param seq_list 顺序表(指针)
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
 * @brief <h1>堆排序</h1>
 * @param seq_list **顺序表**
 * @note
 */
void HeapSort(seq_list_t* seq_list) {
    // 对数组heap->elements[1 ... seq_list->length]建立大顶堆
    for (int i = seq_list->length / 2; i > 0; i--) {
        MaxHeapSiftDown(seq_list, i, seq_list->length);
    }

    for (int i = seq_list->length; i > 1; --i) {
        Swap(&seq_list->elements[1], &seq_list->elements[i]);
        MaxHeapSiftDown(seq_list, 1, i - 1);
    }
}


/*!
 * @brief <h1>将顺序表中的两个有序段合并成一个有序段</h1>
 * @param seq_list **顺序表**
 * @param merged_seq_list **合并结果的顺序表**
 * @param left **左侧有序段的左边界**
 * @param mid **两个有序段的中间位置**(左侧段的右边界(包含), 右侧段的左边界(不包含))
 * @param right **右侧有序段的右边界**
 * @note
 */
void Merge(seq_list_node_t* seq_list, seq_list_node_t* merged_seq_list, int left, int mid, int right) {

    /// ### 1 初始化3个遍历变量 ###
    /// &emsp; 合并后的顺序表遍历索引, 初始化为left \n
    int merged_seq_list_index = left;
    /// &emsp; 顺序表执行归并的左侧有序段的遍历索引, 初始化为left \n
    int left_part_index = left;
    /// &emsp; 顺序表执行归并的右侧有序段的遍历索引, 初始化为mid + 1 \n
    int right_part_index = mid + 1;

    /// ### 2 执行合并 ###
    /// &emsp; **for loop** 遍历顺序表两个归并段 : \n
    for (; left_part_index <= mid && right_part_index <= right; merged_seq_list_index++) {
        /// &emsp;&emsp; **if** 左侧归并段当前元素 <= 右侧归并段当前元素 : \n
        if (LessThanOrEqual(seq_list[left_part_index].key, seq_list[right_part_index].key)) {
            /// &emsp;&emsp;&emsp; 左侧归并段当前元素加入合并顺序表尾部 \n
            merged_seq_list[merged_seq_list_index] = seq_list[left_part_index];
            left_part_index++;
        } else {    /// &emsp;&emsp; **else** (左侧归并段当前元素 <= 右侧归并段当前元素) : \n
            /// &emsp;&emsp;&emsp; 右侧归并段当前元素加入合并顺序表尾部 \n
            merged_seq_list[merged_seq_list_index] = seq_list[right_part_index];
            right_part_index++;
        }
    }

    /// &emsp; 将左侧有序段剩余的元素, 加入到合并结果顺序表 \n
    while (left_part_index <= mid) {
        merged_seq_list[merged_seq_list_index] = seq_list[left_part_index];
        merged_seq_list_index++;
        left_part_index++;
    }

    /// &emsp; 将右侧有序段剩余的元素, 加入到合并结果顺序表 \n
    while (right_part_index <= right) {                                         //将剩余的SR[right_part_index..right]复制到TR
        merged_seq_list[merged_seq_list_index] = seq_list[right_part_index];
        merged_seq_list_index++;
        right_part_index++;
    }
}


/*!
 * @brief <h1>归并排序(递归)<h1>
 * @param seq_list **顺序表**
 * @param merged_seq_list **归并结果的顺序表**
 * @param left **归并段左侧边界**
 * @param right **归并段右侧边界**
 * @note
 */
void MergeSortRecursive(seq_list_node_t* seq_list, seq_list_node_t* merged_seq_list, int left, int right) {

    /// ### 1 递归终止条件###
    /// &emsp; **if** 归并段没有元素 : \n
    /// &emsp;&emsp; 直接返回 \n
    if (left > right) {
        return;
    }

    /// &emsp; **if** 归并段只有1个元素 : \n
    /// &emsp;&emsp; 该元素赋值给归并结果顺序表的对应元素 \n
    if (left == right) {
        merged_seq_list[left] = seq_list[left];
        return;
    }

    /// ### 2 递归执行归并 ###
    /// &emsp; 声明缓存顺序表cache_seq_list \n
    seq_list_node_t cache_seq_list[MAX_SEQ_LIST_SIZE + 1];

    /// &emsp; 将seq_list[left ... right]分为 左侧[left ... mid] 和 右侧[mid + 1 ... right] 两部分 \n
    int mid = (left + right) / 2;

    /// - 对左侧部分调用MergeSortRecursive, 进行递归, 归并结果保存在缓存顺序表cache_seq_list
    MergeSortRecursive(seq_list, cache_seq_list, left, mid);
    /// - 对右侧部分调用MergeSortRecursive, 进行递归, 归并结果保存在缓存顺序表cache_seq_list
    MergeSortRecursive(seq_list, cache_seq_list, mid + 1, right);

    /// - 将缓存顺序表cache_seq_list的两部分[left ... mid] 和 [mid + 1 ... right] 合并到merged_seq_list顺序表
    Merge(cache_seq_list, merged_seq_list, left, mid, right);
}


/*!
 * @brief <h1>归并排序</h1>
 * @param seq_list **顺序表**
 * @note
 */
void MergeSort(seq_list_t* seq_list) {
    /// 调用MergeSortRecursive, 对顺序表seq_list做归并排序
    MergeSortRecursive(seq_list->elements, seq_list->elements, 1, seq_list->length);
}


/*!
 * 获取key索引i数位的整型值
 * @param key 关键字
 * @param i 索引
 * @return 值
 * @note
 */
int ord(char* key, int i) {
    /// 关键字索引i的asc码 减去 0的asc码
    int num = (int)key[i] - NUM_0_ASCII_CODE;

    return num;
}


/*!
 * @brief <h1>静态链表按照各元素某数位值, 分配各元素入桶</h1>
 * @param static_linked_list **静态链表**(指针)
 * @param place_of_digit **数位**
 * @param digit_bucket_heads **基数桶的首元素数组**(队头数组)
 * @param digit_bucket_tails **基数桶的尾元素数组**(队尾数组)
 * @note
 * ### 说明 ###
 * &emsp; 以10进制正整数为例
 * - place_of_digit代表数位, 从右侧开始计数, 1: 个位(ones), 2: 十位(tens), 3: 百位(hundreds) ...
 * - 每个桶是一个队列
 *  + digit_bucket_heads[0 ... 9]分别指向各基数桶(队列)的第一个元素(队头)
 *  + digit_queue_tails[0 ... 9]分别指向各基数桶(队列)的最后一个元素(队尾)
 */
void DistributeIntoBuckets(radix_static_linked_list_t* static_linked_list,
                           int place_of_digit,
                           BUCKETS digit_bucket_heads,
                           BUCKETS digit_bucket_tails)
{
    /// ### 1 各基数桶(队列)初始化为空 ###
    /// &emsp; **for loop** 遍历基数数位 :\n
    /// &emsp;&emsp; 基数桶的首元素数组(队头数组)各项设置为0\n
    /// &emsp;&emsp; 基数桶的尾元素数组(队尾数组)各项设置为0\n
    for (int j = 0; j < RADIX_10; j++) {
        digit_bucket_heads[j] = 0;
        digit_bucket_tails[j] = 0;
	}

    /// ### 2 求数位在元素数组中的索引###
    int place_index = static_linked_list->number_of_digit - place_of_digit;

    /// ### 3 遍历静态链表, 执行分配 ###
    static_linked_list_node_t* elements = static_linked_list->elements;
    /// &emsp; **for loop** 遍历静态链表各元素 :\n
	for (int i = elements[0].next; i != 0; i = elements[i].next) {

        /// &emsp;&emsp; 取第i个元素, 数位place_of_digit的数位值\n
        int place_value = ord(static_linked_list->elements[i].key, place_index);

        /// &emsp;&emsp; **if** 该数位对应的桶(队列)为空 :\n
        if (!digit_bucket_heads[place_value]) {
            /// &emsp;&emsp;&emsp; 该数位的数组索引place_index入队(进桶)\n
            digit_bucket_heads[place_value] = i;
        } else {    /// &emsp;&emsp; **else** (如果该数位对应的桶(队列)不为空\n
            /// &emsp;&emsp;&emsp; 队尾元素的next, 指向place_index(即加入队尾)\n
            elements[digit_bucket_tails[place_value]].next = i;
        }

        digit_bucket_tails[place_value] = i;  // &emsp;&emsp; 更新该数位队尾数组元素值\n
	}
}


/*!
 * <h1>基数排序收集桶</h1>
 * @param elements **静态链表元素数组**
 * @param digit_bucket_heads **基数桶的首元素数组**(队头数组)
 * @param digit_bucket_tails **基数桶的尾元素数组**(队尾数组)
 * @note
 * digit自小至大, 将digit_queue_heads[0 ... 9]所指各桶, 依次连接成一个链表
 */
void CollectBuckets(static_linked_list_node_t* elements,
                    BUCKETS digit_bucket_heads,
                    BUCKETS digit_bucket_tails)
{

    /// ### 1 找到第一个非空桶(队列) ###
    /// &emsp; 遍历digit_bucket_heads, 找到第一个非空桶\n
    int place_value = 0;
    while (digit_bucket_heads[place_value] == 0) {
        place_value++;
    }

    /// &emsp; elements[0].next指向第一个非空桶的首结点(第一个非空队列的队头)\n
    elements[0].next = digit_bucket_heads[place_value];
    /// &emsp; 变量digit_bucket_tail保存当前非空桶的最后1个元素
    int digit_bucket_tail = digit_bucket_tails[place_value];

    /// ### 2 执行桶收集 ###
    /// &emsp; **for loop** 数位从0到9 :\n
    while (place_value < RADIX_10) {

        /// &emsp;&emsp; 寻找下一个非空桶\n
        place_value++;
        while (place_value < RADIX_10 && digit_bucket_heads[place_value] == 0) {
            place_value++;
        }

        /// &emsp;&emsp; **if** 找不到非空桶 : \n
        /// &emsp;&emsp;&emsp; 退出
        if (place_value == RADIX_10) {
            break;
        }

        /// &emsp;&emsp; 前一非空桶的最后一个元素(队尾元素)elements[digit_bucket_tail]的next, 指向当前数位对应的非空桶的首个元素的索引(队头)
        elements[digit_bucket_tail].next = digit_bucket_heads[place_value];
        /// &emsp;&emsp; 更新digit_bucket_tail值为当前非空桶的最后一个元素的索引(队尾);
        digit_bucket_tail = digit_bucket_tails[place_value];
    }

    /// &emsp; 最后一个非空桶的最后一个元素(队尾元素)的next指向0
    elements[digit_bucket_tail].next = 0;
}


/*!
 * <h1>基数排序</h1>
 * @param static_linked_list **待排序静态链表**
 * @note
 */
void RadixSort(radix_static_linked_list_t* static_linked_list) {
    int digit_queue_heads[10];  // 基数队列队头数组
    int digit_queue_tails[10];  // 基数队列队尾数组

    /// ### 1 初始化static_linked_list各元素的next ###
    /// &emsp; **for loop** 遍历静态链表, 索引范围[ 1 ... (length - 1) ] : \n
    for (int i = 0; i < static_linked_list->length; ++i) {
        /// &emsp;&emsp; 索引i元素的next, 设置为i + 1 \n
        static_linked_list->elements[i].next = i + 1;
    }

    /// &mesp; 索引length元素的next, 设置为0(构成循环静态链表)
    static_linked_list->elements[static_linked_list->length].next = 0; // 最后一个元素的next指向0

    /// ### 2 按最低位优先(右侧个位开始), 依次对各个位进行分桶和收集 ###
    /// &emsp; **for loop** 从右侧开始, 遍历各个位 :\n
    for (int i = 1; i <= static_linked_list->number_of_digit; i++) {

        /// &emsp;&emsp; 右侧第i位作为基数, 进行分桶 \n
        DistributeIntoBuckets(static_linked_list, i, digit_queue_heads, digit_queue_tails);

        /// &emsp;&emsp; 对分完的桶, 进行收集
        CollectBuckets(static_linked_list->elements, digit_queue_heads, digit_queue_tails);
    }
}
