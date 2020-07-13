#include <iostream>
#include <stack>

using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(head == nullptr) {
            return true;
        }

        stack<ListNode*> stk;
        ListNode *ptr = head;
        while(ptr != nullptr) {
            stk.push(ptr);
            ptr = ptr->next;
        }

        int size = stk.size();
        int half = (size+1)/2;

        for(int i = 0; i < half; i++) {
            ptr = stk.top();
            stk.pop();
        }
        if(size %2 == 1) {
            ptr = ptr->next;
        }

        while(!stk.empty()) {
            if(ptr->val != stk.top()->val) {
                return false;
            }
            ptr = ptr->next;
            stk.pop();
        }

        return true;
    }
};

int main()
{
    return 0;
}