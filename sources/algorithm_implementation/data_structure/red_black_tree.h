#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>
#include <vector>
#include <stack>
#include <string>

namespace Mcoder
{

enum RedBlackTreeNodeColor { RED, BLACK };

///
/// \brief The RedBlackTreeNode class
///
template<typename basetype>
class RedBlackTreeNode
{
public:
    RedBlackTreeNode<basetype> *parent;
    RedBlackTreeNode<basetype> *lchild;
    RedBlackTreeNode<basetype> *rchild;

    basetype data;
    RedBlackTreeNodeColor color;

    RedBlackTreeNode()
    {
        parent = nullptr;
        lchild = nullptr;
        rchild = nullptr;

        color = BLACK;
    }

    RedBlackTreeNode(RedBlackTreeNode<basetype> * NIL)
        :parent(NIL),lchild(NIL),rchild(NIL)
    {
        color = BLACK;
    }
};


///
/// \brief Red black tree data structure
///
template<typename basetype>
class RedBlackTree
{
public:
    RedBlackTreeNode<basetype> NIL;
    RedBlackTreeNode<basetype> *root;

    RedBlackTree()
    {
        // NIL node is always black
        NIL.lchild = &NIL;
        NIL.rchild = &NIL;
        NIL.parent = &NIL;
        NIL.color = BLACK;

        root = &NIL;    // is an empty tree
    }

    ~RedBlackTree()
    {
        // 通过中序遍历来释放 node 的空间
        std::vector<RedBlackTreeNode<basetype>*> nodes;

        // 中序遍历，迭代法
        if(root == &NIL) return;

        RedBlackTreeNode<basetype> *curr=root;
        std::stack<RedBlackTreeNode<basetype> *> st;

        while(!st.empty() || curr != &NIL)
        {
            while(curr!=&NIL)
            {
                st.push(curr);
                curr=curr->lchild;
            }
            curr=st.top();
            st.pop();

            nodes.push_back(curr);
            curr=curr->rchild;
        }

        for (RedBlackTreeNode<basetype>* node:nodes )
        {
            delete node;
        }
    }

    std::vector<basetype> inorder_iterative()
    {
        return inorder_iterative(this->root);
    }

    std::vector<basetype> inorder_iterative(RedBlackTreeNode<basetype> *root)
    {
        std::vector<basetype> rets;
        if(root == &NIL)
            return rets;

        RedBlackTreeNode<basetype> *curr = root;
        std::stack<RedBlackTreeNode<basetype> *> st;

        while(!st.empty() || curr != &NIL)
        {
            while (curr != &NIL)
            {
                st.push(curr);
                curr = curr->lchild;
            }

            curr = st.top();
            st.pop();

            rets.push_back(curr->data);
            curr = curr->rchild;
        }

        return rets;
    }

    std::vector<RedBlackTreeNode<basetype>*> inorder_iterative_nodes(RedBlackTreeNode<basetype>*root)
    {
        std::vector<RedBlackTreeNode<basetype>*> rets;
        if(root == &NIL)
            return rets;

        RedBlackTreeNode<basetype> *curr = root;
        std::stack<RedBlackTreeNode<basetype> *> st;

        while(!st.empty() || curr != &NIL)
        {
            while (curr != &NIL)
            {
                st.push(curr);
                curr = curr->lchild;
            }

            curr = st.top();
            st.pop();

            rets.push_back(curr);
            curr = curr->rchild;
        }

        return rets;
    }

    RedBlackTreeNode<basetype> *search(RedBlackTreeNode<basetype> *x, const basetype& key)
    {
        if(x == &NIL || key == x->data)
            return x;
        if(key < x->data)
            return search(x->lchild, key);
        else
            return search(x->rchild, key);
    }

    RedBlackTreeNode<basetype> *search_iterative(const basetype& key)
    {
        RedBlackTreeNode<basetype> *x = root;
        while (x!=&NIL && key != x->data)
        {
            if(key < x->data)
                x = x->lchild;
            else
                x= x->rchild;
        }

        return x;
    }

    RedBlackTreeNode<basetype> *minimum()
    {
        return minimum(this->root);
    }

    RedBlackTreeNode<basetype> *minimum(RedBlackTreeNode<basetype> *node)
    {
        if(node == &NIL) return &NIL;
        RedBlackTreeNode<basetype> *x = node;
        while( x->lchild != &NIL )
        {
            x = x->lchild;
        }
        return x;
    }

    RedBlackTreeNode<basetype> *maximum()
    {
        return maximum(this->root);
    }

    RedBlackTreeNode<basetype> *maximum(RedBlackTreeNode<basetype> *node)
    {
        if(node == &NIL) return &NIL;
        RedBlackTreeNode<basetype> *x = node;
        while (x->rchild != &NIL)
        {
            x = x->rchild;
        }
        return x;
    }

    RedBlackTreeNode<basetype> *successor(RedBlackTreeNode<basetype> *node)
    {
        if(node->rchild != &NIL)
            return minimum(node->rchild);

        // if the node does not have a right child, find the successor upper side
        RedBlackTreeNode<basetype> *y = node->parent;
        RedBlackTreeNode<basetype> *x = node;

        while (y != &NIL && x == y->rchild)
        {
            // x is right child means that x > y
            // x is left child means that x < y
            x = y;
            y = y->parent;
        }

        return y;
    }

    RedBlackTreeNode<basetype> *predecessor(RedBlackTreeNode<basetype> *node)
    {
        if(node->lchild != &NIL)
            return maximum(node->lchild);

        RedBlackTreeNode<basetype> *y = node->parent;
        RedBlackTreeNode<basetype> *x = node;

        while(y != &NIL && x == y->lchild)
        {
            x = y;
            y = y->parent;
        }

        return y;
    }

    RedBlackTreeNode<basetype> *insert(basetype key)
    {
        RedBlackTreeNode<basetype> *node = new RedBlackTreeNode<basetype>(&NIL);
        node->data = key;
        return insert(node);
    }

    RedBlackTreeNode<basetype> *insert(RedBlackTreeNode<basetype> *node)
    {
        RedBlackTreeNode<basetype> *y = &NIL;
        RedBlackTreeNode<basetype> *x = root;

        while (x != &NIL)
        {
            y = x;
            if(node->data < y->data)
                x = x->lchild;
            else
                x = x->rchild;
        }

        node->parent = y;
        if(y == &NIL)
            root = node;
        else if(node->data < y->data)
            y->lchild = node;
        else
            y->rchild = node;

        node->lchild = &NIL;
        node->rchild = &NIL;
        node->color = RED;

        insert_fixup(node);

        return node;
    }

    void insert_fixup(RedBlackTreeNode<basetype> *node)
    {
        RedBlackTreeNode<basetype> *y;
        while (node->parent->color == RED)
        {
            if(node->parent == node->parent->parent->lchild)
            {
                y = node->parent->parent->rchild;
                if(y->color == RED)
                {
                    // Case 1
                    // node是红色，node 的父节点和 父结点的兄弟结点 y 是红色
                    node->parent->color = BLACK;
                    y->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
                else
                {
                    if(node == node->parent->rchild)
                    {
                        // Case 2
                        // node 是红色， node 的父亲结点是红色， 父亲结点的兄弟结点是黑色
                        // node 是一个右孩子
                        node = node->parent;
                        left_rotation(node);
                    }
                    // Case 3
                    // node 是红色，父节点是红色，父结点的兄弟节点是黑色
                    // ndoe 是一个左孩子
                    // Case 3 之后，循环便会截止
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    right_rotation(node->parent->parent);
                }
            }
            else
            {
                // 与上方对称
                y = node->parent->parent->lchild;
                if(y->color == RED)
                {
                    // Case 1
                    // node是红色，node 的父节点和 父结点的兄弟结点 y 是红色
                    node->parent->color = BLACK;
                    y->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }
                else
                {
                    if(node == node->parent->lchild)
                    {
                        // Case 2
                        node = node->parent;
                        right_rotation(node);
                    }
                    // Case 3
                    // Case 3 之后，循环便会截止
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    left_rotation(node->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void left_rotation(RedBlackTreeNode<basetype> *node)
    {
        RedBlackTreeNode<basetype> *right = node->rchild;

        node->rchild = right->lchild;    // turn right's left child to node's right child
        if(right->lchild != &NIL)
            right->lchild->parent = node;

        right->parent = node->parent;
        if(node->parent == &NIL)
            root = right;
        else if(node == node->parent->lchild)
            node->parent->lchild = right;
        else
            node->parent->rchild = right;

        right->lchild = node;
        node->parent = right;
    }

    void right_rotation(RedBlackTreeNode<basetype> *node)
    {
        RedBlackTreeNode<basetype> *left = node->lchild;

        node->lchild = left->rchild;
        if(left->rchild != &NIL)
            left->rchild->parent = node;

        left->parent = node->parent;
        if(node->parent == &NIL)
            root = left;
        else if(node == node->parent->lchild)
            node->parent->lchild = left;
        else
            node->parent->rchild = left;

        left->rchild = node;
        node->parent = left;
    }

    void transplant(RedBlackTreeNode<basetype> *u, RedBlackTreeNode<basetype> *v)
    {
        if(u->parent == &NIL)
            root = v;
        else if(u == u->parent->lchild)
            u->parent->lchild =v;
        else
            u->parent->rchild = v;
        if(v != &NIL)
            v->parent = u->parent;
    }

    void remove(RedBlackTreeNode<basetype>* z)
    {
        RedBlackTreeNode<basetype> *y = z;  // y是将要删除的结点，或是在树内移动的结点（z的后继
        RedBlackTreeNode<basetype> *x;      // 记录 y的孩子结点 x，或者是 NIL
        RedBlackTreeNodeColor y_original_color = y->color;

        if(z->lchild == &NIL)
        {
            // 左支为空，用右支代替 z 的原本位置
            x = z->rchild;
            transplant(z, z->rchild);
        }
        else if(z->rchild == &NIL)
        {
            // 右支为空，用左支代替原本的位置
            x = z->lchild;
            transplant(z, z->lchild);
        }
        else
        {
           // 找到结点 z 的后继结点，准备将后继结点代替z原本的位置
           y = minimum(z->rchild);
           y_original_color = y->color;
           x = y->rchild;

           if(y->parent == z)
               x->parent = y;
           else
           {
               // 用 后继结点的右孩子 取代后继结点的位置
               transplant(y, y->rchild);
               y->rchild = z->rchild;
               y->rchild->parent = y;
           }

           // 将后继结点移动至 被删除结点的位置
           transplant(z, y);
           y->lchild = z->lchild;
           y->lchild->parent = y;
           y->color = z->color;
        }

        // 如果移动了黑色结点，则会导致黑高发生变换，破坏红黑树的性质
        if(y_original_color == BLACK)
            remove_fixup(x);
    }

    ///
    /// 因为 移出了一个黑色结点，导致x处的黑高被破坏，
    /// 假设 x 有一个额外的黑色，一次为思路进行处理
    ///
    void remove_fixup(RedBlackTreeNode<basetype> *x)
    {
        RedBlackTreeNode<basetype> *w;
        while(x != &NIL && x->color == BLACK)
        {
            if(x == x->parent->lchild)
            {
                w = x->parent->rchild;
                if(w->color == RED)
                {
                    // Case 1
                    // x 的兄弟结点是红色 x是黑色
                    // 转换为 case 2 进行处理
                    w->color = BLACK;
                    x->parent->color = RED;
                    left_rotation(x->parent);
                    w = x->parent->rchild;
                }

                if(w->lchild->color == BLACK && w->rchild->color == BLACK)
                {
                    // Case 2
                    // 兄弟结点是黑色，兄弟结点的两个孩子都是黑色
                    // 涂红兄弟结点，再上一层处理
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if(w->rchild->color == BLACK)
                    {
                        // Case 3
                        // 兄弟节点是黑的，左孩子红色，右孩子黑色
                        // 转换为 Case 4 处理
                        w->lchild->color = BLACK;   // 涂黑左孩子
                        w->color = RED;             // 涂黑 w
                        right_rotation(w);          // 用左孩子取代，w变成右孩子
                        w = x->parent->rchild;
                    }

                    // Case 4
                    // 兄弟结点是黑色，右孩子是红色，左孩子的颜色可以是红色也可是黑色
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->rchild->color = BLACK;
                    left_rotation(x->parent);
                    x = root;
                }
            }
            else
            {
                // 对称
                w = x->parent->lchild;
                if(w->color == RED)
                {
                    // Case 1
                    w->color = BLACK;
                    x->parent->color = RED;
                    right_rotation(x->parent);
                    w = x->parent->lchild;
                }

                if(w->rchild->color == BLACK && w->lchild->color == BLACK)
                {
                    // Case 2
                    w->color = RED;
                    x = x->parent;
                }
                else
                {
                    if(w->lchild->color == BLACK)
                    {
                        // Case 3
                        w->rchild->color = BLACK;
                        w->color = RED;
                        left_rotation(w);
                        w = x->parent->lchild;
                    }

                    // Case 4
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->lchild->color = BLACK;
                    right_rotation(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    std::vector<std::string> debug()
    {
        std::vector<std::string> ret;
        std::string title = "Key\tLeft\tRight\tParent\tColor";


        std::vector<RedBlackTreeNode<basetype>*> nodes = inorder_iterative_nodes(root);
        title = title + "\tSize:" + std::to_string(nodes.size());
        ret.push_back(title);

        for (RedBlackTreeNode<basetype>* item: nodes)
        {
            std::string info;
            info = std::to_string(item->data) + "\t"
                    + std::to_string(item->lchild->data) + "\t"
                    + std::to_string(item->rchild->data) + "\t"
                    + std::to_string(item->parent->data) + "\t";
            if(item->color == RED)
                info += "RED";
            else
                info += "BLACK";

            ret.push_back(info);
        }

        std::string nil;
        nil = std::to_string(NIL.data) + "\t"
                + std::to_string(NIL.lchild->data) + "\t"
                + std::to_string(NIL.rchild->data) + "\t"
                + std::to_string(NIL.parent->data) + "\t";
        if(NIL.color == RED)
            nil += "RED NIL";
        else
            nil += "BLACK NIL";

        ret.push_back(nil);

        return ret;
    }


};

}
#endif // RED_BLACK_TREE_H
