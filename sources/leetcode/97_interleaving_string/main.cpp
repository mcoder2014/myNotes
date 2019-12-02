#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3)
    {
        if(s3.length() != s1.length() + s2.length())
            return false;
//        return helper(s1, s2, s3, 0, 0);

        int m = s1.length(), n = s2.length();
//        if(m == 0 || n == 0)
//            return helper(s1, s2, s3, 0, 0);
        vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
        dp[0][0] = 0;

        for(int i = 0; i <= m; i++)
        {
            for(int j = 0; j <= n; j++)
            {
                if(i==0 && j ==0)
                    dp[i][j] = true;
                else if( i == 0)
                    dp[i][j] =( dp[i][j-1] && s2[j-1] == s3[i+j-1]);
                else if( j == 0)
                    dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]);
                else
                    dp[i][j] = ( dp[i][j-1] && s2[j-1] == s3[i+j-1]) ||
                            (dp[i-1][j] && s1[i-1] == s3[i+j-1]);
            }
        }
        return dp[m][n];
    }

    bool helper(string& s1, string& s2, string& s3, int i, int j)
    {
        if(i == s1.length() && j == s2.length())
            return true;

        bool result = false;
        if(i < s1.length() && s3[i+j] == s1[i])
            result |= helper(s1, s2, s3,i+1,j);
        if(j < s2.length() && s3[i+j] == s2[j])
            result |= helper(s1, s2, s3, i,j+1);
        return result;
    }
};

int main()
{
    Solution solution;
    auto test = [&](string s1, string s2, string s3)
    {
        bool result = solution.isInterleave(s1, s2, s3);
        cout << s1 << "\t"
             << s2 << "\t"
             << s3 << "\t"
             << result << endl;
    };

    test("aabcc", "dbbca", "aadbbcbcac");
    test("aabcc", "dbbca", "aadbbbaccc");
    test("","cac", "cac");
    test("","","");
    test("db","b","cbb");
    test("cbcccbabbccbbcccbbbcabbbabcababbbbbbaccaccbabbaacbaabbbc",
         "abcbbcaababccacbaaaccbabaabbaaabcbababbcccbbabbbcbbb",
         "abcbcccbacbbbbccbcbcacacbbbbacabbbabbcacbcaabcbaaacbcbbbabbbaacacbbaaaabccbcbaabbbaaabbcccbcbabababbbcbbbcbb");
    return 0;
}
