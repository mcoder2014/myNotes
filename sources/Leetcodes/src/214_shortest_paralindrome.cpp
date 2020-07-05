#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    string shortestPalindrome(string s)
    {
        string s_reverse(s), s_new;
        reverse(s_reverse.begin(), s_reverse.end());
        s_new = s + "#" + s_reverse;
        int i = -1, j = 0; //i指向前缀下标初始-1，j指向后缀下标初始0
        //next[j]表示j之前的字符串的最长前缀和后缀相等的字符个数，即最长前缀的下一个字符下标
        vector<int> next(s_new.size() + 1, 0);
        next[0] = -1;
        //循环扫描字符串s_new
        while (j < s_new.size())
        {
            if (i == -1 || s_new[i] == s_new[j])
            {
                i++;
                j++;
                next[j] = i;
            }
            else
                i = next[i];
        }
        //将s_new的s_reverse的与s非重复重复部分截取拼接上s就是最短回文串结果
        return s_new.substr(s.size() + 1, s.size() - next[s_new.size()]) + s;
    }
};

int main()
{
    return 0;
}