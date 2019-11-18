#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isNumber(string s)
    {
        int idx = 0, len = s.size();
        int sign = 1;
        // 过滤空格
        for (;idx < len; idx++) {
            if(s[idx] != ' ')
                break;
        }

        // sign
        if(s[idx] == '-')
        {
            sign = -1;
            idx++;
        }
        else if (s[idx] == '+')
        {
            sign = 1;
            idx++;
        }
        else if (!(s[idx] >= '0' && s[idx] <= '9'))
        {
            return false;
        }

        // 前面的实数
        unordered_map<char, int> chmp;
        for( ; idx < len; idx++)
        {
            if((s[idx] >= '0' && s[idx] <= '9'))
                continue;
            else if(s[idx] == '.' )
            {
                chmp[s[idx]]++;
                if(chmp[s[idx]] >1)
                    return false;
            }
            else if(s[idx] == 'e')
            {
                chmp[s[idx]]++;
                if(chmp[s[idx]] >1)
                    return false;
                if(idx +1 == len)
                    return false;
                if((s[idx+1]=='-'||s[idx+1]=='+') && idx+2 < len)
                    idx+=1;
                else
                    return false;
            }
            else if(s[idx]==' ')
            {
                break;
            }
            else {
                return false;
            }
        }

        // 过滤末尾的空格
        if(idx < len)
        {
            for(;idx<len; idx++)
                if(s[idx] != ' ')
                    return false;
        }

        return  true;

    }
};

int main()
{
    Solution solution;
    cout << "String\tsolve result\treal result\n";
    auto test = [&](string s,bool real)
    {
        bool res = solution.isNumber(s);
        cout << s << "\t" << res << "\t" << real << endl;
    };
    test("0", true);
    test(" 0.1", true);
    test("abc", false);
    test("1 a", false);
    test("2e10",true);
    test(" -90e3  ",true);
    test(" 1e", false);
    test("e3",false);
    test("6e-1",true);
    test("99e2.5", false);
    test("53.5e93",true);
    test(" --6",false);
    test("-+3",false);
    test("99a54e52",false);

    return 0;
}
