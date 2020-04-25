#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        if(minOfData.size() > 0 && x > minOfData.top())
        {
            minOfData.push(minOfData.top());
        }
        else
        {
            minOfData.push(x);
        }
        data.push(x);
    }
    
    void pop() {
        data.pop();
        minOfData.pop();
    }
    
    int top() {
        return data.top();
    }
    
    int getMin() {
        return minOfData.top();
    }

private:
    stack<int> data;
    stack<int> minOfData;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

int main()
{
    return 0;
}