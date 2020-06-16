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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *head = nullptr;

        ListNode *p1 = l1;
        ListNode *p2 = l2;
        ListNode *p3 = head;
        ListNode *tmp = nullptr;
        int more = 0;   // 进位

        // 两者都有的位数部分
        while(p1 != nullptr && p2 != nullptr)
        {
            int value = p1->val + p2->val + more;
            more = value / 10;

            tmp = new ListNode(value%10);    // this node value
            if(p3 == nullptr)
            {
                p3 = tmp;
                head = tmp;
            }
            else
            {
                p3->next = tmp;
                p3 = p3->next;
            }
            p1 = p1->next;
            p2 = p2->next;
        }

        ListNode *p_remain = nullptr;
        if(p1 != nullptr)
            p_remain = p1;
        if(p2 != nullptr)
            p_remain = p2;

        // 位数更长的那个数字的剩余部分
        while (p_remain != nullptr)
        {
            int value = p_remain->val + more;
            more = value / 10;
            tmp = new ListNode(value%10);    // this node value
            if(p3 == nullptr)
            {
                p3 = tmp;
                head = tmp;
            }
            else
            {
                p3->next = tmp;
                p3 = p3->next;
            }
            p_remain = p_remain->next;
        }

        // 如果最后还需要进一位
        if(more != 0)
        {
            tmp = new ListNode(more);
            more = 0;
            if(p3 == nullptr)
            {
                p3 = tmp;
                head = tmp;
            }
            else
            {
                p3->next = tmp;
                p3 = p3->next;
            }
        }

        return head;
    }
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
