#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <vector>
#include <algorithm>
#include <stack>

template<class T>
class BinaryTree
{
public:
    BinaryTree():val(),left(nullptr), right(nullptr){}
    explicit BinaryTree(T value):val(value),left(nullptr),right(nullptr) {};

    // 左孩子
    BinaryTree *left;

    // 右孩子
    BinaryTree *right;

    // 值
    T val;

    /**
     * @brief preOrder
     * 前序遍历 迭代方式
     * @return
     */
    std::vector<T> preOrder()
    {
        std::stack<BinaryTree<T>*> stk;
        std::vector<T> result;

        BinaryTree<T> * p = this;
        while(p!=nullptr || !stk.empty())
        {
            while (p!=nullptr)
            {
                result.push_back(p->val);
                stk.push(p);
                p = p->left;
            }

            if(!stk.empty())
            {
                p = stk.top();
                stk.pop();
                p = p->right;
            }
        }
        return result;
    }

    /**
     * @brief inOrder
     * 中序遍历 迭代方式
     * @return
     */
    std::vector<T> inOrder()
    {
        std::stack<BinaryTree<T>*> stk;
        std::vector<T> result;

        BinaryTree<T> * p = this;
        while(p!=nullptr || !stk.empty())
        {
            while (p!=nullptr)
            {
                stk.push(p);
                p = p->left;
            }

            if(!stk.empty())
            {
                p = stk.top();
                stk.pop();
                result.push_back(p->val);
                p = p->right;
            }
        }
        return result;
    }

    /**
     * @brief postOrder
     * 后续遍历 迭代方式
     * @return
     */
    std::vector<T> postOrder()
    {
        std::stack<BinaryTree<T>*> stk;
        std::vector<T> result;
        stk.push(this);

        while(!stk.empty())
        {
            BinaryTree<T> *node = stk.top();
            result.push_back(node->val);
            stk.pop();

            if(node->left != nullptr)
                stk.push(node->left);
            if(node->right != nullptr)
                stk.push(node->right);
        }
        std::reverse(result.begin(), result.end());
        return result;
    }

    /**
     * @brief levelOrder
     * 层次遍历 迭代方式
     * @return
     */
    std::vector<T> levelOrder()
    {
        std::vector<T> result;
        std::vector<BinaryTree<T>*> lst;
        lst.push_back(this);
        lst.push_back(nullptr);
        while (!lst.empty())
        {
            BinaryTree<T> *node = lst[0];
            lst.erase(lst.begin());
            if(node == nullptr)
            {
                // 换行
                if(!lst.empty())
                {
                    lst.push_back(nullptr);
                    // change a new row
                }
            }
            else
            {
                result.push_back(node->val);
                if(node->left != nullptr)
                    lst.push_back(node->left);
                if(node->right != nullptr)
                    lst.push_back(node->right);
            }
        }

        return result;
    }

};

#endif // BINARYTREE_H
