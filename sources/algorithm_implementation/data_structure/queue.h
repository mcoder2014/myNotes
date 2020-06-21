#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

namespace Mcoder
{

template<typename basetype>
class Queue
{
  public:
    uint head;
    uint tail;

    basetype *data;
    uint size;

    Queue();
     explicit Queue(uint size);
    ~Queue();

    void enqueue(basetype value);
    basetype dequeue();
    bool empty();
    bool full();
};


template<typename basetype>
Queue<basetype>::Queue():Queue<basetype>(50)
{

}

template<typename basetype>
Queue<basetype>::Queue(uint size)
{
    this->size = size;
    this->data = new basetype[size];
    this->tail = 0;
    this->head = 0;
}

template<typename basetype>
Queue<basetype>::~Queue()
{
    if(data != nullptr)
        delete [] data;
}

template<typename basetype>
void Queue<basetype>::enqueue(basetype value)
{
    if(full())
    {
        std::cout << "overflow" << std::endl;
        return;
    }

    data[tail] = value;
    if(tail == size -1)
        tail = 0;
    else {
        tail++;
    }

}

template<typename basetype>
basetype Queue<basetype>::dequeue()
{
    if(empty())
    {
        std::cout << "underflow" << std::endl;
        return basetype(-1);
    }

    basetype x = data[head];
    if(head == size - 1)
        head = 0;
    else
        head ++;
    return x;
}

template<typename basetype>
bool Queue<basetype>::empty()
{
    return head == tail;
}

template<typename basetype>
bool Queue<basetype>::full()
{
    return head == (tail +1)%size;
}

};

#endif // QUEUE_H
