#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>

using namespace std;
struct DoublyNode {
    int data;
    DoublyNode *prev, *next;

    DoublyNode (int x) {
        data = x;
        prev = NULL;
        next = NULL;
    }
};

void add(DoublyNode **head, int x) {
    DoublyNode *ptr = new DoublyNode(x);
    ptr->next = *head;
    if (*head != NULL) (*head)->prev = ptr;
    *head = ptr;
}

class LRUCache {
    private:
        DoublyNode *head = NULL, *tail = NULL;
        map<DoublyNode*, int> nodeKey;
        map<int, DoublyNode*> keyNode;
        int k, count;

    public:
        LRUCache(int capacity) {
            k = capacity;
            count = 0;
			
			//dummy list (predefined)
            add(&head, -2);
            add(&head, -1);
            tail = head->next;  
        }
    
        void recentlyUsed (int key) {                               //adjusts the node with given key to the recent position
            keyNode[key]->prev->next = keyNode[key]->next;
            keyNode[key]->next->prev = keyNode[key]->prev;
            tail->prev->next = keyNode[key];
            keyNode[key]->next = tail;
            keyNode[key]->prev = tail->prev;
            tail->prev = keyNode[key];
        }
    
        int get(int key) {
            if (keyNode.find(key) == keyNode.end()) return -1;
            
            if (tail->prev != keyNode[key]) recentlyUsed(key);
            
            return keyNode[key]->data;
        }

        void put(int key, int value) {
            if (!(keyNode.find(key) == keyNode.end())) { keyNode[key]->data = value; recentlyUsed(key); }

            else {                                                  //if the key is distinct                             
                if (count >= k) {
                    keyNode.erase(nodeKey[head->next]);
                    nodeKey.erase(head->next);
                    head->next->next->prev = head;
                    head->next = head->next->next;
                    count--;
                }
				
				//add the new node for the given key to the doubly linked list
                DoublyNode* newNode = new DoublyNode(value);
                tail->prev->next = newNode;
                newNode->next = tail;
                newNode->prev = tail->prev;
                tail->prev = newNode;
                keyNode[key] = newNode;
                nodeKey[newNode] = key;
                count++;
            }
        }
};



/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main()
{

    LRUCache cache(2 /* capacity */);

    cache.put(1, 1);
    cache.put(2, 2);
    cache.get(1);    // returns 1
    cache.put(3, 3); // evicts key 2
    cache.get(2);    // returns -1 (not found)
    cache.put(4, 4); // evicts key 1
    cache.get(1);    // returns -1 (not found)
    cache.get(3);    // returns 3
    cache.get(4);    // returns 4

    return 0;
}