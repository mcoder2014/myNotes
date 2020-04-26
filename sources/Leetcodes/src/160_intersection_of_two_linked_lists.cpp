#include <stack>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if(headA == nullptr || headB == nullptr)
            return nullptr;

        std::stack<ListNode*> stackA;
        std::stack<ListNode*> stackB;
        push(stackA, headA);
        push(stackB, headB);

        ListNode * lastIntersectNode = nullptr;
        while(stackA.size() > 0 && stackB.size() > 0
                && stackA.top() == stackB.top()) {
            lastIntersectNode = stackA.top();
            stackA.pop();
            stackB.pop();
        }
        return lastIntersectNode;   
    }

    void push(std::stack<ListNode*>& stk, ListNode* head) {
        while(head != nullptr) {
            stk.push(head);
            head = head->next;
        }
    }
};

int main()
{
    return 0;
}