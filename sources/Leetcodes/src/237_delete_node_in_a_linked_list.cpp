/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    void deleteNode(ListNode* node) {
        if(node->next != nullptr) {
            ListNode *next = node->next;
            node->val = next->val;
            node->next = next->next;
            delete next;
        }
    }
};

int main()
{
    return 0;
}