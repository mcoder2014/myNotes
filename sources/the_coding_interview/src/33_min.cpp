#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void unionMin(vector<int>& nums) {
    vector<string> stringNums;

    for(int& item:nums) {
        stringNums.push_back(std::to_string(item));
    }

    sort(stringNums.begin(), stringNums.end());

    for(string & item: stringNums) {
        cout << item;
    }
    cout << endl;
}

int main() {

    vector<int> nums;
    int tmp;

    cout << "input line of rotated vector, e.g. 11 23 5561 56 " << endl; 

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

        unionMin(nums);

    }

    return 0;
}