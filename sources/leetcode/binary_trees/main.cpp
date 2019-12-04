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

class Solution {
public:
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

    /// 101 symmetric tree
    bool isSymmetric(TreeNode* root)
    {
        if(root == nullptr)
            return true;
        return isSymmetric(root->left, root->right);
    }

    bool isSymmetric(TreeNode* lchild, TreeNode* rchild)
    {
        if(lchild ==nullptr && rchild == nullptr)
        {
            return true;
        }
        else if(lchild ==nullptr | rchild == nullptr)
        {
            return false;
        }
        else
        {
            // Check root
            if(lchild->val != rchild->val)
                return false;
            bool sl = isSymmetric(lchild->left, rchild->right);
            sl = sl && isSymmetric(lchild->right, rchild->left);
            return sl;
        }
    }

    /// 102 binary tree level order traversal
    vector<vector<int>> levelOrder(TreeNode* root)
    {
        vector<vector<int>> result;
        if(root == nullptr) return result;
        vector<int> layer;
        list<TreeNode*> node_list;
        TreeNode * p = root;
        node_list.push_back(nullptr);   // sep
        while (p!=nullptr)
        {
            layer.push_back(p->val);
            if(p->left != nullptr)
                node_list.push_back(p->left);
            if(p->right != nullptr)
                node_list.push_back(p->right);

            p = node_list.front();
            node_list.pop_front();
            if(p == nullptr)
            {
                result.push_back(layer);
                layer.clear();
                if(!node_list.empty())
                {
                    node_list.push_back(nullptr);
                    p = node_list.front();
                    node_list.pop_front();
                }
            }
        }
        if(!layer.empty())
            result.push_back(layer);
        return result;
    }

    /// 107 binary tree level order traversal II
    vector<vector<int>> levelOrderBottom(TreeNode* root)
    {
        vector<vector<int>> result;
        if(root == nullptr) return result;
        vector<int> layer;
        list<TreeNode*> node_list;
        TreeNode * p = root;
        node_list.push_back(nullptr);   // sep
        while (p!=nullptr)
        {
            layer.push_back(p->val);
            if(p->left != nullptr)
                node_list.push_back(p->left);
            if(p->right != nullptr)
                node_list.push_back(p->right);

            p = node_list.front();
            node_list.pop_front();
            if(p == nullptr)
            {
                result.push_back(layer);
                layer.clear();
                if(!node_list.empty())
                {
                    node_list.push_back(nullptr);
                    p = node_list.front();
                    node_list.pop_front();
                }
            }
        }
        if(!layer.empty())
            result.push_back(layer);
        reverse(result.begin(), result.end());
        return result;
    }

    /// 103 binary tree zigzag level order traversal
    vector<vector<int>> zigzagLevelOrder(TreeNode* root)
    {
        vector<vector<int>> result;
        if(root == nullptr) return result;
        vector<int> layer;
        list<TreeNode*> node_list;
        TreeNode * p = root;
        node_list.push_back(nullptr);   // sep
        int flag = 0;
        while (p!=nullptr)
        {
            layer.push_back(p->val);
            if(p->left != nullptr)
                node_list.push_back(p->left);
            if(p->right != nullptr)
                node_list.push_back(p->right);

            p = node_list.front();
            node_list.pop_front();
            if(p == nullptr)
            {
                if(flag++%2 == 0)
                    result.push_back(layer);
                else
                {
                    std::reverse(layer.begin(),layer.end());
                    result.push_back(layer);
                }
                layer.clear();
                if(!node_list.empty())
                {
                    node_list.push_back(nullptr);
                    p = node_list.front();
                    node_list.pop_front();
                }
            }
        }
        if(!layer.empty())
            result.push_back(layer);
        return result;
    }

    /// 104 maximum depth of binary tree
    int maxDepth(TreeNode* root)
    {
        if(root == nullptr) return 0;
        int left = 0, right = 0;
        if(root->left == nullptr && root->right == nullptr)
            return 1;
        if(root->left != nullptr)
            left = maxDepth(root->left);
        if (root->right != nullptr)
            right = maxDepth(root->right);

        return max(left, right)+1;
    }

    /// 105 construct binary tree from preorder and inorder traversal
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
    {
        return buildTree_pre_in(preorder, inorder, 0, preorder.size(), 0, inorder.size());
    }

    TreeNode* buildTree_pre_in(vector<int>& preorder, vector<int>& inorder,
                               int pre_begin, int pre_end,
                               int in_beigin, int in_end)
    {
        TreeNode* root = nullptr;
        if(pre_begin < pre_end && in_beigin < in_end)
        {
            root = new TreeNode(preorder[pre_begin]);
            vector<int>::iterator sep = find(inorder.begin()+in_beigin, inorder.begin()+in_end, preorder[pre_begin]);
            int span = sep - (inorder.begin()+in_beigin);
            root->left = buildTree_pre_in(preorder,inorder, pre_begin + 1,pre_begin+1+span, in_beigin, in_beigin + span);
            root->right = buildTree_pre_in(preorder,inorder, pre_begin+1+span, pre_end, in_beigin+span+1, in_end);
        }
        return root;
    }

    /// 106 construct binary tree from inorder and postorder traversal
    TreeNode* buildTree_post_in(vector<int>& inorder, vector<int>& postorder)
    {
        return buildTree_post_in(inorder,postorder,0,postorder.size(),0,inorder.size());
    }

    TreeNode* buildTree_post_in(vector<int>& inorder, vector<int>& postorder,
                                int post_begin, int post_end,
                                int in_begin, int in_end)
    {
        TreeNode *root = nullptr;

        if(post_begin<post_end && in_begin < in_end)
        {
            root = new TreeNode(postorder[post_end-1]);
            vector<int>::iterator sep = find(inorder.begin()+in_begin, inorder.begin()+in_end, postorder[post_end-1]);
            int span = sep - (inorder.begin()+in_begin);
            root->left = buildTree_post_in(inorder,postorder, post_begin, post_begin+span, in_begin, in_begin+span);
            root->right = buildTree_post_in(inorder,postorder, post_begin+span, post_end-1, in_begin+span+1, in_end);
        }
        return root;
    }


};
int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
