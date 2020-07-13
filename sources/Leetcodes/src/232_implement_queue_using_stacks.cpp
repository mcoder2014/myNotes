#include <iostream>
#include <stack>

using namespace std;

class MyQueue {
public:
    /** Initialize your data structure here. */
    MyQueue() {

    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        stackIn.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        checkStackOut();
        int value = stackOut.top();
        stackOut.pop();
        return value;
    }
    
    /** Get the front element. */
    int peek() {
        checkStackOut();
        return stackOut.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return stackIn.empty() && stackOut.empty();
    }

private:
    stack<int> stackIn;
    stack<int> stackOut;

    void checkStackOut() {
        if(stackOut.empty()) {
            int value;
            while(!stackIn.empty()) {
                value = stackIn.top();
                stackIn.pop();
                stackOut.push(value);
            }
        }
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

int main()
{
    MyQueue* obj = new MyQueue();
    obj->push(2);
    int param_2 = obj->pop();
    int param_3 = obj->peek();
    bool param_4 = obj->empty();
    return 0;
}