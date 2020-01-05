#include <deque>
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {}

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {}

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    Node* cloneGraph(Node* node) 
    {
        if(node == nullptr)
            return nullptr;

        unordered_map<Node*, Node*> mp;
        mp[node] = new Node();
        deque<Node*> que;
        que.push_back(node);
        // Get all the node first
        while(!que.empty())
        {
            Node* cur = que.front();
            que.pop_front();

            Node *newnode = mp[cur];
            newnode->val = cur->val;

            for(Node *neighbour: cur->neighbors)
            {
                if(mp.find(neighbour) != mp.end())
                {
                    newnode->neighbors.push_back(mp[neighbour]);
                }
                else
                {
                    Node *tmp = new Node();
                    mp[neighbour] = tmp;
                    newnode->neighbors.push_back(mp[neighbour]);
                    que.push_back(neighbour);
                }
            }
        }
        return mp[node];    
    }


};

int main()
{
    return 0;
}