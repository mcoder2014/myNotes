#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <deque>

using namespace std;

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Node
{
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};


//// 和图的深度拷贝那道题目很像
class Solution
{
public:
    Node *copyRandomList(Node *head)
    {
        if(head == nullptr)
            return nullptr;
        unordered_map<Node *, Node *> mp;
        deque<Node *> que;
        Node *node = head;
        que.push_back(node);
        mp[node] = new Node(0);

        while (que.size())
        {
            Node *node = que.front();
            que.pop_front();

            mp[node]->val = node->val;
            if (node->next != nullptr)
            {
                if (mp.find(node->next) == mp.end())
                {
                    mp[node->next] = new Node(0);
                    que.push_back(node->next);
                }
                mp[node]->next = mp[node->next];
            }
            if (node->random != nullptr)
            {
                if (mp.find(node->random) == mp.end())
                {
                    mp[node->random] = new Node(0);
                    que.push_back(node->random);
                }
                mp[node]->random = mp[node->random];
            }
        }
        return mp[node];
    }
};

int main()
{

    return 0;
}