# 数据结构
动态集合通常包括如下的常见操作
- SEARCH(S, k): 查找一个集合中的k元素的位置
- INSERT(S, x): 将新的元素插入到集合中
- DELETE(S, x): 从集合中删除一个指定的元素x
- MINIMUM(S): 找到集合中的最小的元素
- MAXIMUM(S): 找到集合中的最大的元素
- SUCCESSOR(S, x): 找到集合中某个元素的后继元素
- PREDECESSOR(S, x): 找到集合中某个元素的前一个元素

# 栈
栈的特点是先进后出“Last in, First out”，栈数据结构的 insert 通常叫做 push ，delete 操作通常叫做 pop。

## 用数组实现栈数据结构
```
STACK-EMPTY(S)
    if S.top == 0
        return TRUE
    else return FALSE

PUSH(S, x)
    S.top = S.top + 1
    S[S.top] = x

POP(S)
    if STACK-EMPTY(S)
        error "underflow"
    else S.top = S.top-1
        return S[S.top + 1]
```
# 队列
队列的 insert 操作通常叫做 enqueue，delete 操作通常叫做 dequeue，队列的特点是先进先出，“First in, first out”。

## 用数组实现队列
- 一个大小为 n 的队列可以表示 n-1 个元素的队列，队列有 head 和 tail 属性，元素为`Q.head, Q.head+1, ... ,Q.tail-1`。
- 判断队列为空：Q.head == Q.tail, 初始化时，Q.head = Q.tail = 0；当我们对一个为空的队列执行 dequeue 操作成为下溢（underflows）。
- 判断队列已满，`Q.head == Q.tail + 1`；如果尝试向一个已经满了的队列加入元素，成为溢出（overflows）

```
// 忽略了对队列溢出检查的伪代码

ENQUEUE(Q, x)
    Q[Q.tail] = x
    if Q.tail == Q.length
        Q.tail = 1
    else
        Q.tail = Q.tail + 1


DEQUEUE(Q)
    x = Q[Q.head]
    if Q.head == Q.length
        Q.head = 1
    else
        Q.head = Q.head + 1
    return x

```

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

![带有NIL节点的双向链表](imgs/circular_double_linked_list.png)
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

# 有根数的表达
为了表示节点的孩子节点数目不限制且非常不均衡的有根数，可以用类似于链表的表示方法
- 用`x.left-child`表示x节点的最左边的孩子节点；
- 用`x.right-sibling`指针信息表示x的右边的兄弟节点；
最终，每个节点有如下信息：`parent, left-child, right-sibling`;

