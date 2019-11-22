#include <iostream>
#include <vector>
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
    ListNode* deleteDuplicates(ListNode* head)
    {
        stack<ListNode*> stk;
        ListNode *ptr = head;
        while(ptr != nullptr)
        {
            stk.push(ptr);
            ptr = ptr->next;
        }

        while(!stk.empty())
        {
            head = stk.top();
            stk.pop();
            bool isValid = true;
            while(!stk.empty() && stk.top()->val == head->val)
            {
                isValid = false;
                stk.pop();
            }
            if(isValid)
            {
                head->next = ptr;
                ptr = head;
            }
        }

        return ptr;
    }
};

int main()
{

    return 0;
}
