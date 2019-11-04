#include <iostream>
#include <string>
#include <stack>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {

        stack<int> stk;
        stk.push(-1);

        int maxL = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if(stk.top() != -1
                    && s[stk.top()] == '('
                    && s[i] == ')')
            {

                stk.pop();
                maxL = maxL > i-stk.top()? maxL:i-stk.top();

            }
            else
            {
                stk.push(i);
            }
        }

        return maxL;
    }
};


int main()
{

    return 0;
}
