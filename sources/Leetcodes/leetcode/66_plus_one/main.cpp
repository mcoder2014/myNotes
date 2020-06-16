#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits)
    {
        reverse(digits.begin(),digits.end());

        int plus = 1;
        int idx = 0;

        while(plus == 1 && idx <digits.size())
        {
            digits[idx] += plus;
            plus = digits[idx] / 10;
            digits[idx] = digits[idx] % 10;
            idx++;
        }
        if(plus == 1)
        {
            digits.push_back(plus);
        }
        reverse(digits.begin(), digits.end());
        return digits;
    }
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
