#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    string multiply(string num1, string num2)
    {
        int len1 = num1.size(), len2= num2.length();
        if(len1 == 0 || len2==0)
            return "0";


        vector<int> n1(len1),n2(len2);
        vector<int> result(len1+len2, -1);

        for(int i = 0; i < len1; i++)
            n1[len1-i-1] = num1[i]-'0';
        for(int i = 0; i < len2; i++)
            n2[len2-i-1] = num2[i]-'0';

        for (int i = 0; i < len1; i++)
        {
            for (int j=0;j < len2; j++)
            {
                int tmp = n1[i]*n2[j];
                if(result[j+i] == -1)
                    result[i+j] = tmp;
                else
                    result[i+j] += tmp;
            }
        }

        int len_res = len1 + len2;
        int plus = 0;
        for(int i = 0; i < len_res; i++)
        {
            if(result[i] == -1 )
            {
                if(plus != 0)
                {
                    result[i] = plus;
                    plus = 0;
                }
                else
                {
                    len_res = i;
                    break;
                }
            }
            result[i] += plus;
            plus = result[i]/10;
            result[i] = result[i]%10;
        }

        string res = "";
        int i=len_res-1;
        while(i > 0 &&result[i] == 0)
            i--;
        for (;i>=0;i--)
        {
            res += char('0' + result[i]);
        }
        return res;
    }
};

int main()
{
    Solution solution;
    auto test = [&](string num1, string num2)
    {
        string result = solution.multiply(num1, num2);
        cout << result << endl;
    };

    test("123","456");
    test("9133","0");
    return 0;
}
