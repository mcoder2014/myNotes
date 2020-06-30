#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> minK(vector<int>& nums, int k) 
{
    priority_queue<int> priorityQueue;

    for(int& item:nums) {
        if(priorityQueue.size() < k) {
            priorityQueue.push(item);
        } else {
            if(item < priorityQueue.top()) {
                priorityQueue.pop();
                priorityQueue.push(item);
            }
        }
    }

    vector<int> returnValue;
    while(!priorityQueue.empty()) {
        returnValue.push_back(priorityQueue.top());
        priorityQueue.pop();
    }

    return returnValue;
}

int main()
{

    vector<int> nums;
    int findValue;
    int tmp;

    cout << "input line of ordered vector, e.g.  1 2 3 4 5 6 7\n"
         << "a new line of the min K to find e.g. 4" << endl; 

    while(true) {
        
        nums.clear();
        while(cin >> tmp) {
            nums.push_back(tmp);
            if (cin.get() == '\n')
            {
                break;
            }
        }

        cin >> findValue;

        for(int value:nums) {
            cout << value << " ";
        }
        cout << endl;

        vector<int> minValues = minK(nums, findValue);
        
        for(int value:minValues) {
            cout << value << " ";
        }
        cout << endl;
    }


    return 0;
}