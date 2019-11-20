#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> combine(int n, int k)
    {
        vector<vector<int>> result;
        vector<int> num(n);
        vector<int> pos(k);

        for (int i = 0; i < n; i++)
            num[i] = i + 1;

        for(int i = 0;i <k;i++)
            pos[i] = i;

        while((pos[0] <= n-k))
        {
            // push
            vector<int> res;
            for (int i = 0; i < k; i++)
            {
                res.push_back(num[pos[i]]);
            }
            result.push_back(res);

            // move next
            int x = k-1;
            for (;x>=0;x--)
            {
                if(pos[x] < n-k+x)
                {
                    // not max_value
                    break;
                }
            }
            if(x <0 || !(pos[x] < n-k+x))
                break;
            pos[x]++;
            for(x++; x < k; x++)
                pos[x] = pos[x-1]+1;
        }
        return result;
    }
};

int main()
{
    Solution solution;
    auto test = [&](int n, int k)
    {
        vector<vector<int>> result = solution.combine(n, k);
        for (vector<int> line:result)
        {
            for(int item: line)
                cout << item << " ";
            cout << "\n";
        }
        cout << "\n";
    };

    test(5,3);
    test(4,2);
    test(4,3);
    test(5,1);

    return 0;
}
