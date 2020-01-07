#include <stdio.h>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

class Solution {
public:

/// 双指针法可以解决
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) 
    {
        int size = gas.size();
        if(size == 0)
            return -1;
        if(size == 1)
            return (gas[0] >= cost[0])? 0:-1;
        
        int start = 0, end = 1;
        int total_gas = gas[start] - cost[start];
        while(start != end)
        {
            if(total_gas >= 0)
            {
                total_gas += gas[end] - cost[end];
                end = (end + 1) % size; 
            }
            else
            {
                start --;
                if(start < 0) start = start + size; 
                start = start% size;
                total_gas += gas[start] - cost[start];
            }
        }
        if(total_gas >= 0)
            return start;
        else 
            return -1;
    }
    
};

int main()
{
    Solution solution;
    auto test = [&](vector<int> gas, vector<int> cost)
    {
        int result = solution.canCompleteCircuit(gas, cost);
        printf("%d\n", result);
    };

    test({1,2,3,4,5},{3,4,5,1,2});
    test({1},{3});
    test({3},{5});

    return 0;
}