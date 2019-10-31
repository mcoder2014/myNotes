#include <iostream>
#include <string>
using namespace std;

/*****

Given a string s, find the longest palindromic substring in s.
You may assume that the maximum length of s is 1000.

Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example 2:

Input: "cbbd"
Output: "bb"

*/


class Solution {
public:
    ///
    /// \brief longestPalindrome
    /// \param s
    /// \return
    /// 200ms
    ///
    string longestPalindrome(string s) {
        int length = s.size();
        if(length <=1)
            return s;

        for(int max_len = s.size(); max_len > 0; --max_len)
        {
            int offset_size = length - max_len;
            for (int i = 0; i <= offset_size; i++)
            {
                if(check(s, i, i + max_len-1))
                {
                    return s.substr(i, max_len);
                }
            }
        }
        return "";
    }

    bool check(string &s, int start, int end)
    {
        while (start < end)
        {
            if(s[start] != s[end])
                return false;
            start ++;
            end --;
        }
        return true;
    }


    ///
    /// 假设每个位置的字符都可能是最长对称子串的中点，进行扩张
    /// 复杂度相比上面小得多 8ms
    ///
    string longestPalindrome2(string s) {
        int length = s.size();
        if(length <=1)
            return s;

        int maxlen = 1;
        int max_start = 0;

        for (int i =0; i <length; i++)
        {
            int left = i;
            int right = i;

            // 如果是偶数个，中间至少两个相等的
            while(right+1 < length && s[right +1] == s[left])
            {
                right ++;
                i++;        // 可以筛去一些情况
            }

            while(left-1 >= 0 && right+1 <length && s[left-1] == s[right+1])
            {
                --left;
                ++right;
            }

            // 记录最大值
            if(right - left + 1 > maxlen)
            {
                max_start = left;
                maxlen = right - left + 1;
            }
        }

        return s.substr(max_start, maxlen);
    }
};

int main()
{
    Solution solution;
    string s = "cc";
    string res = solution.longestPalindrome2(s);
    cout << res << endl;

    return 0;
}
