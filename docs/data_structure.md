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

# 二叉搜索树
二叉搜索树可以用作字典和有限队列，二叉搜索树的基本动态集合操作的时间复杂度是O(logn)

## 基本问题
1. 如何遍历二叉搜索树输出有序序列；
 > 中序遍历可以输出从小到大排序的有序数列

2. 如何从二叉搜索树中搜索到某个数值的节点；
3. 找到最大值和最小值；
 > 树的最左孩子节点是最小值；树的最右孩子节点是最大值；
4. 找到某个节点的前一个节点(小一)和后一个节点（大一）；
 > 右支的最左孩子节点是后一个节点；左支的最右孩子节点是前一个节点；
5. 如何插入、删除元素；

**二叉搜索树的表示**
二叉搜索树可以使用链接的数据结构表示，每个节点对象包括`key`属性用来存储数据，并包含`left, right, p`属性分别指向该节点的左孩子、右孩子和父亲节点的对象。

**二叉搜索树的属性**
假设 x 是二叉搜索树上的一个节点，如果 y 是 x 左支的节点，则 y.key <= x.key ，如果 y 是 x 右支的节点，则 y.key >= x.key。

```
// 中序遍历，获得顺序序列（递归）
INORDER-TREE-WALK(x)
    if x != NIL
        INORDER-TREE-WALK( x.left )
        print x.key
        INORDER-TREE-WALK( x.right )

// 搜索某一个节点(递归)
TREE-SEARCH(x, k)
    if x == NIL or k == x.key
        return x
    if k < x.key
        return TREE-SEARCH( x.left, k )
    else
        return TREE-SEARCH( x.right, k )

// 搜索某一个节点（迭代）
ITERATIVE-TREE-SEARCH(x, k)
    while x != NIL and k != x.key
        if k < x.key
            x = x.left
        else
            x = x.right
    return x

// 查找最小值 （最左孩子节点）
TREE-MINIMUM(x)
    while(x.left != NIL)
        x = x.left
    return x

// 查找最大值 （最右孩子节点）
TREE-MAXIMUM(x)
    while x.right != NIL
        x = x.right
    return x

// 查找后续节点
TREE-SUCCESSOR(x)
    if x.right != NIL
        return TREE-MINIMUM(x.right)
    y = x.p
    while y != NIL and x == y.right
        x = y
        y = y.p
    return y

// 查找前序节点
TREE-PREDECESSOR(x)
    if x.left != NILL
        return TREE-MAXIMUM(x.left)
    y = x.p
    while y != NIL and x == y.left
        x = y
        y = y.p
    return y

// 插入节点
TREE-INSERT(T, z)
    y = NIL
    x = T.root
    while x != NIL
        y = x
        if z.key < x.key
            x = x.left
        else x = x.right
    z.p = y
    if y == NIL
        T.root = z // tree T was empty
    else if z.key < y.key
        y.left = z
    else y.right = z

// 迁移
TRANSPLANT(T, u, v)
    if u.p == NIL
        T.root = v
    elseif u == u.p.left
        u.p.left = v
    else 
        u.p.right = v
    if v != NIL
        v.p = u.p

// 删除节点
TREE-DELETE(T, z)
    if z.left == NIL
        TRANSPLANT(T, z, z.right)
    elseif z.right == NIL
        TRANSPLANT(T, z, z.left)
    else 
        y = TREE-MINIMUM(z.right)
        if y.p != z
            TRANSPLANT(T, y, y.right)
            y.right = z.right
            y.right.p = y
        TRANSPLANT(T, z, y)
        y.left = z.left
        y.left.p = y
```

# 红黑树
红黑树是平衡的查找树的一种，最坏的基本操作的时间复杂度是 O(lgn)。

红黑树是一棵二叉搜索树，每个结点增加了一个颜色属性，可以标识为红色或黑色，通过对任意一条从根结点到叶子结点的路径上的颜色做约束，保证没有任意一条路径比其他的路径长出2倍，因此近乎是平衡的。

红黑树的每个结点包含5个属性：`color, key, left, right, parent`。

**红黑树属性**
1. 每个结点必须是红色或者黑色中的一种颜色；
2. 根结点的颜色是黑色的；
3. 每个叶子结点是黑色的（NIL结点）；
4. 如果一个结点是红色的，则它的两个子节点都是黑色的；
5. 对每个结点，从该结点到其所有的后代叶结点的简单路径上，均包含相同数目的黑色结点；

**黑高**：从某个结点x出发到叶子结点的任意一条简单路径的所经过的黑色结点的个数；
**高度**：一棵有n个内部结点的红黑树的高度至多是`2lg(n+1)`

## 算法
```
// 旋转，左旋与右旋对称
LEFT-ROTATE(T, x)
    y = x.right         // set y
    x.right = y.left    // turn y's left subtree into x's right subtree
    if y.left != T.nil
        y.left.p = x
    y.p = x.p           // link x's parent to y
    if x.p == T.nil
        T.root = y
    elseif x == x.p.left
        x.p.left = y
    else
        x.p.right = y
    y.left = x          // put x on y's left
    x.p = y
```
![](imgs/red_black_tree_rotate.png)

### 插入
```
RB-INSERT(T, z)
    y = T.nil
    x = T.root
    while x != T.nil
        y = x
        if z.key < x.key
            x = x.left
        else
            x = x.right
    z.p = y
    if y == T.nil
        T.root = z
    elseif z.key < y.key
        y.left = z
    else 
        y.right = z
    z.left = T.nil
    z.right = T.nil
    z.color = RED
    RB-INSERT-FIXUP(T,z)
// 红黑树的插入与二叉搜索书的插入有四处不同
// 1. 将 nil 更改为哨兵方式，使用 T.nil替代
// 2. 置 z.left 和 z.right 为 T.nil ，保持合理的树结构
// 3. 将 z 初始化为红色
// 4. 因为将 z 置为红色时可能违反属性2 和属性4，所以使用 Fixup 函数保持红黑树的性质。

RB-INSERT-FIXUP(T, z)
    while z.p.color == RED
        if z.p == z.p.p.left
            y = z.p.p.right
            if y.color == RED
                z.p.color = BLACK       // case 1
                y.color = BLACK         // case 1
                z.p.p.color = RED       // case 1
                z = z.p.p               // case 1
            else
                if z == z.p.right       // case 2
                    z = z.p             // case 2
                    LEFT-ROTATE(T, z)   // case 2
                z.p.color = BLACK       // case 3
                z.p.p.color = RED       // case 3
                RIGHT-ROTATE(T, z.p.p)  // case 3
        else
            // 与上方对称，将 left 与 right 颠倒一下
    T.root.color = BLACK

// Case 1: y 的父节点的兄弟结点是红色 （z是红色，z的父亲结点和父亲的兄弟节点都是红色）
// Case 2: z 的父亲的兄弟结点是黑色，且 z 是一个右孩子 (z是红色，z的父亲结点是红色，但父亲结点的兄弟节点是黑色) 
//           - 需要转换为 Case 3 然后在进行处理
// Case 3: z 的父亲的兄弟结点是黑色的，且z是一个左孩子
```

Case 1:
![](imgs/red_black_tree_insert_case_1.png)

Case 2 and Case 3:
![](imgs/red_black_tree_insert_case_2_3.png)

### 删除
删除一个结点需要时间复杂度O(lgn)，删除结点的操作相对复杂些。

```
RB-TRANSPLANT(T, u, v)
    if u.p == T.nil
        T.root = v
    elseif u == u.p.left
        u.p.left = v
    else 
        u.p.right = v
    v.p = u.p

// 与二叉搜索树的删除相比，多了几行代码记录y的踪迹，因为y有可能导致红黑树的性质被破坏
// 当想要删除结点z，如果z的子节点少于2个时，z从树中删除，并让y成为z。
// 当z有两个子节点时，y应该是z的后序，并且y将移动到z的位置，
// 在结点被移动之前，需要记住y的颜色，并记录结点 x 的总计，将x移动至树中y的原来位置，
// 因为结点x也可能引起红黑树的属性的破坏，删除结点 z 之后，红黑树调用了FIXUP来恢复红黑性质
// 如果y是黑色的，则删除和移动y可能会导致红黑树的属性发生破坏，
// 当y是红色时，(删除后黑高不变，并不破坏红黑树性质;不存在相邻的红色结点)

RB-DELETE(T, z)
    y = z
    y-original-color = y.color
    if z.left == T.nil
        x = z.right
        RB-TRANSPLANT(T, z, z.right)
    elseif z.right == T.nil
        x = z.left
        RB-TRANSPLANT(z, z, z.left)
    else
        y = TREE-MINIMUM(T, y, y.right)
        y-original-color = y.color
        x = y.right
        if y.p == z
            x.p = y
        else
            RB-TRANSPLANT(T, y, y.right)
            y.right = z.right
            y.right.p = y
        RB-TRANSPLANT(T, z, y)
        y.left = z.left
        y.left.p = y
        y.color = z.color
    if y-original-color == BLACK
        RB-DELETE-FIXUP(T, x)

RB-DELETE-FIXUP(T, x)
    while x != T.root and x.color == BLACK
        if x == x.p.right
            w = x.p.left
            if w.color == RED
                w.color = BLACK          // case 1
                x.p.color = RED          // case 1
                LEFT-ROTATE(T, x.p)      // case 1
                w = x.p.right            // case 1
            if w.left.color == BLACK and w.right.color == BLACK
                w.color = RED            // case 2
                x = x.p                  // case 2
            else 
                if w.right.color == BLACK
                    w.left.color = BLACK // case 3
                    w.color = RED        // case 3
                    RIGHT-ROTATE(T, w)   // case 3
                    w = x.p.right        // case 3
                w.color = x.p.color      // case 4
                x.p.color = BLACK        // case 4
                w.right.color = BLACK    // case 4
                LEFT-ROTATE(T, x.p)      // case 4
                x = T.root               // case 4
        else
            // 对称， 交换 left 和right
    x.color = BLACK
 
```
如果 y 是黑色，会产生三个问题：
1. y是原来的根节点，y的一个红色孩子成为了根节点，违反了性质2；
2. x和x.p是红色的，违反了性质4；
3. 在树中移动了y结点，导致一条路径上的黑色结点少一，违反了性质5；（将任意包含x的简单路径上黑色结点数量增加1）

![](imgs/red_black_tree_delete_case_1_2_3_4.png)

- Case 1: x 的兄弟结点 w 是红色的；（转换成Case 2 || 3 || 4 处理）
- Case 2: x 的兄弟结点 w 是黑色的，而且 w 的两个子结点都是黑色的；
- Case 3: x 的兄弟结点 w 是黑色的，w的左孩子是红色的，w的右孩子是黑色的；（将 Case 3 转换成 Case 4）
- Case 4: x 的兄弟结点 w 是黑色的，且 w 的右孩子是红色的；

# B-tree

# 字典树跳跃表
    skiplist