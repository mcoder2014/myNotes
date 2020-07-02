# 排序算法 Sort algorithms

## 插入排序 Insertion Sort

插入排序，时间复杂度O(n^2)

```fake
INSERTION-SORT(A)
for j = 2 to A.length
    key = A[j]
    // Insert A[j] into the sorted sequence A[1..j-1].
    i = j - 1
    while i > 0 and A[i] > key
        A[i+1] = A[i]
        i = i - 1
    A[i+1] = key
```

### 插入排序复杂度

时间复杂度：

* 在插入排序中，当待排序数组是有序时，是最优的情况，只需当前数跟前一个数比较一下就可以了，这时一共需要比较N- 1次，时间复杂度为 O(N)。
* 最坏的情况是待排序数组是逆序的，此时需要比较次数最多，总次数记为：1+2+3+…+N-1，所以，插入排序最坏情况下的时间复杂度为 O(N^2)。
* 平均 O(N^2)

空间复杂度：　O(1)

## 选择排序

第一次从待排序的数据元素中选出最小（或最大）的一个元素，存放在序列的起始位置，然后再从剩余的未排序元素中寻找到最小（大）元素，然后放到已排序的序列的末尾。以此类推，直到全部待排序的数据元素的个数为零。选择排序是**不稳定的排序方法**。

### 选择排序复杂度

时间复杂度：

* 最好 O(N)
* 最坏 O(N^2)
* 平均 O(N^2)

## 冒泡排序

它重复地走访过要排序的元素列，依次比较两个相邻的元素，如果顺序（如从大到小、首字母从Z到A）错误就把他们交换过来。走访元素的工作是重复地进行直到没有相邻元素需要交换，也就是说该元素列已经排序完成。

这个算法的名字由来是因为越小的元素会经由交换慢慢“浮”到数列的顶端（升序或降序排列），就如同碳酸饮料中二氧化碳的气泡最终会上浮到顶端一样，故名“冒泡排序”。

### 冒泡排序复杂度

时间复杂度

* 最好 O(N)
* 最坏 O(N^2)
* 平均 O(N^2)

## 归并排序 Merge Sort

归并排序属于分治法，分治法在结构上是递归的，将原问题分解为几个规模较小但类似于原问题的子问题，递归地求解这些子问题，然后再合并这些子问题的解来建立原问题的解。
时间复杂度O(nlogn)

分治法在每层递归时都包含三个步骤：

* 分解：分解原问题为若干子问题，这些子问题是原问题的规模较小的实例。
* 解决：解决这些子问题，递归地求解各子问题。如果子问题的规模足够小，就可以直接求解。
* 合并：将子问题的解合并为原问题的解。

### 归并排序复杂度

时间复杂度：

* 最好 O(nlogn)
* 最坏 O(nlogn)
* 平均 O(nlogn)

空间复杂度 O(n)

### 归并排序伪代码

```fake

// 合并子步骤
MERGE(A, p, q, r)
n1 = q - p + 1
n2 = r - q
let L[1..n1+1] and R[1..n2 + 1] be new arrays
for i = 1 to n1
    L[i] = a[p + i - 1]
for j = 1 to n2
    R[j] = a[q + j - 1]
L[n1 + 1] = num_range.max()
R[n2 + 1] = num_range.max()
i = 1
j = 1
for k = p to rshijianfuzadu
    if L[i] <= R[j]
        A[k] = L[i]
        i = i + 1
    else
        A[k] = R[j]
        j = j+1

// 归并排序
MERGE-SORT(A, p, r)
if p < r
    q = (p + r)/2
    MERGE-SORT(A, p, q)
    MERGE-SORT(A, q+1, r)
    MERGE(A, p, q, r)
```

## Heapsort 堆排序

堆指的是完全二叉树，分为最大堆最小堆。用数组表示时，很容易找到父子节点， 找到i节点的父节点 `parient(i) = i/2;`，左子节点 `left(i) = 2 * i;`， 右子节点 `right(i) = 2 * i + 1;`.

### 堆有一些基本过程

* **维护堆性质的过程** Max-Heapify 过程，时间复杂度 `O(logn)`，是维护最大堆性质的关键;将堆的末端子节点作调整，使得子节点永远小于父节点
* **构建最大堆过程** Build-Max-Heap 过程，具有线性时间复杂度 `O(N)`，功能是从无序的输入数组中构造一个最大堆;
* **堆排序过程** Heapsort 过程，时间复杂度`O(nlogn)`，功能是对一个数组进行原址排序;
* Max-Heap-Insert, Heap-Extract-Max, Heap-Increase-Key, Heap-Maximum 过程，时间复杂度`O(logn)`，利用堆数据结构实现一个优先队列;

### 大顶堆排序伪代码

```python

// 找到父节点
PARIENT(i)
    return i/2

// 找到左孩子节点
LEFT(i)
    return 2 * i

// 找到右孩子节点
RIGHT(i)
    return 2 * i + 1

// 维护堆性质
// 找到三个节点中的最大的
MAX-HEAPIFY(A, i)
    l = LEFT(i)
    r = RIGHT(i)
    largest = i
    if l <= A.heap-size and A[l] > a[i]:
        largest = l
    if r <= A.heap-size and A[r] > A[largest]:
        largest = r
    if largest != i
        exchage A[i] with A[largest]
        MAX-HEAPIFY(A, largest)

// 构建最大堆
BUILD-MAX-HEAP(A)
    A.heap-size = A.length
    for i = [A.length/2] downto 1
        MAX-HEAPIFY(A, i)

// 堆排序
// 每次取出最大元素放在尾部，然后继续构维持堆性质
HEAPSORT(A)
    BUILD-MAX-HEAP(A)
    for i = A.length downto 2
        exchange A[1] with A[i]
        A.heap-size = A.heap-size - 1
        MAX-HEAPIFY(A,i)
```

## Leetcode

### [23. Merge k Sorted Lists](https://leetcode.com/problems/merge-k-sorted-lists/)

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 向一个同一个链表插入
        ListNode *head = nullptr;
        ListNode *ptr = nullptr;


        for(ListNode* l:lists)
        {
            ptr = head; // 从链表头部开始
            while(l != nullptr)
            {
                // 向 head 链表插入当前的结点
                if(ptr == nullptr)
                {
                    ptr = new ListNode(l->val);
                    head = ptr;
                    l = l->next;
                    continue;
                }

                while(head!=nullptr && l!= nullptr
                      && head->val > l->val)
                {
                    // 插入到头部
                    ListNode *node = new ListNode(l->val);
                    node->next = head;
                    head = node;
                    ptr = head;
                    l = l->next;
                }

                while(ptr->next != nullptr
                      && l!= nullptr
                        && ptr->val < l->val
                      && ptr->next->val < l->val)
                    ptr = ptr->next;

                if(l != nullptr)
                {
                    ListNode *node = new ListNode(l->val);
                    node->next = ptr->next;
                    ptr->next = node;
                    ptr = node;
                    l = l->next;
                }
            }
        }

        return head;
    }
};
```

### [347. Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/)

TODO:

### [295. Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/)

TODO:

## 快排算法 Quick Sort

通过一趟排序将要排序的数据分割成独立的两部分，其中一部分的所有数据都比另外一部分的所有数据都要小，然后再按此方法对这两部分数据分别进行快速排序，整个排序过程可以递归进行，以此达到整个数据变成有序序列。快排是一种分治排序的方法，是原址排序，最差时间复杂度 O(n^2)，平均时间复杂度O(nlogn)。

### 快排伪代码

```fake
QUICKSORT(A, p, r)
    if p < r
        q = PARTITION(A, p, r)
        QUICKSORT(A, p, q-1)
        QUICKSORT(A, q+1, r)

// 划分算法
// 一次划分算法的时间复杂度为 O(n)
PARTITION(A, p, r)
    x = A[r]
    i = p - 1
    for j= p to r-1
        if A[j] <= x
            i++
            exchange A[i] with A[j]
    exchange A[i+1] with A[r]
    return i+1
```

### 快速排序复杂度

时间复杂度：

* 最好 O(nlogn) **每次划分所选择的中间数恰好将当前序列几乎等分**，经过log2n趟划分，便可得到长度为1的子表。
* 最差 O(n^2) **每次所选的中间数是当前序列中的最大或最小元素**，这使得每次划分所得的子表中一个为空表，另一子表的长度为原表的长度-1。
* 平均 O(nlogn)

从空间性能上看，尽管快速排序只需要一个元素的辅助空间，但快速排序需要一个栈空间来实现递归。最好的情况下，即快速排序的每一趟排序都将元素序列均匀地分割成长度相近的两个子表，所需栈的最大深度为log2(n+1)；但最坏的情况下，栈的最大深度为n。这样，快速排序的空间复杂度为O(log2n))。

### 如何优化快速排序

1. 每次选择划分元素的时候，随机选择一个数
2. 更苛刻，每次随机选择三个数，然后用中值作为分隔元素

## 计数排序 Count Sort

假设每一个输入元素都是整数类型，大小从0到k，记下比输入元素小的元素的个数，确定输出位置.
不是基于比较的排序；

```fake
COUNTING-SORT(A, B, k)
    let C[0..k] be a new array
    for i = 0 to k
        C[i] = 0
    for j = 1 to A.length
        C[A[j]] = C[A[j]] + 1
    // C[i] now contains the number of elements equal to i
    for i = 1 to k
        C[i] = C[i] + C[i-1]
    // C[i] new contains the number of elements less than or equal to i
    for j = A.length downto 1
        B[C[A[j]]] = A[j]
        C[A[j]] = C[A[j]] - 1
```

## 基数排序 Radix Sort

对每一位上的数字进行排序，然后从个位一直排到最高位。

```fake
RADIX-SORT(A, d)
    for i = 1 to d
        use a stable sort to sort array A on digit i
```

## 桶排序 bucket sort

桶排序是计数排序的升级版本，利用了函数的映射关系，高效与否的关键在于这个映射函数。桶排序假设输入是[0,1],平均分布的小数，所以很少出现落在同一个区间的情况，平均时间复杂度O(n)

```fake
BUCKET-SORT(A)
    let B[0..n-1] be a new array
    n = A.length
    for i = 0 to n - 1
        make B[i] an empty list
    for i = 1 to n
        insert A[i] into list B[[nA[i]]]
    for i = 0 to n-1
        sort list B[i] with insertion sort
    concatenate the lists B[0], B[1], ..., B[n-1] together in order
```

## 基数排序 vs 计数排序 vs 桶排序

这三种排序都用到了桶的概念，但对桶的使用方法上有区别：

* 基数排序：根据键值的每一位数字来分配桶；
* 计数排序：每个桶只存储单一键值；
* 桶排序：每个桶存储一定范围的数值；

## 希尔排序

希尔排序(Shell's Sort)是插入排序的一种又称“缩小增量排序”（Diminishing Increment Sort），是直接插入排序算法的一种更高效的改进版本。希尔排序是非稳定排序算法。

希尔排序是把记录按下标的一定增量分组，对每组使用直接插入排序算法排序；随着增量逐渐减少，每组包含的关键词越来越多，当增量减至1时，整个文件恰被分成一组，算法便终止。

希尔排序是基于插入排序的以下两点性质而提出改进方法的：

1. 插入排序在对几乎已经排好序的数据操作时，效率高，即可以达到线性排序的效率。
2. 但插入排序一般来说是低效的，因为插入排序每次只能将数据移动一位。

排序过程：先取一个正整数 `d1<n`，把所有序号相隔d1的数组元素放一组，组内进行直接插入排序；然后取`d2<d1`，重复上述分组和排序操作；直至di=1，即所有记录放进一个组中排序为止。例如：取 `di = 5, 2, 1`分组排序三次

## 随机选择算法 Random Select Algorithm

**问题描述**：为了快速找到一组数列中第i个大小的元素

**解决方法** 利用快排算法思路，剪掉了一个分支，期望的时间复杂度O(n)，最坏时间复杂度O(n^2)

```fake
RANDOMIZED-SELECT(A, p, r, i)
    if p == r
        return A[p]
    q = RANDOMIZED-SELECT(A, p, r)
    k = q - p + 1
    if i == k   // the pivot value is the answer
        return A[q]
    elseif i < k
        return RANDOMIZED-SELECT(A, p, q-1, i)
    else
        return RANDOMIZED-SELECT(A, q + 1, r, i - k)
```

## reference

1. [Algorithms 3rd](https://item.jd.com/11144230.html)
