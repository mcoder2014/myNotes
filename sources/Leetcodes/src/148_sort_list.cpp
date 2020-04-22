/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution
{
public:
    /**
     * 归并排序、快速排序都是 nlogn 
     */
    ListNode *sortList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
        {
            return head;
        }

        ListNode *fast = head;
        ListNode *slow = head;

        while (fast->next != nullptr && fast->next->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
        }

        fast = slow;
        slow = slow->next;
        fast->next = nullptr;

        head = sortList(head);
        slow = sortList(slow);
        return merge(head, slow);
    }

    ListNode *merge(ListNode *left, ListNode *right)
    {
        ListNode *head = nullptr;
        ListNode *ptr = nullptr;
        if (left->val > right->val)
        {
            head = right;
            right = right->next;
        }
        else
        {
            head = left;
            left = left->next;
        }
        ptr = head;

        while (left != nullptr && right != nullptr)
        {
            ListNode *node = nullptr;
            if (left->val > right->val)
            {
                ptr->next = right;
                ptr = ptr->next;
                right = right->next;
            }
            else
            {
                ptr->next = left;
                ptr = ptr->next;
                left = left->next;
            }
        }
        if(left != nullptr)
        {
            ptr->next = left;
        }
        else
        {
            ptr->next = right;
        }
        return head;
    }
};

int main()
{
    return 0;
}
