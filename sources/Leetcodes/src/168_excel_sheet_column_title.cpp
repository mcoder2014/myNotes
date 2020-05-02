#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;


class Solution {
public:
    string convertToTitle(int n) {
        // 1  ->  A
        // 26 ->  Z
        if(n==0)
            return "";

        string returnValue;
        int SEP = 26;
        int value = n;
        while(value != 0) {
            int tmp = (value-1) % SEP;
            returnValue.push_back('A' + (char)(tmp));
            value = (value-1) / SEP;
        }
        reverse(returnValue.begin(), returnValue.end());
        return returnValue;
    }
};

int main()
{
    Solution slu;

    cout << 260 << " " <<slu.convertToTitle(260) << endl;
    cout << 261 << " " <<slu.convertToTitle(261) << endl;
    return 0;
}