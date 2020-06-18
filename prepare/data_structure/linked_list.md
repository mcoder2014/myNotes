# 链表
- 列表分为很多种类：双向链表、单向链表；有序链表、无序链表、循环链表等。
- 双向链表中的每个节点都有如下属性 `key, next, prev`；

## 用指针实现链表
```
// 链表的搜索
LIST-SEARCH(L, x)
    x = L.head
    while x != NIL and x.key != k
        x = x.next
    return x

// 在链表的头部插入元素
LIST-INSERT(L, x)
    x.next = L.head
    if L.head != NIL
        L.head.prev = x
    L.head = x
    x.prev = NIL

// 从链表中删除元素
LIST-DELETE(L, x)
    if x.prev != NIL
        x.prev.next = x.next
    else 
        L.head == x.next
    if x.next != NIL
        x.next.prev = x.prev
```

## 通过插入 NIL 节点可以不用区分链表的首位节点

![带有NIL节点的双向链表](../imgs/circular_double_linked_list.png)
始终保持一个空节点（也叫哨兵节点）用来表示空节点，连接头节点和尾节点，可以简化链表的算法

```
LIST-DELETE'(L, x)
    x.prev.next = x.next
    x.next.prev = x.prev

LIST-SEARCH'(L, k)
    x = L.nil.next
    while x != L.nil and x.key != k
        x = x.next
    return x

LIST-INSERT'(L, x)
    x.next = L.nil.next
    L.nil.next.prev = x
    L.nil.next = x
    x.prev = L.nil
```

## 使用数组实现链表
1. 用三个数组`next, key, prev`，可以表示出链表；
2. 用一个数组，通过设置 offset 来实现，相邻的三个元素分别表示 `next， key， prev`信息；
3. 分配和管理空闲空间，通过增加一个单向链表来进行分配和管理链表元素。

# 常见问题
## 链表逆置
头插法、尾插法、就地逆置

## 判断链表有环，找到环开始的点
1. 双指针法，一个慢指针一次移动一个距离，一个快指针一次移动两个距离；
2. 我们在第一次相遇时，把慢指针留在原地，把快指针放回起点head处，然后把快指针变为慢指针，**两个指针一起以速度1前进，当它们相遇时** ，相遇点就是入环点4；
