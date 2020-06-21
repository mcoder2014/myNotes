#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "LinkedListNode.h"

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
#endif // DOUBLYLINKEDLIST_H
