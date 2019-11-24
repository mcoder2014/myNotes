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

    /// 86.partition list
    ListNode* partition(ListNode* head, int x)
    {
        ListNode node1(0), node2(0);
        ListNode *p1 = &node1, *p2 = &node2;
        ListNode *ptr=head;
        while(ptr!=nullptr)
        {
            if(ptr->val < x)
            {
                p1->next = ptr;
                p1 = p1->next;
            }
            else
            {
                p2->next = ptr;
                p2 = p2->next;
            }
            ListNode *tmp = ptr;
            ptr=ptr->next;
            tmp->next = nullptr;
        }
        if(node1.next != nullptr)
            head = node1.next;
        else
            head = node2.next;
        p1->next = node2.next;
        return head;
    }
};

int main()
{

    return 0;
}
