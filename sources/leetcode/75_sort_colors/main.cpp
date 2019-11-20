#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums)
    {
        vector<int> count(3,0);
        for(int item:nums)
            count[item]++;
        nums.clear();
        for (int i = 0; i < count.size();i++)
        {
            for(int j=0;j<count[i]; j++)
                nums.push_back(i);
        }
    }

};


int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
