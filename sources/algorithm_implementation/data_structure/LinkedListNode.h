#ifndef LINKEDLISTNODE_H
#define LINKEDLISTNODE_H
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
#endif // LINKEDLISTNODE_H
