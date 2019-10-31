#include <iostream>
#include <string>
#include <climits>
using namespace std;

class Solution {
public:
    int myAtoi(string str) {

        // 忽略前方的空格
        int idx = 0;
        int length = str.length();
        int sign = 1;
        long long result = 0;
        while(idx < length)
        {
            if(str[idx] != ' ')
                break;

            idx++;
        }

        // 空格后不是数字返回 0
        // 可能是正数可能是负数
        if(str[idx] == '-')
        {
            sign = -1;
            idx++;
        }
        else if (str[idx] == '+')
        {
            // 钓鱼执法呀，题目里没提这个选项
            sign = 1;
            idx++;
        }
        else if ((str[idx] >= '0' && str[idx] <= '9'))
        {
            result = str[idx] - '0';
            idx++;
        }
        else
        {
            return 0;
        }
        // 空格后不是数字返回 0
        // 可能是正数可能是负数
        // 遇到第一个不是数字的结尾便停止
        // 溢出返回 INT_MAX or INT_MIN

        while(idx < length)
        {
            if(!(str[idx] >= '0' && str[idx] <= '9'))
                break;

            result = result * 10 + str[idx] - '0';

            if(result > INT_MAX && sign > 0)
                // overflow
                    return INT_MAX;
            else if(result > (long long)INT_MAX+1 && sign < 0)
                return INT_MIN;

            idx++;
        }
        return result * sign;
    }
};

int main()
{
    Solution solution;
    string input = "42";
    int result = solution.myAtoi(input);
    cout << input << "\t" << result << "\n";


    input = "   -42";
    result = solution.myAtoi(input);
    cout << input << "\t" << result << "\n";

    input = "4193 with words";
    result = solution.myAtoi(input);
    cout << input << "\t" << result << "\n";


    input = "words and 987";
    result = solution.myAtoi(input);
    cout << input << "\t" << result << "\n";


    input = "91283472332";
    result = solution.myAtoi(input);
    cout << input << "\t" << result << "\n";

    input = "-2147483647";
    result = solution.myAtoi(input);
    cout << input << "\t" << result << "\n";


    return 0;
}
