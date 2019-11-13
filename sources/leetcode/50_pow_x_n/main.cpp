#include <iostream>

using namespace std;

class Solution {
public:
    double myPow(double x, int n)
    {
        int64_t nn;
        if(n==0)
            return 1;
        else if(n < 0)
        {
            x = 1/x;
            nn = -n;
        }
        else
        {
            nn = n;
        }

        double ans = 1;
        while(nn != 0)
        {
            if(nn%2 == 1)
                ans = ans * x;
            nn = nn/2;
            x *= x;
        }
        return ans;
    }
};

int main()
{
    Solution solution;
    auto test = [&](double x, int n)
    {
        double res = solution.myPow(x, n);
        cout << res << "\n";
    };

    test(2,10);
    test(2,-2);
    return 0;
}
