#ifndef STACK_H
#define STACK_H

#include <iostream>

// Test Stack
namespace Mcoder
{

template <typename basetype>
class Stack
{

public:
    basetype *data;
    uint top;
    uint size;
    Stack();
    Stack(uint stack_size);
    ~Stack();
    bool empty();
    void push(basetype value);
    basetype pop();
};

template<typename basetype>

Stack<basetype>::Stack()
    :Stack<basetype>(50)
{}

template<typename basetype>
Stack<basetype>::Stack(uint stack_size)
{
    top = -1;
    data = new basetype[stack_size];
    size = stack_size;
}

template<typename basetype>
Stack<basetype>::~Stack()
{
    delete [] data;
}

template<typename basetype>
bool Stack<basetype>::empty()
{
    if(top == -1)
        return true;
    else
        return false;
}

template<typename basetype>
void Stack<basetype>::push(basetype value)
{
    top ++;
    data[top] = value;
}

template<typename basetype>
basetype Stack<basetype>::pop()
{
    if(empty())
    {
        std::cout << "underflow" << std::endl;
        return data[0];
    }
    else
    {
        top--;
        return data[top + 1];
    }
}

};

#endif // STACK_H
