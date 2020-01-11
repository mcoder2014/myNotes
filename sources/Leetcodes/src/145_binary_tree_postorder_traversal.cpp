#include <iostream>
#include <stdio.h>
#include <stack>
#include <vector>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> nodes;
        stack<TreeNode*> stk;
        TreeNode * ptr = root;
        TreeNode * last = nullptr;
        while(ptr != nullptr || !stk.empty())
        {
            if(ptr !=nullptr)
            {
                stk.push(ptr);
                ptr = ptr->left;
            }
            else
            {
                TreeNode *node  = stk.top();
                if(node->right && last != node->right)
                    ptr = node->right;
                else
                {
                    nodes.push_back(node->val);
                    last = node;
                    stk.pop();
                }
            }
        }
        return nodes;
    }
};