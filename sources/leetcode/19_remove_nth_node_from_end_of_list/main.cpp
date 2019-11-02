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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        stack<ListNode*> s;
        ListNode *ptr = head;
        while(ptr != nullptr)
        {
            s.push(ptr);
            ptr = ptr->next;
        }

        ListNode *ptr_n = nullptr;
        for(int i =0; i < n-1; i++)
        {
//            ptr_n = s.top();
            s.pop();
        }

        ptr_n = s.top();
        s.pop();
        // 找到父节点
        ListNode *ptr_p;
        if(s.size() > 0)
            ptr_p = s.top();
        else
        {
            // root node
            return ptr_n->next;
        }

        ptr_p->next = ptr_n->next;
        ptr_n->next = nullptr;
        return head;
    }
};


int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
