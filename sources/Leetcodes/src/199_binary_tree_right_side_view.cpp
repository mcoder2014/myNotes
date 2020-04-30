#include <iostream>
#include <vector>
#include <deque>
using namespace std;


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 层次遍历，每层只保留最右节点
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        deque<TreeNode*> nodes; 
        nodes.push_back(root);
        nodes.push_back(nullptr);
        vector<int> result;
        int layer = 0;

        while(nodes.size() > 0) {
            TreeNode* node = nodes[0];
            nodes.pop_front();

            if(result.size() == layer) {
                result.push_back(node->val);
            } else {
                result[layer] = node->val;
            }

            if(node->left != nullptr) {
                nodes.push_back(node);
            }
            if(node->right != nullptr) {
                nodes.push_back(node);
            }
            
            if(nodes.size() > 0 && nodes[0] == nullptr) {
                layer++;
                nodes.pop_front();
                if(nodes.size() != 0) {
                    nodes.push_back(nullptr);
                }
            }
        }   
        return result;
    }
};

int main()
{
    return 0;
}