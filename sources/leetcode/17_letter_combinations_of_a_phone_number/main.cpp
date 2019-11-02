#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<string> letterCombinations(string digits) {

        if(digits.length() == 0)
            return vector<string>();

        unordered_map<char, string> Table
        {
          {'2',"abc"},
            {'3',"def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"}
        };

        int result_size = 1;
        for(char c: digits)
        {
            if(c == '1')
                continue;
            result_size = result_size * Table[c].length();
        }

        vector<string> result(result_size, "");

        int round = 1;
        int delta = result_size;
        for(int i=0; i <digits.size(); i++)
        {
            if(digits[i] == '1')
                continue;
            // Each digit
            int ch_possible = Table[digits[i]].length();
            int last_delta = delta;
            delta = delta / ch_possible;

            for(int j = 0; j < round; j++)
            {
                // round Part
                for(int ch =0; ch < ch_possible; ch++)
                {
                    for (int k = 0; k < delta; k++)
                    {
                        result[j * last_delta + ch * delta + k].push_back(
                                    Table[digits[i]][ch]);
                    }
                }
            }
            round = round * ch_possible;
        }

        return result;
    }
};


int main()
{
    Solution solution;

    auto test = [&](string digits)
    {
        vector<string> result = solution.letterCombinations(digits);
        cout << "[" ;
        for (int i=0; i < result.size()-1; i++)
        {
            cout << "\"" << result[i] << "\",";
        }

        cout << "\"" << result[result.size()-1] <<"\"]\n";
    };

    test("23");
    test("265");
    test("123");
    return 0;
}
