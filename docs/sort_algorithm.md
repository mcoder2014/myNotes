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