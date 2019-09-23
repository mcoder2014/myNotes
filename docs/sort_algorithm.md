# Sort algorithms

# Insertion Sort
```
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

# Merge Sort 
归并排序属于分治法，分治法在结构上是递归的，将原问题分解为几个规模较小但类似于原问题的子问题，递归地求解这些子问题，然后再合并这些子问题的解来建立原问题的解。
分治法在每层递归时都包含三个步骤：
- 分解：分解原问题为若干子问题，这些子问题是原问题的规模较小的实例。
- 解决：解决这些子问题，递归地求解各子问题。如果子问题的规模足够小，就可以直接求解。
- 合并：将子问题的解合并为原问题的解。

归并排序的合并
```
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
for k = p to r
    if L[i] <= R[j]
        A[k] = L[i]
        i = i + 1
    else 
        A[k] = R[j]
        j = j+1
```

归并排序
```
MERGE-SORT(A, p, r)
if p < r
    q = (p + r)/2
    MERGE-SORT(A, p, q)
    MERGE-SORT(A, q+1, r)
    MERGE(A, p, q, r)
```

# (二叉)堆
## Heapsort 堆排序
堆指的是完全二叉树，分为最大堆最小堆。用数组表示时，很容易找到父子节点， 找到i节点的父节点 `parient(i) = i/2;`，左子节点 `left(i) = 2 * i;`， 右子节点 `right(i) = 2 * i + 1;`.
堆有一些基本过程：
- Max-Heapify 过程，时间复杂度 `O(logn)`，是维护最大堆性质的关键;
- Build-Max-Heap 过程，具有线性时间复杂度，功能是从无序的输入数组中构造一个最大堆;
- Heapsort 过程，时间复杂度`O(nlogn)`，功能是对一个数组进行原址排序;
- Max-Heap-Insert, Heap-Extract-Max, Heap-Increase-Key, Heap-Maximum 过程，时间复杂度`O(logn)`，利用堆数据结构实现一个优先队列;

```
PARIENT(i)
    return i/2

LEFT(i)
    return 2 * i

RIGHT(i)
    return 2 * i + 1
```

### 维持堆的性质
```
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
```

### 构建堆
```
BUILD-MAX-HEAP(A)
    A.heap-size = A.length
    for i = [A.length/2] downto 1
        MAX-HEAPIFY(A, i)
```

### 堆排序
```
HEAPSORT(A)
    BUILD-MAX-HEAP(A)
    for i = A.length downto 2
        exchange A[1] with A[i]
        A.heap-size = A.heap-size - 1
        MAX-HEAPIFY(A,i)
```

## 优先队列
一个最大优先队列维持S个元素，支持如下操作：
- INSERT(S, x) 插入元素
- MAXIMUM(S) 找到最大元素
- EXTRACT-MAX(S) 找到最大元素并从队列中移出最大元素    
- INCREASE-KEY(S, x, k) 调高某一个元素的优先值

相反，最小优先队列支持如下操作：
- INSERT(S, x)
- MINIMUM(S)
- EXTRACT-MIN(S)
- DECREASE-KEY(S, x, k)


### 找到最大值
```
HEAP-MAXIMUM(A)
    return A[1]
```

### 找到并移出最大值
```
HEAP-EXTRACT-MAX(A)
    if A.heap-size < 1
        error "heap underflow"
    max = A[1]
    A[1] = A[A.heap-size]
    A.heap-size = A.heap-size - 1
    MAX-HEAPIFY(A, 1)
    return max
```

### 增大某一个元素的优先值
```
HEAP-INCREASE-KEY(A, i, key)
    if key < A[i]
        error "new key is smaller than current key"
    A[i] = key
    while i > 1 and A[PARENT(i)] < A[i]
        exchange A[i] with A[PARENT[i]]
        i = PARENT[i]
```

### 插入元素
```
MAX-HEAP-INSERT(A, key)
    A.heap-size = A.heap-size + 1
    A[A.heap-size] = -INT_SIZE
    HEAP-INCREASE-KEY(A, A.heap-size, key)
```

# 快排算法
快排是一种分治排序的方法，是原址排序，最差时间复杂度 O(n^2)，平均时间复杂度O(nlogn)。

```
QUICKSORT(A, p, r)
    if p < r
        q = PARTITION(A, p, r)
        QUICKSORT(A, p, q-1)
        QUICKSORT(A, q+1, r)

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