#include <iostream>
#include <vector>
#include <stack>

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
    vector<int> preorderTraversal(TreeNode* root) 
    {
        vector<int> result;
        TreeNode *ptr = root;
        stack<TreeNode*> stk;
        while(ptr != nullptr || !stk.empty())
        {
            if(ptr != nullptr)
            {
                result.push_back(ptr->val);
                stk.push(ptr);
                ptr = ptr->left;
            }
            else
            {
                TreeNode* node = stk.top();
                stk.pop();
                ptr = node->right;
            }
            
        }
        return result;
    }
};

int main()
{
    return 0;
}