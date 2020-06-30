#include <iostream>
#include <vector>

using namespace std;

int binarySearch(vector<int>& nums, int value) {
    if(nums.size() == 0)
        return -1;

    int left = 0;
    int right = nums.size()-1;

    int mid = 0;

    while(left < right) {
        mid = (left + right) / 2;
        if(nums[mid] == value) {
            return mid;
        } else if(nums[mid] > value) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return (nums[left] == value) ? left : -1;
}

int main() 
{
    vector<int> nums;
    int findValue;
    int tmp;

    cout << "input line of ordered vector, e.g.  1 2 3 4 5 6 7\n"
         << "a new line of the value want to find e.g. 4" << endl; 

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

        int index = binarySearch(nums, findValue);
        cout << index << endl;
    }

    return 0;
}