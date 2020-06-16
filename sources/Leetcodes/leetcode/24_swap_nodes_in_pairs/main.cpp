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
    ListNode* swapPairs(ListNode* head) {

        ListNode *p1 = head;
        ListNode *p2;   // 除了第一个循环，每个循环开始时存 p1 前一个结点

        while(p1 !=nullptr
              && p1->next != nullptr)
        {

            if(p1 == head)
            {
                p2 = p1->next;

                // 改变head 对第一个结点的引用
                head = p2;

                // 改变第一个结点对后续结点的引用
                p1->next = p2->next;
                // 改变两个结点之间的链接
                p2->next = p1;

                p2 = p1;        // p2 成为交换后的后一个结点
                p1 = p2->next;  // p1 成为这个结点的孩子节点
            }
            else
            {
                p2->next = p1->next;

                p2 = p1->next;
                p1->next = p2->next;
                p2->next = p1;

                p2 = p1;
                p1 = p2->next;
            }
        }

        return head;
    }
};

int main()
{
    return 0;
}
