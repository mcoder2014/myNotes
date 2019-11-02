#include <iostream>
#include <stack>
using namespace std;

struct ListNode {
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
    ListNode* reverseKGroup(ListNode* head, int k) {
        stack<ListNode *> lstack;
        ListNode *ptr = head;
        ListNode *pprev = nullptr;  // 记录之前的结点
        bool head_part = true;
        while (ptr !=nullptr)
        {

            for (int i=0; i < k; i++)
            {
                // 中断
                if(ptr == nullptr)
                    return head;
                lstack.push(ptr);
                ptr = ptr->next;
            }

            if(head_part)
            {
                head_part = false;
                head = lstack.top();
                ListNode * p1 = lstack.top();
                lstack.pop();
                for (int i = 1; i <k; i++) {
                    p1->next = lstack.top();
                    lstack.pop();
                    p1 = p1->next;
                }
                p1->next = ptr;
                pprev = p1;
            }
            else
            {
                for (int i =0; i < k; i++)
                {
                    pprev->next = lstack.top();
                    lstack.pop();
                    pprev = pprev->next;

                }
                pprev->next =ptr;
            }
        }

        return head;
    }
};

int main()
{
    ListNode *head = new ListNode(1);
    ListNode *ptr = head;
    ptr->next = new ListNode(2);
    ptr = ptr->next;
    ptr->next = new ListNode(3);
    ptr = ptr->next;
    ptr->next = new ListNode(4);
    ptr = ptr->next;
    ptr->next = new ListNode(5);
    ptr = ptr->next;
    ptr->next = new ListNode(6);
    ptr = ptr->next;

    Solution solution;
    head = solution.reverseKGroup(head, 3);
    ptr = head;

    while(ptr != nullptr)
    {
        cout << ptr->val << "->";
        ptr = ptr->next;
    }
    cout << "null\t";

    return 0;
}
