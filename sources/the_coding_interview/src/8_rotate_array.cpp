#include <iostream>
#include <vector>

using namespace std;

/**
 * 查找旋转数组的旋转位置
 */  
int findMin(vector<int> nums) {
    if(nums.size() == 0)
        return -1;

    int left = 0;
    int right = nums.size() -1;
    int mid = 0;

    while(left < right-1) {
        mid = (left + right) / 2;

        if(nums[left] <= nums[mid]) {
            left = mid;
        } else if(nums[right] >= nums[mid]){
            right = mid;
        }

    }

    return right;
}

int main() 
{
    vector<int> nums;
    int tmp;

    cout << "input line of rotated vector, e.g. 5 6 7 1 2 3 4 " << endl; 

    while(true) {
        
        nums.clear();
        while(cin >> tmp) {
            nums.push_back(tmp);
            if (cin.get() == '\n')
            {
                break;
            }
        }

        for(int value:nums) {
            cout << value << " ";
        }
        cout << endl;

        int index = findMin(nums);
        cout << index << endl;
    }

    return 0;
}