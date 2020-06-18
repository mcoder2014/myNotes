# 二叉树相关的问题

# 有根数的表达
为了表示节点的孩子节点数目不限制且非常不均衡的有根数，可以用类似于链表的表示方法
- 用`x.left-child`表示x节点的最左边的孩子节点；
- 用`x.right-sibling`指针信息表示x的右边的兄弟节点；
最终，每个节点有如下信息：`parent, left-child, right-sibling`;

# 查找树
二叉查找树、红黑树、平衡二叉树都属于二叉查找树。
## 平衡二叉树
## 红黑树
## 二叉搜索树
二叉搜索树可以用作字典和有限队列，二叉搜索树的基本动态集合操作的时间复杂度是O(logn)

### 基本问题
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

# 二叉树常见问题

## 判断二叉树是否对称

## 二叉树遍历
### 前序
### 中序
### 后序
### 层次