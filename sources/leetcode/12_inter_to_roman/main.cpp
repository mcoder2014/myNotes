#include <iostream>
#include <string>
#include<unordered_map>
using namespace std;

class Solution {
public:
    string intToRoman(int num) {
        int digit=num%10;
        num = num/10;

        int ten=num%10;
        num = num/10;

        int hundred=num%10;
        num = num / 10;

        int throusand=num%10;

        string result;
        result += value(throusand, 'M','M','M');
        result += value(hundred, 'M', 'D', 'C');
        result += value(ten, 'C', 'L', 'X');
        result += value(digit, 'X', 'V', 'I');

        return result;
    }

    int romanToInt(string s) {
        unordered_map<char, int> Map = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
        };

        int size = s.size();
        int result = 0;
        for(int i = 0; i < size-1; i++)
        {
            if(Map[s[i]] < Map[s[i+1]])
                result = result - Map[s[i]];
            else
                result = result + Map[s[i]];
        }

        result = result + Map[s[size -1]];

        return result;
    }

    string value(int digit, char ten, char five, char one)
    {
        string s;
        if(digit == 0)
            return "";
        else if(digit <= 3)
        {
            for(int i=0;i<digit; i++)
                s.push_back(one);
        }
        else if(digit <= 8)
        {
            for (int i = digit; i <5; i++)
                s.push_back(one);
            s.push_back(five);
            for (int i=5;i<digit;i++)
                s.push_back(one);
        }
        else if (digit == 9)
        {
            s.push_back(one);
            s.push_back(ten);
        }
        return s;
    }
};

int main()
{
    Solution solution;

    auto test= [&](int input)
    {
        string output = solution.intToRoman(input);
        cout << input << "\t" << output
             << "\t" << solution.romanToInt(output) << endl;
    };

    test(3);
    test(4);
    test(5);
    test(6);
    test(9);
    test(58);
    test(1994);

    return 0;
}
