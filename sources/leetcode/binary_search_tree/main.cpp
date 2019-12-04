#include <iostream>
#include <vector>
#include <list>
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

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
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

    /// 108 convert sorted array to binary search tree
    TreeNode* sortedArrayToBST(vector<int>& nums)
    {
        return sortedArrayToBST(nums, 0, nums.size());
    }
    TreeNode* sortedArrayToBST(vector<int>& nums, int begin, int end)
    {
        TreeNode* root = nullptr;
        if(begin < end)
        {
            int mid = (begin + end)/2;
            root = new TreeNode(nums[mid]);
            root->left = sortedArrayToBST(nums, begin, mid);
            root->right = sortedArrayToBST(nums, mid+1,end);
        }
        return root;
    }

    /// 109 convert sorted list to binary search tree
    TreeNode* sortedListToBST(ListNode* head)
    {
        vector<int> nums;
        ListNode *ptr = head;
        while (ptr!=nullptr)
        {
            nums.push_back(ptr->val);
            ptr = ptr->next;
        }
        return sortedArrayToBST(nums);
    }

    /// 110 balanced binary tree
    bool isBalanced(TreeNode* root)
    {
        int height = 0;
        return isBalanced(root, height);
    }

    bool isBalanced(TreeNode* root, int& height)
    {
        if(root == nullptr)
        {
            height=0;
            return  true;
        }
        int leftHeight = 0;
        int rightHeight = 0;
        if(!isBalanced(root->left, leftHeight)) return false;
        if(!isBalanced(root->right, rightHeight)) return false;

        if(abs(leftHeight-rightHeight) > 1) return false;
        height = max(leftHeight, rightHeight)+1;
        return true;
    }

    /// 111 minimum depth of binary tree
    int minDepth(TreeNode* root)
    {
        if(root == nullptr)
            return 0;
        int leftHeight = minDepth(root->left);
        int rightHeight = minDepth(root->right);
        if(leftHeight * rightHeight == 0)
            return max(leftHeight, rightHeight) + 1;
        else
            return min(leftHeight, rightHeight) + 1;
    }


};

int main()
{
    return 0;
}
