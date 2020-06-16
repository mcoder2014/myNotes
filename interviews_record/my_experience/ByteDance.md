# 字节跳动
## 岗位职责
1. 负责跨平台高性能native客户端核心组件的研发；
2. 负责协助高质量的设计和编码；
3. 主要语言为Rust/C++。

## 岗位要求
1. 计算机相关专业，熟悉至少一门编程语言；
2. 掌握扎实的计算机基础知识，深入理解数据结构、算法、网络和操作系统知识；
3. 良好的设计和编码品味，能产出高质量的设计和代码；
4. 积极乐观，认真负责，乐于协作；

## 一面
1. 手写链表表示的两个整数加法： 1234 + 34
2. 计算机网络相关的问题
    1. HTTP 协议有哪些方法，方法的区别
    2. 幂级
    3. HTTPS 与 HTTP 的区别
    4. 传输前加密与传输时加密有什么不同
    5. 为什么 POST 方法比 GET 方法更安全？
3. 数据库
    1. 手写 SQL 语句
    2. 数据库的索引
    3. 给一个订单表，如何优化这个表的索引
        > #(订单ID,商品ID，订单时间(精确到天)，订单状态（枚举类型：已完成、未完成、撤销）)
        > 我说：因为最近购买的商品订单会被经常查找到，所以从时间上去优化索引。
4. C++ 的问题
   1. 虚拟内存
   2. 进程的内存包括哪些块
   3. 模版实现的多态和虚函数实现的多态有什么区别
   4. 你认为模版实现的多态效率高还是虚函数实现的多态效率高？为什么？
   5. 对函数递归的理解
5. 介绍你项目中有哪些亮点？
   
## 二面
1. 对于协程的理解？
2. 协程和多线程有什么区别？哪个效率高？
3. 协程和多线程可以同时实现吗？
4. 手写算法题，给二叉树根节点 root 和两个结点 node1, node2，找到他们最近的公共父节点。
5. C++ 函数调用时的具体流程
6. 局部变量如何存储在 C++ 栈中


# 字节跳动 上海 EA 2020年1月10日面试
# 算法题
## 算法题一
小明要在街上一排互相相邻的糖果屋拿糖，但不能在两个相邻的糖果屋同时拿糖。给定一个数组列表，每个元素代表每间房子中的糖的数目，小明一次最多能拿多少糖？

输入： [1,5,2,1,7] 

输出：12

```C++
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

int maxCandies(vector<int>& nums, int start)
{
    if(start >= nums.size())
        return 0;
    
    int max_value = 0;
    for(int i = start+2; i<nums.size(); i++)
    {
        // get candy
        int tmp = maxCandies(nums, i);
        max_value = tmp>max_value?tmp:max_value;
    }
    
    // not get candy
    int not_get_value = maxCandies(nums, start+1);
    
    if(nums[start] + max_value > not_get_value)
        return nums[start] + max_value;
    else
        return not_get_value;
}

int main() {
    int n;
    
    cin >> n;
    vector<int> nums(n, 0);
    for(int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    cout<<"size:" << nums.size() << endl;
    
    int result = maxCandies(nums, 0);
    cout << "Result :" << result << endl;
    

}
```
## 算法题二
给定二维小写、无序的字符数组chars，  搜索不定长度的全小写字符的单词word是否在chars中出现。

搜索规则： 从chars任意位置开始，可以向上、下、左、右移动，依次和word的每个字符匹配，如果能够匹配完成，则输出true，否则输出false。示例： 

        a   e   f
chars = d   x   j
        m   q   h

输入单词adx、fjh匹配结果输出true， 输入axh则为false