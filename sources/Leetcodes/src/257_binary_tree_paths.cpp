#include <iostream>
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
    vector<string> binaryTreePaths(TreeNode* root) {
        paths.clear();
        vector<int> record;
        helper(record, root);
        return paths;
    }

    void helper(vector<int>& path, TreeNode* root) {
        if(root == nullptr) {
            return;
        }
        path.push_back(root->val);
        if(root->left == nullptr && root->right == nullptr) {
            paths.push_back(toString(path));
        } 
        
        if(root->left != nullptr) {
            helper(path, root->left);
        }

        if(root->right != nullptr) {
            helper(path, root->right);
        }

        path.pop_back();
    }

    string toString(vector<int>& path) {
        if(path.size() == 0) {
            return "";
        }
        string ret;
        for(int i = 0; i < path.size()-1; i++) {
            ret += to_string(path[i]);
            ret += "->";
        }
        ret += to_string(path[path.size()-1]);
        return ret;
    }

    vector<string> paths;
};

int main()
{
    return 0;
}