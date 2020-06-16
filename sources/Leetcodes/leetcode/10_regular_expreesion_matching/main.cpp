#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p)
    {
        //        return helper(s, p, 0, 0);
        //        vector<vector<int8_t>> dp_map(s.size(), vector<int8_t>(p.size(), -1));
        //        return helper(s, p, dp_map, 0, 0);
        return true;
    }

    /**
1.  P[i][j] = P[i - 1][j - 1],
    if p[j - 1] != '*' && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
2.  P[i][j] = P[i][j - 2],
    if p[j - 1] == '*' and the pattern repeats for 0 times;
3.  P[i][j] = P[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'),
    if p[j - 1] == '*' and the pattern repeats for at least 1 times.
    */
    bool bottom_up(string s, string p)
    {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;
        for (int i = 0; i <= m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (j > 1 && p[j - 1] == '*')
                {
                    dp[i][j] = dp[i][j - 2]
                            || (i > 0 && (s[i - 1] == p[j - 2] || p[j - 2] == '.') && dp[i - 1][j]);
                }
                else
                {
                    dp[i][j] = i > 0 && dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
                }
            }
        }
        return dp[m][n];
    }

    // 直接递归的方法相当于不是使用动态规划，更像是贪心算法
    /// https://leetcode.com/problems/regular-expression-matching/discuss/5937/My-4ms-C%2B%2B-DP-solution-(another-recursive-version-also-given-72ms)
    bool helper(const string &s, const string &p, int sS, int pS)
    {
        int sSize = s.size(), pSize = p.size(), i, j;
        if(pS==pSize) return sS ==sSize; // if p goes to its end, then only if s also goes to its end to return true;

        if(p[pS+1]!='*')
        {
            if( sS<sSize && (p[pS]==s[sS] || p[pS] == '.'))
                return helper(s, p, sS+1, pS+1);
        }
        else
        {
            if(helper(s, p, sS,pS+2))
                return true;

            while(sS<sSize && (p[pS]==s[sS] || p[pS] == '.'))
                if(helper(s,p, ++sS, pS+2))
                    return true;
        }
        return false;
    }

};


int main()
{
    Solution solution;

    string s = "aa";
    string p = "p";
    bool result = solution.isMatch(s, p);
    cout << "s:\t" << s << "\tp:\t" << p << "\t" << result<< endl;


    s = "aa";
    p = "aa";
    result = solution.isMatch(s, p);
    cout << "s:\t" << s << "\tp:\t" << p << "\t" << result<< endl;

    s = "aa";
    p = "a*";
    result = solution.isMatch(s, p);
    cout << "s:\t" << s << "\tp:\t" << p << "\t" << result<< endl;

    s = "aa";
    p = "a";
    result = solution.isMatch(s, p);
    cout << "s:\t" << s << "\tp:\t" << p << "\t" << result<< endl;

    s = "ab";
    p = ".*";
    result = solution.isMatch(s, p);
    cout << "s:\t" << s << "\tp:\t" << p << "\t" << result<< endl;

    s = "aab";
    p = "c*a*b";
    result = solution.isMatch(s, p);
    cout << "s:\t" << s << "\tp:\t" << p << "\t" << result<< endl;

    s = "mississippi";
    p = "mis*is*p*.";
    result = solution.isMatch(s, p);
    cout << "s:\t" << s << "\tp:\t" << p << "\t" << result<< endl;

    return 0;
}
