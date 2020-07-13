#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    vector<int> diffWaysToCompute(string input)
    {
        vector<int> res;
        for (int i = 0; i < input.size(); ++i)
        {
            char c = input[i];
            if (c == '+' || c == '-' || c == '*')
            { //递归划分
                auto res1 = diffWaysToCompute(input.substr(0, i));
                auto res2 = diffWaysToCompute(input.substr(i + 1));
                
                for (auto r1 : res1)
                { //计算结果
                    for (auto r2 : res2)
                    {
                        if (c == '+')
                        {
                            res.push_back(r1 + r2);
                        }
                        else if (c == '-')
                        {
                            res.push_back(r1 - r2);
                        }
                        else if (c == '*')
                        {
                            res.push_back(r1 * r2);
                        }
                    }
                }
            }
        }
        if (res.empty())
        { //纯数字，input中没符号
            res.push_back(stoi(input));
        }
        return res;
    }
};

int main()
{
    return 0;
}