#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    /// 98.validate binary search tree
    bool isValidBST(TreeNode* root) {
       return dfs_valid(root, LONG_MIN, LONG_MAX);
   }
   bool dfs_valid(TreeNode *root, long low, long high) {
       if (!root) return true;
       return low < root->val && root->val < high
               && dfs_valid(root->left, low, root->val)
               && dfs_valid(root->right, root->val, high);
   }

   /// 100 same tree
   bool isSameTree(TreeNode* p, TreeNode* q)
   {
        if(p == nullptr && q ==nullptr)
            return true;
        else if (p ==nullptr || q==nullptr)
            return false;

        return p->val == q->val
                && isSameTree(p->left, q->left)
                && isSameTree(p->right, q->right);
   }

};

int main()
{
    return 0;
}
