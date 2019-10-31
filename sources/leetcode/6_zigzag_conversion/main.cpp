#include <iostream>
#include <string>
#include <vector>

using namespace std;

/***
 *
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:

string convert(string s, int numRows);
Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"
Example 2:

Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:

P     I    N
A   L S  I G
Y A   H R
P     I

 **/


class Solution {
public:
    string convert(string s, int numRows) {
        vector<vector<char>> list(numRows, vector<char>());
        string result = s;
        int wide = numRows;
        if(numRows > 2)
            wide = 2 * numRows - 2;
        int length = s.length();
        for (int i = 0; i < length; i++)
        {
            int id = i % wide;
            if(id < numRows)
                list[id].push_back(s[i]);
            else
            {
                list[numRows -2 -(id%numRows)].push_back(s[i]);
            }
        }

        int idx = 0;
        for (int i=0; i<numRows; i++)
        {

            for (char c:list[i])
            {
//                cout << c;
                result[idx] = c;
                ++idx;
            }
//            cout << endl;
        }
        return result;
    }
};



int main()
{
    Solution solution;
    string s = "PAYPALISHIRING";
    string res = solution.convert(s, 4);
    cout << res << endl;
    return 0;
}
