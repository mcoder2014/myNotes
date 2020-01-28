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
    ListNode* insertionSortList(ListNode* head) 
    {
        if(head == nullptr) return nullptr;
        ListNode *ptr = head->next;
        ListNode *ptr_slow = head;
        
        while(ptr != nullptr)
        {
            ListNode *insertPos = head;
            ListNode *ptr_next = ptr->next;

            while(insertPos != ptr)
            {
                if(insertPos->val > ptr->val)
                {
                    break;
                }
                insertPos = insertPos->next;
            }

            if(insertPos != ptr)
            {
                // remove
                ptr_slow->next = ptr_next;

                ptr->next = insertPos->next;
                insertPos->next = ptr;

                int tmp = insertPos->val;
                insertPos->val = ptr->val;
                ptr->val = tmp;

                // 后插法带来的错误
                if(ptr_slow == insertPos)
                    ptr_slow = ptr_slow->next;

            }
            else
            {
                ptr_slow = ptr_slow->next;
            }
            
            ptr = ptr_next;
            // ptr_slow = ptr_slow->next;
        }
        return head;
    }
};

int main()
{
    return 0;
}