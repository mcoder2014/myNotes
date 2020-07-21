#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/**
 * 三指针法
 */
class Solution
{
public:
    int nthUglyNumber(int n)
    {
        vector<int> ugly(n, 1);
        vector<int> idx(3, 0);

        for (int i = 1; i < n; ++i)
        {

            int a = ugly[idx[0]] * 2;
            int b = ugly[idx[1]] * 3;
            int c = ugly[idx[2]] * 5;

            int next = std::min(a, std::min(b, c));

            if (next == a)
            {
                ++idx[0];
            }
            if (next == b)
            {
                ++idx[1];
            }
            if (next == c)
            {
                ++idx[2];
            }
            ugly[i] = next;
        }
        return ugly.back();
    }
};

int main()
{
    return 0;
}