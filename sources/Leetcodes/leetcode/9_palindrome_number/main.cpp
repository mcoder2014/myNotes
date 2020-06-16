#include <iostream>
#include <climits>
using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0)
            return false;

        int result = 0;
        int tmp = x;
        while (tmp > 0)
        {
            result = result * 10 + (tmp%10);
            tmp = tmp / 10;
        }
        return x == result;
    }
};

int main()
{
    Solution solution;
    int test = 10;
    bool result = solution.isPalindrome(test);
    cout << test << "\t" << result << endl;
    return 0;
}
