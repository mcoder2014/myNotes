#include <iostream>
#include <exception>

using namespace std;

#ifndef STACK_H
#define STACK_H

template <class T>
class MyStack
{
public:
    MyStack(size_t capacity = 100):capacity(capacity+1), begin(0), end(0)
    {
        data = new int[capacity];
    }

    ~MyStack() 
    {
        delete data;
        data = nullptr;
    }

    /**
     * push()
     * 塞入一个元素，如果栈已经满了，会覆盖最早入栈的元素
     * @param value T
     */
    void push(const T& value) 
    {
        // 判断是否已满, 已满则抛弃最早元素
        if(begin == (end+1)%capacity) 
        {
            begin = (begin + 1) % capacity;
        }
        
        end = (end + 1) % capacity;
        data[end] = value;
    }

    /**
     * pop()
     * 出栈一个元素
     * stack 为空时，会有问题
     * @return T 
     */
    T pop() 
    {
        // 判断是否为空
        if(begin== end) 
        {
            // TODO: throw exception
            throw exception();
        }

        T value = data[end];
        end = (end + capacity - 1) % capacity;
        return value;
    }

    /**
     * size（）
     * 返回元素个数
     * @return size_t
     */  
    size_t size()
    {
        return (end - begin + capacity) % capacity;
    }

private:
    T* data;
    size_t capacity;
    size_t begin;
    size_t end;
};

#endif

template<class T>
void pushAndPrint(MyStack<T>& mystack, T value) 
{
    mystack.push(value);
    cout << "push: " << value << "\tsize: " << mystack.size() << endl;
}

template<class T>
void popAndPrint(MyStack<T>& mystack)
{
    T pop = mystack.pop();
    cout << "pop: " << pop << "\tsize: " << mystack.size() << endl;
}

void test()
{
    MyStack<int> myStack(9);

    // 塞入五个元素
    for(int i = 0; i < 5; i++) 
    {
        pushAndPrint(myStack, i);
    }

    // 弹出全部元素
    while(myStack.size() > 0)
    {
        popAndPrint(myStack);
    }

    // 压入一百个元素
    for(int i = 0; i < 100; i++)
    {
        pushAndPrint(myStack, i);
    }

    // 弹出全部元素
    while(myStack.size() > 0)
    {
        popAndPrint(myStack);
    }
}

int main()
{
    test();
    return 0;
}