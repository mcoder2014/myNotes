#include <iostream>
#include <vector>

using namespace std;

int maxSub(vector<int>& nums)
{
    if(nums.size() == 0)
    {
        return 0;
    }
    vector<int> bitmap(100, 0);

    for(int item:nums)
    {
        bitmap[item] = 1;
    }

    int maxLen = 0;
    int tmpLen = 0;
    bool flag = false;

    for(int item:bitmap)
    {
        if(item == 1)
        {
            if(flag)
            {
                tmpLen++;
                maxLen = std::max(maxLen, tmpLen);
            }
            else
            {
                flag = true;
                tmpLen = 1;
            }
        }
        else
        {
            if(flag)
            {
                flag = false;
                tmpLen = 0;
            }
        }
    }

    return maxLen;
}


int main()
{
    vector<int> nums;
    int tmp;

    while(1)
    {
        nums.clear();
        while(cin >> tmp)
        {
            nums.push_back(tmp);
            if(cin.get() == '\n') 
            {
                break;
            }
        }

        int value = maxSub(nums);
        cout << "max sub: " << value << endl;
    }

    return 0;
}