#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};



class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k)
    {
        if(head == nullptr)
            return nullptr;
        std::vector<ListNode*> nodes;
        ListNode *p1 = head;
        while(p1 != nullptr)
        {
            nodes.push_back(p1);
            p1 = p1->next;
        }

        int length = nodes.size();
        int head_index = (length -(k%length))%length;
        head = nodes[head_index];
        if(head_index != 0)
        {
            nodes[length-1]->next = nodes[0];
            nodes[head_index-1]->next = nullptr;
        }
        return head;
    }
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
