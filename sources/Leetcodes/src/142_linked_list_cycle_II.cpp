/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <iostream>
#include <stdio.h>
#include <unordered_map>

using namespace std;

struct ListNode 
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution 
{
public:
    bool hasCycle(ListNode *head) 
    {
        if(head == nullptr)
            return false;
        ListNode * ptr1 = head;
        ListNode * ptr2 = head->next;

        while(ptr1 != ptr2 && ptr2 != nullptr)
        {
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
            if(ptr2 != nullptr)
                ptr2 = ptr2->next;
        }
        if(ptr2 == nullptr)
            return false;
        else
            return true;
    }
    ListNode *detectCycle(ListNode *head) 
    {
        if(head == nullptr)
            return nullptr;
        unordered_map<ListNode*, int> mp;
        ListNode *node = head;
        while(node != nullptr)
        {
            if(mp.find(node) != mp.end())
                return node;
            mp[node] = 1;
            node = node->next;
        }
        return nullptr;

    }
};

int main()
{
    return 0;
}