#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <iostream>

namespace Mcoder
{
template<typename basetype>
class LinkedListNode
{
public:
    LinkedListNode()
    {
        prev = nullptr;
        next = nullptr;
    }
    LinkedListNode<basetype>* prev;
    LinkedListNode<basetype>* next;
    basetype data;
};

template<typename basetype>
class DoublyLinkedList
{
public:
    LinkedListNode<basetype> *head;

    DoublyLinkedList()
    {
        head = nullptr;
    }
    ~DoublyLinkedList()
    {

        LinkedListNode<basetype> *node = head;
        LinkedListNode<basetype> *backup_node;
        while(node != nullptr)
        {
            backup_node = node;
            node = node->next;
            delete  backup_node;
        }

    }
    LinkedListNode<basetype> *search(basetype& value)
    {
        if(head == nullptr)
            return nullptr;

        LinkedListNode<basetype> *x = head;
        while(x != nullptr && x->data != value)
        {
            x = x->next;
        }
        return x;
    }

    void insert(basetype value)
    {
        LinkedListNode<basetype>* node = new LinkedListNode<basetype>();
        node->data = value;
        insert(node);
    }

    void insert(LinkedListNode<basetype> *node)
    {
        node->next = head;
        head->prev = node;

        // Move back the head pointer
        head = node;
        node->prev = nullptr;
    }

    void remove(LinkedListNode<basetype>* node)
    {
        if(node->prev != nullptr)
            node->prev->next = node->next;
        else
            head = node->next;
        if(node->next != nullptr)
            node->next->prev = node->prev;

        node->next = nullptr;
        node->prev = nullptr;
    }

};

template<typename basetype>
class DoublyLinkedListWithSentinel
{
public:
    LinkedListNode<basetype> nil;

    DoublyLinkedListWithSentinel()
    {
        nil.next = &nil;
        nil.prev = &nil;
    }
    ~DoublyLinkedListWithSentinel()
    {
        LinkedListNode<basetype> *node = nil.next;
        LinkedListNode<basetype> *backup_node;
        while(node != &nil)
        {
            backup_node = node;
            node = node->next;
            delete backup_node;
        }
    }

    LinkedListNode<basetype> *search(basetype& value)
    {
        LinkedListNode<basetype> *node = nil.next;
        while(node != &nil && node->data != value)
            node = node->next;
        return node;

    }
    void insert(basetype value)
    {
        LinkedListNode<basetype> *node = new LinkedListNode<basetype>();
        node->data = value;
        insert(node);
    }
    void insert(LinkedListNode<basetype>* node)
    {
        node->next = nil.next;
        nil.next->prev = node;
        nil.next = node;
        node->prev = nil;
    }

    void remove(LinkedListNode<basetype>* node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
};

///
/// doubly linekd list realized by three array
///
template<typename basetype>
class DoublyLinkedList_array
{
public:
    uint size;
    int *next;
    int *prev;
    basetype *key;

    int head;  // linked list's head point
    int free;  // linked list's free space

    DoublyLinkedList_array()
        :DoublyLinkedList_array(50)
    {

    }
    DoublyLinkedList_array(uint size)
    {
        this->size = size;
        next = new int[size];
        prev = new int[size];
        key = new basetype[size];

        head = -1;

        // create free linked list
        for(int i=0; i < size-1; i++)
        {
            next[i] = i+1;
        }
        next[size-1] = -1;

    }
    ~DoublyLinkedList_array()
    {
        if(next != nullptr)
            delete [] next;
        if(prev != nullptr)
            delete [] prev;
        if(key != nullptr)
            delete [] key;
    }

    int search(basetype value)
    {
        int node = head;
        while(next[node] != -1 && prev[node] != value)
        {
            node = next[node];
        }
        return node;
    }

    bool insert(basetype value)
    {
        int free_space = allocate_node();
        if(free_space == -1)
            return false;
        else
        {
            next[free_space] = head;
            prev[head] = free_space;
            key[free_space] = value;

            this->head = free_space;
        }
    }

    int remove(uint index)
    {
        // next.prev = prev
        prev[next[index]] = prev[index];
        // prev.next = next
        next[prev[index]] = next[index];

        free_node(index);
    }

    int allocate_node()
    {
        if(free == -1)
        {
            std::cout << "out of space" << std::endl;
            return -1;
        }
        else
        {
            int x = free;
            free = next[free];
            return x;
        }
    }
    void free_node(int node)
    {
        next[node] = free;
        free = node;
    }
};

}


#endif // DOUBLYLINKEDLIST_H
