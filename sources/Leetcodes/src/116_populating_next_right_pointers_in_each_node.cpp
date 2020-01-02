#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) 
    {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) 
    {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) 
        {}
};

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/
class Solution {
public:

/// 利用层次遍历来做，O(n)的空间
    Node* connect(Node* root) 
    {
        if(root == nullptr)
            return nullptr;
        deque<Node*> queue;
        queue.push_back(root);
        queue.push_back(nullptr);
        Node * ptr;
        Node * last_node = nullptr;

        while(queue.size() >0)
        {
            ptr = queue.front();
            queue.pop_front();
            if(ptr == nullptr)
            {
                if(last_node != nullptr)
                    last_node->next = nullptr;
                last_node = nullptr;
                // 如果还有内容，则插入行标记
                if(queue.size() >0)
                    queue.push_back(nullptr);
            }
            else
            {
                if(last_node != nullptr)
                    last_node->next = ptr;
                
                last_node = ptr;
                
                if(ptr->left)   queue.push_back(ptr->left);
                if(ptr->right)  queue.push_back(ptr->right);
            }
        }
        return root;
    }


/// 利用满二叉树的特性，以及全部初始化为0的特性，只需要修改内部左右孩子结点，
/// 以及相邻的 右孩子和左孩子结点的链接
    Node *connect2(Node * root)
    {
        Node* level_start = root;
        while(level_start != nullptr)
        {
            Node *cur = level_start;
            while(cur != nullptr)
            {
                if(cur->left)
                    cur->left->next = cur->right;
                if(cur->right && cur->next)
                    cur->right->next = cur->next->left;
                cur = cur->next;
            }
            level_start = level_start->left;
        }
        return root;
    }

};
int main()
{
    
}