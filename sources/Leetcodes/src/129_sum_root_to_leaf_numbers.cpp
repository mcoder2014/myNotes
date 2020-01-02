#include <iostream>
#include <stdio.h>
#include <algorithm>

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
    int sumNumbers(TreeNode* root) 
    {
        if(root == nullptr)
            return 0;
        return sumNumbers(root, 0); 
    }

    int sumNumbers(TreeNode* root, int parent)
    {
        if(root == nullptr)
            return 0;

        int curVal = 10 * parent + root->val;

        if(root->left == nullptr &&
            root->right == nullptr)
            {
                // leaf
                return curVal;
            }

        int left = sumNumbers(root->left, curVal);
        int right = sumNumbers(root->right, curVal);

        return left + right;
    }
};

int main()
{
    return 0;
}