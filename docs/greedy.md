# 贪心算法

## 原理
贪心算法其实有一个更复杂的动态规划解法，在判断一个问题是否可以用贪心算法解决之前，可以先用动态规划的方法去分析。
动态规划的方法构造了一个最优子结构，将一个问题分成多个子问题，**而贪心算法选择了子问题里最好的一个子问题，直接忽略了其他子问题**。

**设计贪心算法步骤**
1. 将最优化问题转换为这样的形式：对其做出一次选择之后，只剩下一个子问题需要求解；
2. 证明做出贪心选择后，原问题总是存在最优解，即贪心选择总是安全的。
3. 证明做出贪心选择后，剩余的子问题满足性质：其最优解与贪心选择组合即可得到原问题的最优解，这样就得到了最优子结构。

**贪心选择性质**：可以通过做出局部最优（贪心）选择来构造全局最优解，即进行选择时，直接做出当前问题中看起来最优的选择，而不考虑子问题的解。

**最优子结构**：如果一个问题的最优解包括其子问题的解，则称此问题是具有最优子结构性质。此性质是能否应用动态规划和贪心方法的关键要素。

# 常见问题
## 活动选择问题
一个空教室，用来做活动，每个活动有起始时间s[i]和结束时间f[i]，想要两个活动之间时间不重叠，并尽量选择更多的活动。

将活动按照结束的时间由小到大排序，然后可以用迭代的方法，也可以用递归的方法。
```
RECURSIVE-ACTIVITY-SELECTOR(s, f, k, n)
    m = k + 1
    while m <= n and s[m] < f[k]    // find the first activity in Sk to finish
        m = m + 1
    if m <= n
        return {am} 并 RECURSIVE-ACTIVITY-SELECTOR(s, f, m, n)
    else
        return {} // 空集

GREEDY-ACTIVITY-SELECTOR(s, f)
    n = s.length
    A = {a1}
    k = 1
    for m = 2 to n
        if s[m] >= f[k]
            A = A 并 {am}
            k = m
    return A
```
## 设计数据压缩编码（Huffman 编码）
哈弗曼编码，将所有结点按从小到大的顺序排列，每次选出最小的两个结点（频率最低的两个结点）进行合并。

```
HUFFMAN(C)
    n = |C|
    Q = C
    for i = 1 to n-1
        allocate a new node z
        z.left = x = EXTRACT-MIN(Q)
        z.right = y = EXTRACT-MIN(Q)
        z.freq = x.freq + y.freq
        INSERT(Q, z)
    return EXTRACT-MIN(Q)   // return the root of the tree
```
## 拟阵的组合结构(Matroids)

## 最小生成树（minimum-spanning-tree）
## 单元最短路径(Dijkstra算法)
## 集合覆盖问题(Chvatal 贪心启发式算法)