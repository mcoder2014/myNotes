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

    Node* connect(Node* root) 
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