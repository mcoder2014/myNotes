#include <iostream>
#include <ListNode.h>

void rmNode(ListNode *head, ListNode *rmNode) {
    if (head == nullptr || rmNode == nullptr) {
        return;
    }

    if (rmNode->next != nullptr) {
        // 如果删除的不是尾节点
        rmNode->value = rmNode->next->value;
        ListNode *tmp = rmNode->next;
        rmNode->next = rmNode->next->next;
        delete tmp;
    } else if (rmNode == head) {
        // 删除的是头结点
        head = nullptr;
        delete rmNode;
        rmNode = nullptr;
    } else {
        // 删除尾节点
        ListNode* ptr = head;
        while(ptr->next != rmNode) {
            ptr = ptr->next;
        }

        ptr->next = nullptr;
        delete rmNode;
        rmNode = nullptr;
    }
}

int main() {


    return 0;
}