#include <iostream>
#include <vector>
#include <deque>
using namespace std;

class Solution
{
public:
    int evalRPN(vector<string> &tokens)
    {
        deque<int> stk_number;
        vector<string>::iterator iter;
        for (string token:tokens)
        {
            // 分辨 数字 or 符号
            if (token.size() == 1 && (token == "+" || token == "-" || token == "*" || token == "/"))
            {
                // 符号
                if (stk_number.size() < 2)
                {
                    // 补0
                    stk_number.push_front(0);
                }
                int num_right = *(stk_number.end() - 1);
                stk_number.pop_back();
                int num_left = *(stk_number.end() - 1);
                stk_number.pop_back();
                stk_number.push_back(cal(num_left, num_right, token));
            }
            else
            {
                // 数字
                stk_number.push_back(std::stoi(token));
            }
        }

        return *(stk_number.end() - 1);
    }
    int cal(int left, int right, string sign)
    {
        if (sign == "+")
            return left + right;
        else if (sign == "-")
            return left - right;
        else if (sign == "*")
            return left * right;
        else if (sign == "/")
            return left / right;
        return -1;
    }
};

int main(int argc, char **argv)
{

    return 0;
}