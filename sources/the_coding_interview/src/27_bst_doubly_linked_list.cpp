#include <iostream>

#include <BinaryTreeNode.h>

BinaryTreeNode *convert(BinaryTreeNode* root, BinaryTreeNode* tail);

/**
 * 把二叉搜索树转换成双向链表
 */ 
BinaryTreeNode *convert(BinaryTreeNode* root) {
    BinaryTreeNode *tail = convert(root, nullptr);

    // 指向双向链表的尾节点
    BinaryTreeNode *head = tail;
    while(head != nullptr && head->left != nullptr) {
        head = head->left;
    }
    return head;
}

/**
 * @param root 二叉搜索树的根
 * @return 尾节点
 */
BinaryTreeNode *convert(BinaryTreeNode* root, BinaryTreeNode* tail) {
    if(root == nullptr) {
        return nullptr;
    }

    BinaryTreeNode *current = root;

    if(current->left !=nullptr) {
        tail = convert(current->left, tail);
    }

    current->left = tail;
    if(tail != nullptr) {
        tail->right = current;
    }

    tail = current;

    if(current->right != nullptr) {
        tail = convert(current->right, tail);
    }
    return tail;
}

int main() {

    return 0;
}