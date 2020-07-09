#include <iostream>

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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        ListNode *p1 = l1;
        ListNode *p2 = l2;
        ListNode *p3 = nullptr;
        ListNode *l3 = nullptr;

        while(p1 != nullptr && p2!=nullptr)
        {
            ListNode *node = new ListNode(0);
            if(p1->val < p2->val)
            {
                node->val = p1->val;
                p1 = p1->next;
            }
            else
            {
                node->val = p2->val;
                p2 = p2->next;
            }

            if(p3 == nullptr)
            {
                // create the head point
                p3 = node;
                l3 = p3;
            }
            else
            {
                p3->next = node;
                p3 = p3->next;
            }
        }

        ListNode *other = p1==nullptr? p2:p1;
        while(other != nullptr)
        {
            ListNode *node = new ListNode(0);
            node->val = other->val;
            other = other->next;
            if(p3 == nullptr)
            {
                // create the head point
                p3 = node;
                l3 = p3;
            }
            else
            {
                p3->next = node;
                p3 = p3->next;
            }
        }

        return  l3;
    }
};



int main()
{

    return 0;
}
