#include <iostream>
#include <climits>
using namespace std;

/*
Given a 32-bit signed integer, reverse digits of an integer.

Example 1:

Input: 123
Output: 321
Example 2:

Input: -123
Output: -321
Example 3:

Input: 120
Output: 21
*/


class Solution {
public:
    int reverse(int x) {

        long long result = 0;
        while(x != 0)
        {
            result = result*10 + x % 10;
            x /= 10;
        }
        return (result > INT_MAX || result < INT_MIN)? 0 : result;
    }
};


int main()
{
    Solution solution;

    int s = 123;
    int result = solution.reverse(s);
    cout << s << "\t" << result << endl;

    s = -123;
    result = solution.reverse(s);
    cout << s << "\t" << result << endl;

    s = 120;
    result = solution.reverse(s);
    cout << s << "\t" << result << endl;

    return 0;
}
