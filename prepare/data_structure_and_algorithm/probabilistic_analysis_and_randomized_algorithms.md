# 概率分析和随机算法

# 随机算法
## 随机排列数组方法
```
Permute_by_sorting(A)
n = A.length
let P[1..n] be a new array
for i = 1 to n:
    P[i] = random(1, n^3)
sort A, using P as sort keys
```

```
randomize_in_place(A)
n = A.length
for i = 1 to n
    swap A[i] with A[random(i,n)]
```