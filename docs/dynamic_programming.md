# 动态规划 （Dynamic Programming, DP 问题）

# 基本概念
1. **阶段**：阶段是整个过程的自然划分，通常按时间顺序或空间特征划分阶段；
2. **状态**：状态表示每个阶段开始时过程所处的自然状态或客观条件。动态规划的状态应该具有如下性质：**某个阶段的状态确定后，这个阶段以后过程的发展不受这个阶段以前各阶段状态的影响**，这种性质称为无后效性。
3. **决策**：当一个阶段的状态确定后，可以做出不同的选择从而演变到下一个阶段的某个状态。这种选择手段称为决策，在最优控制问题中也称为控制。
4. **策略**：有策略组成的序列称为策略。
5. **状态转移方程**：在确定性的过程中，一旦某阶段的状态和策略为已知，则下阶段的状态便完全确定。
6. **指标函数和最优值函数**：制表函数是衡量过程优劣的数量指标，它是定义在全过程和所有后部子过程上的数量函数。指标函数应具有可分离性。
7. **最优策略和最优轨线**： 使指标函数达到最优值的策略是从k开始的后部子过程的最优策略。
8. **递归方程**

# 求解步骤
如果一个问题可以用动态规划方程求解，那么我们可以按下列步骤，首先建立起动态规划的数学模型：
1. 将过程划分为恰当的阶段；
2. 正确选择状态变量 `x[k]`，使它既能描述过程的状态，又满足无后效性，同时确定允许状态集合 `X[k]`;
3. 选择决策变量 `u[k]`，确定允许决策集合`U[k](x[k])`;
4. 写出状态转移方程；
5. 确定阶段指标 `v[k](x[k], u[k])` 及指标函数 `V[k][n]`的形式（阶段指标纸盒，阶段指标之积，阶段指标之极大或极小等）;
6. 写出基本方程即最优值函数满足的递归方程，及端点条件。

# 原理
通常使用四个步骤来设计一个动态规划算法：
1. 刻画一个最优解的结构特征；
2. 递归的定义最优解的值（递归公式）；
3. 计算最优解的值，通常采用自底向上的方法；
4. 利用计算出的信息构造一个最优解

**动态规划问题的求解方法**：直接递归、备忘录递归（带备忘的自顶向下发）、自底向上法

适合应用动态规划方法求解的最优化问题应该具备两个要素：**最优子结构**和**子问题重叠**。

## 最优子结构
如果一个问题的最优解包括其子问题的最优解，我们就称此问题具有最优子结构性质。
发掘最优子结构性质的过程中遵循了如下通用模式：
1. 证明问题最优解的第一个组成部分是做出一个选择，做出此类选择会产生一个或多个待解的子问题；
2. 对于一个给定的问题，在其可能的第一步选择中，假定已经知道那种选择才会得到最优解；
3. 得定可获得最优解的选择后，确定会产生哪些子问题，以及如何最好的刻画子问题空间；
4. 利用“剪切-粘贴”计数证明：作为构成原问题最优解的组成部分，每个子问题的解，就是它本身的最优解。

## 注意问题是否具有最优子结构性质
- 无权最短路径：对于有向图，找到一条从u到v的边数最少的路径。**具有最优子结构性质**
- 无权最长路径：找到一条从u到v的边数最多的简单路径。**不具有最优子结构性质，NP完全问题**

## 重叠的子问题
适合动态规划方法求解的问题的第二个性质是子问题空间足够小，即问题的递归算法会反复求解相同的子问题，而不是一直生成新的子问题。
如果递归算法反复的求解相同的子问题，就称最优化问题具有重叠子问题，反之适合使用分治方法求解的问题通常在每一步都生成全新的子问题。

## 重构最优解
通常将每个子问题所做的选择存在一个表中，这样就不必根据代价值来重构这些信息。

## 备忘录
保持自顶向下的策略又可以获得与自底向上的动态规划方法相当的效率，可以通过加入备忘机制，记录已经求解的子问题的解。

# 经典例题
## 钢条切割
现有长度为 n 的钢条和价目表 pi ，希望切割钢条获得最大收益


| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | 
| Length i | 1 | 2 | 3 | 4 | 5  | 6  | 7  | 8  | 9  | 10 |
| Price pi | 1 | 5 | 8 | 9 | 10 | 17 | 17 | 20 | 24 | 30 |

使用r[i] 表示长度为 i 的钢条切割后的最佳收益，则递归求解公式`r[n] = max(p[n], r[1] + r[n-1], r[2] + r[n-2], ... , r[n-1] + r[1])`

```
// 直接递归的方法
CUT-ROD(p, n)
    if n == 0
        return 0
    q = INT_MIN
    for i = 1 to n
        q = max(q, p[i] + CUT-ROD(p, n-i))
    return q

// 备忘的自顶向下递归求解
MEMOIZED-CUT-ROD(p, n)
    let r[0..n] be a new array
    for i = 0 to n
        r[i] = INT_MIN
    return MEMOIZED-CUT-ROD-AUX(p, n, r)

MEMOIZED-CUT-ROD-AUX(p, n, r)
    if r[n] >= 0
        return r[n]
    if n == 0
        q = 0
    else
        q = INT_MIN
        for(i = 1 to n)
            q = max(q, p[i] + MEMOIZED-CUT-ROD-AUX(p, n-i, r))
    r[n] = q
    return q

// 自底向上的求解方法
Bottom-UP-CUT-ROD(p, n)
    let r[0..n] be a new array
    r[0] = 0
    for j = 1 to n
        q = INT_MIN
        for i = 1 to j
            q = max(q, p[i] + r[j-i])
        r[j] = q
    return r[n]

// 保存结果
EXTENDED-BOTTOM-UP-CUT-ROD(p, n)
    let r[0..n] and s[0..n] be new arrays
    r[0] = 0
    for j = 1 to n
        q = INT_MIN
        for i = 1 to j 
            if q < p[i] + r[j-i]
                q = p[i] + r[j-i]
                s[j] = i
        r[j] = q
    return r and s

// 输出结果
PRINT-CUT-ROD-SOLUTION(p, n)
    (r, s) = EXTENDED-BOTTOM-UP-CUT-ROD(p, n)
    while n > 0
        print s[n]
        n = n - s[n]
```

## 矩阵链乘法
多个矩阵相乘，适当的调用结合律，可以减少乘法的调用次数，找到最短的调用次数

**递归求解公式**
```
m[i, j] = 0 if i = j
m[i, j] = min(m[i, k] + m[k + 1, j] + p[i-1] * p[k] * p[j]) if i < j


// 计算矩阵相乘
MATRIX-MULTIPLY(A, B)
    if A.columns != B.rows
       error "incompatible dimensions"
    else
        let C be a new A.rows * B.columns matrix
        for i = 1 to A.rows
            for j = 1 to B.columns
                c[i][j] = 0
                for k = 1 to A.columns
                    c[i][j] = c[i][j] + a[i][k] * b[k][j]
        return C

// 自底向上
MATRIX-CHAIN-ORDER(p)
    n = p.length - 1
    let m[1..n, 1..n] and s[1..n-1, 2..n] be new tables
    for i = 1 to n
        m[i, i] = 0
    for l = 2 to n
        for i = 1 to n-l+1
            j = i+l-1
            m[i, j] = INT_MAX
            for k = i to j-1
                q = m[i, k] + m[k+1, j] + p[i-1] * p[k] * p[j]
                if q < m[i, j]
                    m[i, j] = q
                    s[i, j] = k
    return m and s

// 输出
PRINT-OPTIMAL-PARENS(s, i, j)
    if i == j
        print "A"
    else
        print "("
        PRINT-OPTIMAL-PARENS(s, i, s[i, j])
        PRINT-OPTIMAL-PARENS(s, s[i, j] + 1, j)
        print ")"

// 备忘录
MEMOIZED-MATRIX-CHAIN(p)
    n = p.length - 1
    let m[1..n, 1..n] be a new table
    for i = 1 to n
        for j = i to n
            m[i, j] = INT_MAX
    return LOOKUP-CHAIN(m, p, 1, n)

LOOKUP-CHAIN(m, p, i, j)
    if m[i, j] < INT_MAX
        return m[i, j]
    if i == j
        m[i, j] = 0
    else
        for k = i to j - 1
            q = LOOKUP-CHAIN(m, p, i, k) + LOOKUP-CHAIN(m, p, k+1, j) + p[i-1]p[k]p[j]
            if q < m[i, j]
                m[i, j] = q
    return m[i, j]
```


## 最长公共子序列 （LCS， Longest Common Subsequence）
对于两个字符串S1和S2，找到第三个字符串S3，使得S3的所有字符均按顺序出现在字符S1和S2中，找到最长的S3。

最长公共子序列问题形式化定义如下：给定一个序列 X=<x1, x2, ..., xm>，另一个序列 Z=<z1, z2, ..., zk>满足如下条件时称为X的子序列，
即存在一个严格递增的X的下标序列<i1, i2, ..., ik> 对所有的j=1, 2, 3, ..., k，满足x[ij] = z[j]。

给定两个序列X和Y，如果Z既是X的的子序列，也是Y的子序列，则称它是X和Y的公共子序列。

### 最长公共子序列的特征
X = {x1, x2, ..., xm}, y = {y1, y2, ..., un}， 最长公共子序列 Z = {z1, z2, ..., zk}
1. if xm = yn, 则 zk = xm =yn, 即 Z(k-1) 是 X(m-1) 和 Y(n-1)的最长公共子序列；
2. if xm != yn, 如果 zk != xm, 则 Z(k) 是 X(m-1) 和 Y（n）的最长公共子序列；
3. if xm != yn, 如果 zk != yn, 则 Z(k) 是 X(m) 和 Y(n-1) 的最长公共子序列；

### 递归的最优解的形式
另c[i, j] 代表X(i)和Y(j)最优解的长度：

```
c[i, j] = 0 ,if i = 0 or j = 0
c[i, j] = c[i-1, j-1] +1 ,if i,j >0 and xi == yj
c[i, j] = max(c[i, j-1], c[i-1, j]) ,if i,j > 0 and xi != yi
```

### 伪代码
```
LCS-LENGTH(X, Y)
    m = X.length
    n = Y.length
    let b[1..m, 1..n] and c[0..m, 0..n] be new tables
    for i =1 to m
        c[i, 0] = 0
    for j = 0 to n
        c[0, j] = 0
    for i = 1 to m
        for j = 1 to n
            if x[i] == y[j]
                c[i, j] = c[i-1, j-1] + 1
                b[i, j] = "up-left"
            else if c[i-1, j] >= c[i, j-1]
                c[i, j] = c[i-1, j]
                b[i, j] = "up"
            else
                c[i, j] = c[i, j-1]
                b[i, j] = "left"
    return c and b

PRINT-LCS(b, X, i, j)
    if i == 0 or j == 0
        return
    if b[i, j] == "up-left"
        PRINT-LCS(b, X, i-1, j-1)
        print x[i]
    else if b[i, j] == "up"
        PRINT-LCS(b, X, i-1, j)
    else
        PRINT-LCS(b, X, i, j-1)
```


## 最优二叉搜索树
希望二叉搜索书上的每个结点，访问频率最高的在更靠近根部的位置，访问频率低的在靠近叶子的位置，结点的位置与访问频率有关系。
构造一棵期望搜索代价最小的二叉搜索树，称为最优二叉搜索树。

最优子结构：如果一棵最优二叉搜索树 T 有一棵包括关键字 k[i], .., k[j] 的子树 T' ，
那么 T' 必然是包括关键字k[i], .., k[j]和伪关键字 d[i-1], .., d[j] 的子问题的最优解。

递归表达:
w(i, j) = sum(p[l], l from i to j ) + sum(q[l], l from i-1 to j)

e[i, j] = q[i-1], when j == i-1

e[i, j] = min(e[i, r-1] + e[r+1, j] + w(i, j), i <= r <=j) i <= j 

```
E[T] = for (node i:tree){sum += (depth(i)+1) * p[i]}
     = 1 + for(node i: tree){sum += depth(i) * p[i]}



OPTIMAL-BST(p, q, n)
    let e[1..n+1, 0..n], w[1..n+1,0..n], and root[1..n,1..n] be new tables
    for i = 1 to n + 1
        e[i, i-1] = q[i-1]
        w[i,i-1] = q[i-1]
    for l = 1 to n
        for i = 1 to n-l+1
            j = i+l-1
            e[i, j] = INT_MAX
            w[i, j] = w[i, j-1] + p[j] + q[j]
            for r = i to j
                t = e[i, r-1] + e[r+1, j] + w[i, j]
                if t < e[i, j]
                    e[i, j] = t
                    root[i, j] = r
    return e and root
```


## 最短路径
TODO:
## 资源分配问题 
TODO:
## 最长递增子序列
TODO:
## 最大子段和问题
TODO:
## 0-1 背包问题 
TODO:

# Leetcode
## [70. 爬楼梯](https://leetcode-cn.com/problems/climbing-stairs)
TODO:
## [322. Coin Change](https://leetcode.com/problems/coin-change/)
TODO:
## [300. 最长上升子序列](https://leetcode-cn.com/problems/longest-increasing-subsequence/)
TODO:
## [139. Word Break](https://leetcode.com/problems/word-break/)
TODO:
## [198. 打家劫舍](https://leetcode-cn.com/problems/house-robber)
TODO:
## [213. 打家劫舍 II](https://leetcode-cn.com/problems/house-robber-ii)
TODO:
## [91. Decode Ways](https://leetcode.com/problems/decode-ways/)
TODO:
## [62. Unique Paths](https://leetcode.com/problems/unique-paths/)
TODO:
## [55. Jump Game](https://leetcode.com/problems/jump-game/)
TODO:

# Reference
1. [Algorithm 3rd]()
2. [yangshun.github.io](https://yangshun.github.io/tech-interview-handbook/algorithms/dynamic-programming)