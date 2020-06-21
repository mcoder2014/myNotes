#ifndef DOUBLYLINKEDLISTARRAY_H
#define DOUBLYLINKEDLISTARRAY_H

#include <iostream>

/**
 * doubly linekd list realized by three array
 */
template<typename basetype>
class DoublyLinkedListArray
{
public:
    uint size;
    int *next;
    int *prev;
    basetype *key;

    int head;  // linked list's head point
    int free;  // linked list's free space

    DoublyLinkedListArray()
        :DoublyLinkedListArray(50)
    {

    }
    explicit DoublyLinkedListArray(uint size):free(size)
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

    ~DoublyLinkedListArray()
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
#endif // DOUBLYLINKEDLISTARRAY_H
