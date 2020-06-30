# 二叉树相关的问题

## 有根数的表达

为了表示节点的孩子节点数目不限制且非常不均衡的有根数，可以用类似于链表的表示方法

- 用`x.left-child`表示x节点的最左边的孩子节点；
- 用`x.right-sibling`指针信息表示x的右边的兄弟节点；
最终，每个节点有如下信息：`parent, left-child, right-sibling`;

## 查找树

二叉查找树、红黑树、平衡二叉树都属于二叉查找树。

### 平衡二叉树

### 红黑树

### 二叉搜索树

二叉搜索树可以用作字典和有限队列，二叉搜索树的基本动态集合操作的时间复杂度是O(logn)

#### 基本问题

1. 如何遍历二叉搜索树输出有序序列；
    > 中序遍历可以输出从小到大排序的有序数列
2. 如何从二叉搜索树中搜索到某个数值的节点；
3. 找到最大值和最小值；
    > 树的最左孩子节点是最小值；树的最右孩子节点是最大值；
4. 找到某个节点的前一个节点(小一)和后一个节点（大一）；
    > 右支的最左孩子节点是后一个节点；左支的最右孩子节点是前一个节点；
5. 如何插入、删除元素；

#### 二叉搜索树的表示

二叉搜索树可以使用链接的数据结构表示，每个节点对象包括`key`属性用来存储数据，并包含`left, right, p`属性分别指向该节点的左孩子、右孩子和父亲节点的对象。

#### 二叉搜索树的属性

假设 x 是二叉搜索树上的一个节点，如果 y 是 x 左支的节点，则 y.key <= x.key ，如果 y 是 x 右支的节点，则 y.key >= x.key。

```fakecode
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

## 二叉树常见问题

### 求二叉树深度

```cpp
int GetDepth(BinaryTreeNode * pRoot)
{
    if(pRoot == NULL) // 递归出口
        return 0;
    int depthLeft = GetDepth(pRoot->m_pLeft);
    int depthRight = GetDepth(pRoot->m_pRight);
    return depthLeft > depthRight ? (depthLeft + 1) : (depthRight + 1);
}
```

### 求二叉树第 k 层的节点的数量

递归解法：

1. 如果二叉树为空或者k<1返回0
2. 如果二叉树不为空并且k==1，返回1
3. 如果二叉树不为空且k>1，返回左子树中k-1层的节点个数与右子树k-1层节点个数之和

```cpp
int GetNodeNumKthLevel(BinaryTreeNode * pRoot, int k)
{
    if(pRoot == NULL || k < 1)
        return 0;
    if(k == 1)
        return 1;
    int numLeft = GetNodeNumKthLevel(pRoot->m_pLeft, k-1); // 左子树中k-1层的节点个数
    int numRight = GetNodeNumKthLevel(pRoot->m_pRight, k-1); // 右子树中k-1层的节点个数
    return (numLeft + numRight);
}
```

### 求二叉树叶子节点的数量

递归解法：

1. 如果二叉树为空，返回0
2. 如果二叉树不为空且左右子树为空，返回1
3. 如果二叉树不为空，且左右子树不同时为空，返回左子树中叶子节点个数加上右子树中叶子节点个数

```cpp
int GetLeafNodeNum(BinaryTreeNode * pRoot)
{
    if(pRoot == NULL)
        return 0;
    if(pRoot->m_pLeft == NUSLL && pRoot->m_pRight == NULL)
        return 1;
    int numLeft = GetLeafNodeNum(pRoot->m_pLeft); // 左子树中叶节点的个数
    int numRight = GetLeafNodeNum(pRoot->m_pRight); // 右子树中叶节点的个数
    return (numLeft + numRight);
}
```

### 判断两棵二叉树结构一致

```cpp
bool StructureCmp(BinaryTreeNode * pRoot1, BinaryTreeNode * pRoot2)
{
    if(pRoot1 == NULL && pRoot2 == NULL) // 都为空，返回真
        return true;
    else if(pRoot1 == NULL || pRoot2 == NULL) // 有一个为空，一个不为空，返回假
        return false;
    bool resultLeft = StructureCmp(pRoot1->m_pLeft, pRoot2->m_pLeft); // 比较对应左子树
    bool resultRight = StructureCmp(pRoot1->m_pRight, pRoot2->m_pRight); // 比较对应右子树
    return (resultLeft && resultRight);
}
```

### 求二叉树两节点的最大距离

```cpp
int GetMaxDistance(BinaryTreeNode * pRoot, int & maxLeft, int & maxRight)
{
    // maxLeft, 左子树中的节点距离根节点的最远距离
    // maxRight, 右子树中的节点距离根节点的最远距离
    if(pRoot == NULL)
    {
        maxLeft = 0;
        maxRight = 0;
        return 0;
    }
    int maxLL, maxLR, maxRL, maxRR;
    int maxDistLeft, maxDistRight;
    if(pRoot->m_pLeft != NULL)
    {
        maxDistLeft = GetMaxDistance(pRoot->m_pLeft, maxLL, maxLR);
        maxLeft = max(maxLL, maxLR) + 1;
    }
    else
    {
        maxDistLeft = 0;
        maxLeft = 0;
    }
    if(pRoot->m_pRight != NULL)
    {
        maxDistRight = GetMaxDistance(pRoot->m_pRight, maxRL, maxRR);
        maxRight = max(maxRL, maxRR) + 1;
    }
    else
    {
        maxDistRight = 0;
        maxRight = 0;
    }
    return max(max(maxDistLeft, maxDistRight), maxLeft+maxRight);
}
```

### 二叉树变成双向链表

要求不能创建新节点，只调整指针。
递归解法：
（1）如果二叉树查找树为空，不需要转换，对应双向链表的第一个节点是NULL，最后一个节点是NULL
（2）如果二叉查找树不为空：

如果左子树为空，对应双向有序链表的第一个节点是根节点，左边不需要其他操作；
如果左子树不为空，转换左子树，二叉查找树对应双向有序链表的第一个节点就是左子树转换后双向有序链表的第一个节点，同时将根节点和左子树转换后的双向有序链 表的最后一个节点连接；
如果右子树为空，对应双向有序链表的最后一个节点是根节点，右边不需要其他操作；
如果右子树不为空，对应双向有序链表的最后一个节点就是右子树转换后双向有序链表的最后一个节点，同时将根节点和右子树转换后的双向有序链表的第一个节点连接。

```cpp
/******************************************************************************
参数：
pRoot: 二叉查找树根节点指针
pFirstNode: 转换后双向有序链表的第一个节点指针
pLastNode: 转换后双向有序链表的最后一个节点指针
******************************************************************************/
void Convert(BinaryTreeNode * pRoot,
             BinaryTreeNode * & pFirstNode, BinaryTreeNode * & pLastNode)
{
    BinaryTreeNode *pFirstLeft, *pLastLeft, * pFirstRight, *pLastRight;
    if(pRoot == NULL)
    {
        pFirstNode = NULL;
        pLastNode = NULL;
        return;
    }

    if(pRoot->m_pLeft == NULL)
    {
        // 如果左子树为空，对应双向有序链表的第一个节点是根节点
        pFirstNode = pRoot;
    }
    else
    {
        Convert(pRoot->m_pLeft, pFirstLeft, pLastLeft);
        // 二叉查找树对应双向有序链表的第一个节点就是左子树转换后双向有序链表的第一个节点
        pFirstNode = pFirstLeft;
        // 将根节点和左子树转换后的双向有序链表的最后一个节点连接
        pRoot->m_pLeft = pLastLeft;
        pLastLeft->m_pRight = pRoot;
    }

    if(pRoot->m_pRight == NULL)
    {
        // 对应双向有序链表的最后一个节点是根节点
        pLastNode = pRoot;
    }
    else
    {
        Convert(pRoot->m_pRight, pFirstRight, pLastRight);
        // 对应双向有序链表的最后一个节点就是右子树转换后双向有序链表的最后一个节点
        pLastNode = pLastRight;
        // 将根节点和右子树转换后的双向有序链表的第一个节点连接
        pRoot->m_pRight = pFirstRight;
        pFirstRight->m_pLeft = pRoot;
    }

    return;
}
```

### 判断二叉树是不是平衡二叉树

```cpp
bool IsAVL(BinaryTreeNode * pRoot, int & height)
{
    if(pRoot == NULL) // 空树，返回真
    {
        height = 0;
        return true;
    }
    int heightLeft;
    bool resultLeft = IsAVL(pRoot->m_pLeft, heightLeft);
    int heightRight;
    bool resultRight = IsAVL(pRoot->m_pRight, heightRight);
    if(resultLeft && resultRight && abs(heightLeft - heightRight) <= 1) // 左子树和右子树都是AVL，并且高度相差不大于1，返回真
    {
        height = max(heightLeft, heightRight) + 1;
        return true;
    }
    else
    {
        height = max(heightLeft, heightRight) + 1;
        return false;
    }
}
```

### 判断是否为完全二叉树

```cpp
bool IsCompleteBinaryTree(BinaryTreeNode * pRoot)
{
    if(pRoot == NULL)
        return false;
    queue<BinaryTreeNode *> q;
    q.push(pRoot);
    bool mustHaveNoChild = false;
    bool result = true;
    while(!q.empty())
    {
        BinaryTreeNode * pNode = q.front();
        q.pop();
        if(mustHaveNoChild) // 已经出现了有空子树的节点了，后面出现的必须为叶节点（左右子树都为空）
        {
            if(pNode->m_pLeft != NULL || pNode->m_pRight != NULL)
            {
                result = false;
                break;
            }
        }
        else
        {
            if(pNode->m_pLeft != NULL && pNode->m_pRight != NULL)
            {
                q.push(pNode->m_pLeft);
                q.push(pNode->m_pRight);
            }
            else if(pNode->m_pLeft != NULL && pNode->m_pRight == NULL)
            {
                mustHaveNoChild = true;
                q.push(pNode->m_pLeft);
            }
            else if(pNode->m_pLeft == NULL && pNode->m_pRight != NULL)
            {
                result = false;
                break;
            }
            else
            {
                mustHaveNoChild = true;
            }
        }
    }
    return result;
}
```

### 二叉树的序列化和反序列化

设计一个算法，并编写代码来序列化和反序列化二叉树。将树写入一个文件被称为“序列化”，读取文件后重建同样的二叉树被称为“反序列化”。

如何反序列化或序列化二叉树是没有限制的，你只需要确保可以将二叉树序列化为一个字符串，并且可以将字符串反序列化为原来的树结构。

输入样例：

```plain
给出一个测试数据样例， 二叉树{3,9,20,#,#,15,7}，表示如下的树结构：
  3
 / \
9  20
   / \
 15   5
```

```java
  //序列化
  public String serialize(TreeNode root) {
        if (root == null) {
            return "#,";
        }
        String mid = root.val + ",";
        String left = serialize(root.left);
        String right = serialize(root.right);
        mid += left + right;
        return mid;
    }

    private String data = "";
    //反序列化
    public TreeNode deserialize(String data) {
        this.data = data;
        return desHelper();
    }

    public TreeNode desHelper() {
        if (this.data.indexOf("#,") == 0) {
            this.data = this.data.substring(this.data.indexOf(",") + 1);
            return null;
        }
        String midVal = this.data.substring(0, this.data.indexOf(","));
        TreeNode mid = new TreeNode(Integer.parseInt(midVal));
        this.data = this.data.substring(this.data.indexOf(",") + 1);
        TreeNode left = desHelper();
        TreeNode right = desHelper();
        mid.left = left;
        mid.right = right;
        return mid;
    }

```

### 二叉树的最近公共祖先

```java
    // 在root为根的二叉树中找A,B的LCA:
    // 如果找到了就返回这个LCA
    // 如果只碰到A，就返回A
    // 如果只碰到B，就返回B
    // 如果都没有，就返回null
    public TreeNode lowestCommonAncestor(TreeNode root, TreeNode node1, TreeNode node2) {
        if (root == null || root == node1 || root == node2) {
            return root;
        }

        // Divide
        TreeNode left = lowestCommonAncestor(root.left, node1, node2);
        TreeNode right = lowestCommonAncestor(root.right, node1, node2);

        // Conquer
        if (left != null && right != null) {
            return root;
        }
        if (left != null) {
            return left;
        }
        if (right != null) {
            return right;
        }
        return null;
    }
```

### 二叉树镜像

```java
    public static void mirrorNonRecurively(TreeNode root){
        if(root == null)
            return;

        java.util.Stack<TreeNode> stack = new java.util.Stack<TreeNode>();

        stack.push(root);

        while(stack.size() > 0){
            TreeNode node = stack.pop();
            if(null != node.left || null != node.right){
              TreeNode temp = node.left;
              node.left = node.right;
              node.right = temp;
            }

            if(null != node.left){
                stack.push(node.left);
            }

            if(null != node.right){
                stack.push(node.right);
            }
        }
    }
```

### 判断二叉树是否对称

### 二叉树遍历

#### 前序

```java
import java.util.ArrayList;
import java.util.Iterator;

public class PreOrderTraversal{
    //二叉树的前序遍历
    public static ArrayList<Integer> preOrderTraversal(TreeNode root){
        ArrayList<Integer> result = new ArrayList<Integer>(15);

        if(root == null)
            return result;

        result.add(root.val);//根
        ArrayList<Integer> left = preOrderTraversal(root.left);//左
        ArrayList<Integer> right = preOrderTraversal(root.right);//右

        result.addAll(left);
        result.addAll(right);
        return result;
    }
}
```

#### 中序

```java
//二叉树中序遍历
public static ArrayList<Integer> inorderTraversal(TreeNode root){
    ArrayList<Integer> result = new ArrayList<Integer>(15);

    if(root == null)
        return result;

    ArrayList<Integer> left = inorderTraversal(root.left);
    result.addAll(left);

    result.add(root.val);

    ArrayList<Integer> right = inorderTraversal(root.right);
    result.addAll(right);

    return result;
}
```

#### 后序

```java
//二叉树后续遍历
public static ArrayList<Integer> postOrderTraversal(TreeNode root){
    ArrayList<Integer> result = new ArrayList<Integer>(15);

    if(root == null)
        return result;

    ArrayList<Integer> left = postOrderTraversal(root.left);
    result.addAll(left);
    ArrayList<Integer> right = postOrderTraversal(root.right);
    result.addAll(right);

    result. add(root.val);

    return result;
}
```

#### 层次

```java
public ArrayList<ArrayList<Integer>> levelOrder(TreeNode root) {
        ArrayList result = new ArrayList();

        if (root == null) {
            return result;
        }

        Queue<TreeNode> queue = new LinkedList<TreeNode>();
        queue.offer(root);

        while (!queue.isEmpty()) {
            ArrayList<Integer> level = new ArrayList<Integer>();
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                TreeNode head = queue.poll();
                level.add(head.val);
                if (head.left != null) {
                    queue.offer(head.left);
                }
                if (head.right != null) {
                    queue.offer(head.right);
                }
            }
            result.add(level);
        }

        return result;
    }
```

#### 二叉树深度优先遍历

```java
    //深度优先搜索
    //利用栈， 先将右子树压入栈， 再将左子树压入栈
    public static void DFS(TreeNode root){
        Stack<TreeNode> stack = new Stack<TreeNode>();
        stack.push(root);

        while(!stack.empty()){
            TreeNode node = stack.peek();
            System.out.println(node.val);

            stack.pop();

            if(node.right != null){
                stack.push(node.right);
            }

            if(node.left != null){
                stack.push(node.left);
            }
        }
    }
```

## Reference

1. [面试精选：二叉树问题集锦](https://blog.csdn.net/xidiancoder/article/details/73658322)
2. [【47期】六大类二叉树面试题汇总解答](https://zhuanlan.zhihu.com/p/109845113)
