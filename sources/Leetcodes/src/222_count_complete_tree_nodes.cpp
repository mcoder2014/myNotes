#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // 正常数节点个数的方法
    int countNodes(TreeNode* root) {
        if(root == nullptr) {
            return 0;
        }

        int leftCounts = countNodes(root->left);
        int rightCounts = countNodes(root->right);
        return 1 + leftCounts + rightCounts;
    }
};

int main()
{
    return 0;
}