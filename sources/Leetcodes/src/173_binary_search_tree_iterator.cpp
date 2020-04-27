#include <iostream>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
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
class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        this->root = root;
        currentNode = root;
    }
    
    /** @return the next smallest number */
    int next() {
        while(currentNode!=nullptr || !treeStack.empty())
        {
            while (currentNode!=nullptr)
            {
                treeStack.push(currentNode);
                currentNode = currentNode->left;
            }

            if(!treeStack.empty())
            {
                currentNode = treeStack.top();
                treeStack.pop();
                int result = currentNode->val;
                currentNode = currentNode->right;
                return result;
            }
        }
        return 0;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return (currentNode != nullptr || !treeStack.empty());
    }

    TreeNode *root;
    TreeNode *currentNode;
    stack<TreeNode*> treeStack;
    
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */

int main()
{
    return 0;
}