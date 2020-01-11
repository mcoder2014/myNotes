#include <iostream>
#include <stack>

using namespace std;

struct ListNode 
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode* head) 
    {
        if(head == nullptr)
            return;

        stack<ListNode*> stk;
        ListNode *ptr = head;
        while(ptr != nullptr)
        {
            stk.push(ptr);
            ptr = ptr->next;
        }

        int size = stk.size();
        ptr = head;
        for(int i = 0; i <(size)/2; i++)
        {
            ListNode *rptr = stk.top();
            stk.pop();
            rptr->next = ptr->next;
            ptr->next = rptr;
            ptr = rptr->next;
        }
        ptr->next = nullptr;

    }
};

int main()
{
    return 0;
}