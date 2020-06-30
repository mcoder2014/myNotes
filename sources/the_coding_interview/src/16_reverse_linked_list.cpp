#include <iostream>
#include <ListNode.h>

ListNode *reverseList(ListNode* head) {
    ListNode *reverseHead = nullptr;
    ListNode * node = head;
    ListNode * prev = nullptr;

    while(node != nullptr) {
        ListNode * next = node->next;
        if(next == nullptr) {
            reverseHead = prev;
        }
        node->next = prev;

        prev = node;
        node = next;
    }
    return reverseHead;
}

int main() {
    return 0;
}