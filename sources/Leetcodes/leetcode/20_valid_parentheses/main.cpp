#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> chs;
        unordered_map<char,char> map{{'}','{'}, {']','['},{')','('}};

        for(char ch:s)
        {
            if(ch == ')' || ch ==']' || ch=='}')
            {
                if(chs.size() == 0)
                    return false;
                char pair = chs.top();
                chs.pop();
                if(map[ch] != pair)
                    return  false;
            }
            else
            {
                chs.push(ch);
            }
        }
        if(chs.size()==0)
            return true;
        else
            return false;
    }

};

int main()
{

    return 0;
}
