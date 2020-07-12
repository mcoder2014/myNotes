/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
#include <iostream>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        if(root == nullptr) {
            return -1;
        }

        int count = 0;
        TreeNode *ptr = root;
        stack<TreeNode*> stk;
        
        while(!stk.empty() || ptr != nullptr) {

            while(ptr!= nullptr) {
                stk.push(ptr);
                ptr = ptr->left;
            }

            // 处理 ptr
            if(!stk.empty()) {
                ptr = stk.top();
                stk.pop();
                if(++count == k) {
                    return ptr->val;
                }

                // 处理右子树
                ptr = ptr->right;
            }
        }
        return -1;
    }
};

int main()
{
    return 0;
}