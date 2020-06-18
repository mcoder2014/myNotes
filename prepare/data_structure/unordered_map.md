# 结合 LeetCode 谈谈哈希表在算法问题上的应用
> 从 `LeetCode` 前一百道题中总结了些哈希表(`unordered_map`)应用于算法问题的场景，在恰当的时候使用哈希表可以大幅提升算法效率，比如：统计字符串中每个字符或单词出现的次数、从一维数组中选择出两个数使之与某数相等。

在开始之前，首先简要的介绍一下哈希表（又称散列表），心急的同学可以跳转到[LeetCode部分](#leetcode)。

# 哈希表介绍
哈希表查找的时间复杂度最差是O(n),平均时间复杂度**O(1)**，因此，理想状态哈希表的使用和数组很像。

散列表使用某种算法操作(散列函数)将键转化为数组的索引来访问数组中的数据，这样可以通过`Key-value`的方式来访问数据，达到常数级别的存取效率。现在的`nosql`数据库都是采用`key-value`的方式来访问存储数据。

散列表是算法在时间和空间上做出权衡的经典例子。通过一个散列函数，将键值key映射到记录的访问地址，达到快速查找的目的。如果没有内存限制，我们可以直接将键作为数组的索引，所有的操作操作只需要一次访问内存就可以完成。

## 散列函数

散列函数就是将键转化为数组索引的过程,这个函数应该易于计算且能够均与分布所有的键。

散列函数最常用的方法是`除留余数法`，通常被除数选用`素数`，这样才能保证键值的均匀散布。

散列函数和键的类型有关，每种数据类型都需要相应的散列函数；比如键的类型是整数，那我们可以直接使用`除留余数法`；键的类型是字符串的时候我们任然可以使用`除留余数法`，可以将字符串当做一个特别大的整数。

```c++
int hash = 0;
for (int i=0;i<s.length();i++){
	hash = (R*hash +s.charAt(i)%M);
}
```

或者

``` c++
Hash hashCode(char *key){
	int offset = 5;
	Hash hashCode = 0;
	while(*key){
		hashCode = (hashCode << offset) + *key++;
	}
	return hashCode;		
}
```

使用时 `hashCode(key) & (size-1) ` 就可以得到一个 `size-1` 范围内的hash值


## 碰撞解决
不同的关键字得到同一个散列地址` f(key1)=f(key2) `，即为碰撞 。这是我们需要尽量避免的情况。常见的处理方法有：

1. 拉链法
2. 开放地址法

### 拉链法

将大小为M的数组中的每个元素指向一条链表，链表中的每个节点都存储了散列值为该元素索引的键值对。每条链表的平均长度是N/M，N是键值对的总个数。如下图：

![](imgs/hashmap.png)

添加操作： 

1. 通过hash函数得到hashCode  
2. 通过hashcode得到index  
3. 如果index处没有链表，建立好新结点，作为新链表的首结点  
4. 如果index处已经有链表，先要遍历看key是否已经存在，如果存在直接返回，如果不存在，加入链表头部  

删除操作： 

1. 通过hash函数得到hashCode  
2. 通过hashcode得到index  
3. 遍历链表，删除结点  

### 开放地址法

使用大小为M的数组保存N个键值对，当碰撞发生时，直接检查散列表中的下一个位置。
检查的方法可以是`线性检测、平方检测、双哈希`等方法，主要区别在于检测的下一个位置。
《算法导论》中更推荐双哈希方法。

```c++
// 插入算法
HASH-INSERT(T, k)
    i = 0
    repeat
        j = h(k, i)
        if T[j] == NIL
            T[j] = k
            return j
        else
            i++
    until i == m
    error "hash table overflow"

// 搜索算法
HASH-SEARCH(T, k)
    i = 0
    repeat
        j = j(k, i)
        if T[j] == k
            return j
        i++
    until T[j] == NIL or i == m
    return NIL
```
# LeetCode 中哈希表的题目 <span id="leetcode"></span>
在练习 LeetCode 的过程中，我数次碰到了可以使用 表来简化问题的场景。

## [由元素值去寻找索引的问题](https://leetcode.com/problems/two-sum/)
给一个数组`nums = [2, 7, 11, 15]`，要求求得两个数使他们的和为 `target = 9`。

这个简单的问题，如果使用循环暴力求解的话，也可以很快获得解，但是时间复杂度是`O(n^2)`，如果这个数组很长的话，有百万千万数量级，就需要超级多的时间才可以循环完。

一个快速的解法是，使用表先记下每个数值的索引，接着循环一次，判断`target-nums[i]`，在不在表中，就可以快速找到一组解。**此处，key是数值，value是数值对应的索引，是利用数值快速寻找索引的方法。**

```C++
vector<int> twoSum(vector<int>& nums, int target) 
{
        unordered_map<int, int> maps;
        int size = nums.size();
        for(int i = 0; i < size; ++i)
            maps[nums[i]] = i;

        for (int i = 0; i < size; ++i) {
            int left = target - nums[i];
            if(maps.count(left) > 0 && maps[left] != i)
            {
                return vector<int>({i, maps[left]});
            }
        }
        return vector<int>();
    }
```
## 记下某个元素出现次数的问题
[数独合法性判断问题](https://leetcode.com/problems/sudoku-solver/)和[包含所有字符的最短子串问题](https://leetcode.com/problems/minimum-window-substring/)都是利用哈希表来计算某个元素出现次数的问题。

在这种所有元素的种类有限的问题中，我们还可以使用数组`vector<int>`来代替哈希表`unordered_map<int,int>、unordered_map<char,int>、`进行统计，因为1-9总共有9种可能，ASCII码元素总共有128种可能性，这实际上便是散列函数为`f(int x){return x;}`的特殊情况。

### 数独问题
数独问题要求每行、每列、以及整个表格分为9个子块，每个子块内，1-9只能出现一次，不能重复。我们可以为每行每列创建哈希表，总共 27个表，将元素加入表中，一旦出现有表中的某个元素大于1，便可判断数独不合格。

```c++
bool isValidSudoku(vector<vector<char>>& board)
    {
        vector<unordered_map<char, int>> rows(9);
        vector<unordered_map<char, int>> cols(9);
        vector<unordered_map<char, int>> subs(9);
        for (int i=0; i<9; i++)
        {
            for (int j=0; j<9; j++)
            {
                // row
                char ch = board[i][j];
                if(ch != '.')
                {
                    rows[i][ch]++;
                    if(rows[i][ch] > 1)
                        return false;

                    cols[j][ch]++;
                    if(cols[j][ch] > 1)
                        return false;

                    int idx = i/3 + j-(j%3);
                    subs[idx][ch]++;
                    if(subs[idx][ch] > 1)
                        return false;
                }
            }
        }
        return true;
    }
```
同样，在求解数独问题时，我们可以利用动态规划方法，在插入每个元素前，利用哈希表检查插入的元素是否合法，如果不合法，则恢复"作案现场"，返回到上一层。

## 将本不是相同 key 的数据转换为相同 key
有的问题，从列表中找到所有是相同元素，不同排列组成的问题，比如[Group Anagrams](https://leetcode.com/problems/group-anagrams/)问题。

```
Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
Output:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]
```
我们可以利用哈希表的原理，自己结合排列组合的特性，将所有元素按字典序转换出来，便可以使这些元素的结果相同，指向同一个索引。即自己写了个散列函数`f(string){return sort(string);}`。问题的解法如下：

```c++
vector<vector<string>> groupAnagrams(vector<string>& strs)
    {
        vector<vector<string>> result;
        unordered_map<string, vector<string>> map;
        for(int i = 0; i < strs.size(); i++)
        {
            string s = strs[i];
            sort(s.begin(), s.end());
            map[s].push_back(strs[i]);
        }
        for(pair<string, vector<string>> pa:map)
        {
            result.push_back(pa.second);
        }
        return result;
    }
```

## 总结
结合上面这些 `LeetCode` 上与哈希表想关的问题，我们可以总结一些哈希表在算法问题中改善算法效率的思路。
1. 在那些需要一次一次遍历，去寻找元素的问题中，可以将问题转化为根据元素的内容去寻找索引，哈希表在这方面的时间效率是贼高的；
2. 在一些字符串词频统计问题、数独问题等问题中，可以利用哈希函数来计算某个元素出现的次数，作为算法的辅助工具；
3. 还有些问题，可以利用散列函数的思路，让几个不同的元素获得同样的结果，从而实现一个聚类。

# 多阶哈希表
解决哈希表冲突的一种方法，多阶哈希表。多阶哈希表其实就是一个锯齿般的数组。

1. 每一行是一阶，上面的元素个数多，下面的元素个数依次减少. 每一行的元素个数都是素数. 每一阶数组的每一个节点用于存储数据的内容，其中，节点的前四个字节用来存储int类型的Key或者是hash_code.
 2. **创建多阶HASH的时候，用户通过参数来指定有多少阶，每一阶做最多有多少个元素** 那么每一阶应该选择多少个元素呢？ 这里采用了素数集中原理的算法来查找. 假如每阶最多有1000个元素，一共10阶，则算法选择十个比1000小的最大素数，从大到小排列，以此作为各阶的元素个数. 通过素数集中的算法得到的10个素数分别是： 997 991 983 977 971 967 953 947 941 937. 可见虽然是锯齿数组，各层之间的差别并不是很多.
3. 查找的过程，先将key在第一阶内取模，看是否是这个元素，如果这个位置为空，直接返回不存在; 如果是这个key，则返回这个位置. **如果这个位置有元素，但是又不是key，则说明hash冲突了，再去第二阶去寻找. 循环往复.**

**和开链法比较**
1. 冲突处理也很简单，开链法非常极端的情况下时间复杂度是 O(N)；
2. 在增容问题上，哈希桶却不占优势，因为它需要一个数据搬迁的过程
3. 多阶哈希初始化时很占空间；哈希桶是来一个插入一个，对空间的利用率很高，并不会浪费很多空间。而多阶哈希在创建时就需要开辟一大段空间，这对空间无形中是一种浪费。
4. 缺点，每次要做K次哈希处理， 如果K阶都被占用了，则可能不能插入；

# references
1. [Algotithm 3rd]()
2. [LeetCode hash table](https://leetcode.com/tag/hash-table/)
3. [多阶哈希表](https://blog.csdn.net/Dawn_sf/article/details/79506520)