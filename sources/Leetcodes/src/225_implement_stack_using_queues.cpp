#include <iostream>
#include <queue>

using namespace std;

class MyStack {
public:
    /** Initialize your data structure here. */
    MyStack() {

    }
    
    /** Push element x onto stack. */
    void push(int x) {
        if(queueA.empty()) {
            queueB.push(x);
        } else {
            queueA.push(x);
        }
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        if(queueA.empty()) {
            while(queueB.size() > 1) {
                queueA.push(queueB.front());
                queueB.pop();
            }
            if(queueB.size() == 1) {
                int value = queueB.front();
                queueB.pop();
                return value;
            } else
            {
                return -1;
            }
        } else {
            while(queueA.size() > 1) {
                queueB.push(queueA.front());
                queueA.pop();
            }
            if(queueA.size() == 1) {
                int value = queueA.front();
                queueA.pop();
                return value;
            } else
            {
                return -1;
            }
        }
    }
    
    /** Get the top element. */
    int top() {
if(queueA.empty()) {
        while(queueB.size() > 1) {
                queueA.push(queueB.front());
                queueB.pop();
            }
            if(queueB.size() == 1) {
                int value = queueB.front();
                queueB.pop();
                queueA.push(value);
                return value;
            } else
            {
                return -1;
            }
        } else {
            while(queueA.size() > 1) {
                queueB.push(queueA.front());
                queueA.pop();
            }
            if(queueA.size() == 1) {
                int value = queueA.front();
                queueA.pop();
                queueB.push(value);
                return value;
            } else
            {
                return -1;
            }
        }
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return queueA.empty() && queueB.empty();
    }

private:
    queue<int> queueA;
    queue<int> queueB;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

int main()
{
    MyStack* obj = new MyStack();
    obj->push(10);
    int param_2 = obj->pop();
    int param_3 = obj->top();
    bool param_4 = obj->empty();
    return 0;
}