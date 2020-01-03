#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<string>> partition(string s) 
    {
        vector<vector<string>> result;
        vector<string> tmp;

        if(s.length() == 0)
            return result;
        if(s.length() == 1)
        {
            result.push_back(vector<string>(1, s));
            return result;
        }

        // 如果一开始就是回文数
        if(isPalindrome(s, 0, s.length()-1))
        {
            tmp.push_back(s.substr(0, s.length()));
            result.push_back(tmp);
            tmp.pop_back();
        }

        dfs(s, 0, result, tmp);
        return result;
    }

    void dfs(string& s, int start, 
        vector<vector<string>>& result, 
        vector<string>& tmp)
    {
        for(int i = start; i < s.length()-1; i++)
        {
            // 检查前半段是不是回文
            if(isPalindrome(s, start, i))
            {
                tmp.push_back(s.substr(start, i-start+1));
                // 检查后半段是否是回文
                if(isPalindrome(s, i+1, s.length()-1))
                {
                    // save result
                    tmp.push_back(s.substr(i+1, s.length()-i));
                    result.push_back(tmp);
                    tmp.pop_back();
                }
                
                {
                    // 对后半段再分割
                    dfs(s, i+1, result, tmp);
                }
                tmp.pop_back();
            }
        }
        

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
        vector<vector<string>> result = solution.partition(s);

        for(vector<string>& vec:result)
        {
            for(string& st:vec)
            {
                cout << st << " ";
            }
            cout << endl;
        }
    };

    test("aabbc");
    test("a");
    test("bbbb");
    test("ababababababababababababcbabababababababababababa");
    return 0;
}