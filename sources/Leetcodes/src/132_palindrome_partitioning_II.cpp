#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/// 找出最优的结果 使用动态规划方法


class Solution {
public:
    int minCut(string s) 
    {
        if(s.size() == 0)
            return 0;

        vector<int> dp(s.length() + 1, 0);
        
        for(int i = 1; i < s.length(); i++)
        {
            int minS = INT32_MAX;
            for(int j = i; j >0; j--)
            {
                if(isPalindrome(s, j, i))
                {
                    int temp = dp[j] + 1;
                    minS = min(minS, temp);
                }
            }
            if(isPalindrome(s, 0, i))
                minS = 0;

            dp[i+1] = minS;
        }
        return dp[s.length()];
    }



    bool isPalindrome(string& s, int start, int end)
    {
        while(start < end)
        {
            if(s[start] != s[end])
                return false;
            start++;
            end--;
        }   
        return true;
    }
};







int main()
{
    Solution solution;
    auto test = [&](string s)
    {
        int minc = solution.minCut(s);
        cout << s << "\t" << minc << endl;
    };

    test("");
    test("s");
    test("sas");
    test("aab");
    test("aabcc");
    test("ababababababababababababcbabababababababababababa");

    return 0;
}