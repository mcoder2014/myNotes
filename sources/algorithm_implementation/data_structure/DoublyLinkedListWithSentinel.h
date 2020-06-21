#ifndef DOUBLYLINKEDLISTWITHSENTINEL_H
#define DOUBLYLINKEDLISTWITHSENTINEL_H

#include "LinkedListNode.h"

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

#endif // DOUBLYLINKEDLISTWITHSENTINEL_H
