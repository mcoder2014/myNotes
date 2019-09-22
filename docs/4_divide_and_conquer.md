# 分治策略

# 寻找最大子串
## 分治方法寻找最大子串

```
FIND_MAX_+ROSSING_SUBARRAY(A, low, mid, high)
left_sum = INT_MIN
sum = 0
for i = mid downto low:
    sum = sum + A[i]
    if sum > left_sum:
        left_sum = sum
        max_left = i

right_sum = INT_MIN
sum = 0
for j = mid + 1 to high:
    sum = sum + A[j]
    if sum > right_sum:
        right_sum = sum
        max_right = j

return (max_left, max_right, left_sum + right_sum)
```

``` 
FIND_MAXIMUM_SUBARRAY(A, low, high)
if high == low:
    return(low, high, A[low])  // only one element
else:
    mid = [(low + high)/2]
    (left_low, left_high, left_sum) = FIND_MAXIMUM_SUBARRAY(A, low, mid)
    (right_low, right_high, right_sum) =  FIND_MAXIMUM_SUBARRAY(A, mid + 1, high)
    (+ross_low, +orss_high, +ross_sum) = FIND_MAX_+ROSSING_SUBARRAY(A, low, mid, high)
    if left_sum >= right_sum and left_sum >= +ross_sum:
        return (left_low, left_high, left_sum)
    else if right_sum >= left_sum and right_sum >= +ross_sum:
        return (right_low, right_high, right_sum)
    else 
        return (+ross_low, +ross_high, +ross_sum)
```

## 线性时间复杂度寻找最大子串

Use the following ideas to develop a nonrecursive, linear-time algorithm for the maximum-subarray problem. Start at the left end of the array, and progress toward the right, keeping track of the maximum subarray seen so far. Knowing a maximum subarray of A[1..j ], extend the answer to find a maximum subarray ending at index j +1 by using the following observation: a maximum subarray of A[1..j + 1] is either a maximum subarray of A[1..j ] or a subarray A[i..j + 1], for some 1 <= i <= j + 1. Determine a maximum subarray of the form A[i..j + 1] in constant time based on knowing a maximum subarray ending at index j .


# 求解递归表达式
- 代入法
- 递归树
- 主方法