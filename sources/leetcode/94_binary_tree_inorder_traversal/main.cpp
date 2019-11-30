#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root)
    {
        vector<TreeNode*> stk;
        TreeNode *p = root;
        vector<int> lst;
        while(p!=nullptr || !stk.empty())
        {
            while(p != nullptr)
            {
                stk.push_back(p);
                p = p->left;
            }
            if(!stk.empty())
            {
                p = stk[stk.size()-1];
                stk.pop_back();
                lst.push_back(p->val);
                p = p->right;
            }
        }
        return lst;
    }

    vector<TreeNode*> generateTrees(int n)
    {

    }
};

int main()
{

    return 0;
}
