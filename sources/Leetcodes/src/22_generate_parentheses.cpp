#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> result;
    vector<string> generateParenthesis(int n)
    {
        // 所有可能的组合情况
        result.clear();
        helper("", n, n);
        return result;
    }

    void helper(string s, int left ,int right)
    {
        if(left >0)
        {
            helper(s+'(', left - 1, right);
        }
        if(left < right)
            helper(s + ')', left, right-1);
        if(left == 0 && right ==0)
            result.push_back(s);
    }

};


int main()
{
    Solution solution;

    auto test = [&](int n)
    {
        vector<string> result = solution.generateParenthesis(n);
        cout << "test " << n << endl;
        for(string line:result)
            cout << line << endl;
        cout <<endl;
    };

    test(2);
    test(1);
    test(0);
    test(3);


    return 0;
}
