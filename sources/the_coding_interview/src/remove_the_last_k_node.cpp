#include <iostream>
using namespace std;

class ListNode
{
public:
    ListNode* next;
    int value;
};

ListNode * removeKNode(ListNode* root, int k)
{
    ListNode *ptr = root;
    ListNode *slowPtr = root;
    ListNode *slowPtrParent = nullptr;
    
    for(int i = 0; i < k; i++) 
    {
        ptr = ptr->next;
    }
    
    while(ptr != nullptr)
    {
        ptr = ptr->next;
        slowPtr = slowPtr->next;
        if(slowPtrParent == nullptr) 
        {
            slowPtrParent = root;
        }
        else
        {
            slowPtrParent = slowPtrParent->next;
        }
    }
    
    // remove slowPtr
    if(root == slowPtr)
    {
        // k = size slowptr = root
        root = slowPtr->next;
        delete slowPtr;
    }
    else
    {
        slowPtrParent->next = slowPtr->next;
        delete slowPtr;
    }
    
}

int main() {
    //int a;
    //cin >> a;
    cout << "Hello World!" << endl;
}