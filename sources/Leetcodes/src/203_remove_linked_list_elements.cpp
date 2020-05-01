#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode* node = head;
        while(node != nullptr) {
            if(node->val == val) {
                if(node == head) {
                    node = removeNode(head, node);
                    head = node;
                } else {
                    node = removeNode(head, node);
                }        
            } else {
                node = node->next;
            }
        }
        return head;
    }

    ListNode* removeNode(ListNode *root, ListNode* node) {
        if(node->next != nullptr) {
            node->val = node->next->val;
            node-> next = node->next->next;
            return node;
        } else if (root == node){
            return nullptr;
        } else {
            while(root->next!=nullptr && root->next != node) {
                root = root->next;
            }
            root->next = nullptr;
            return nullptr;
        }
    }
};

int main()
{
    return 0;
}