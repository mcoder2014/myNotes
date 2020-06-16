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
   ListNode* reverseBetween(ListNode* head, int m, int n)
   {
       ListNode node(0);
       ListNode *dummy = &node, *pre = dummy, *cur;
       dummy -> next = head;
       for (int i = 0; i < m - 1; i++)
       {
           pre = pre -> next;
       }
       cur = pre -> next;
       for (int i = 0; i < n - m; i++)
       {
           ListNode* temp = pre -> next;
           pre -> next = cur -> next;
           cur -> next = cur -> next -> next;
           pre -> next -> next = temp;
       }
       return dummy -> next;
   }
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
