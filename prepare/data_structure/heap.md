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