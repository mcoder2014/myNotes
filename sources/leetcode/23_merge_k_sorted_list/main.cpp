#include <iostream>
#include <vector>
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
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 向一个同一个链表插入
        ListNode *head = nullptr;
        ListNode *ptr = nullptr;
        for(ListNode* l:lists)
        {
            ptr = head; // 从链表头部开始
            while(l != nullptr)
            {
                // 向 head 链表插入当前的结点
                if(ptr == nullptr)
                {
                    ptr = new ListNode(l->val);
                    head = ptr;
                    l = l->next;
                    continue;
                }

                while(head!=nullptr && l!= nullptr
                      && head->val > l->val)
                {
                    // 插入到头部
                    ListNode *node = new ListNode(l->val);
                    node->next = head;
                    head = node;
                    ptr = head;
                    l = l->next;
                }

                while(ptr->next != nullptr
                        && l!= nullptr
                        && ptr->val < l->val
                        && ptr->next->val < l->val)
                    ptr = ptr->next;

                if(l != nullptr)
                {
                    ListNode *node = new ListNode(l->val);
                    node->next = ptr->next;
                    ptr->next = node;
                    ptr = node;
                    l = l->next;
                }
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
