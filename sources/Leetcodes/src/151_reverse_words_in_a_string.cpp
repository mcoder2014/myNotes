#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        if(s.size() == 0)
            return s;

        string returnValue;
        bool nWord = true;
        string buffer;

        for(string::iterator iter = s.begin(); iter != s.end(); iter++)
        {
            char ch = *iter;
            if(ch == ' ')
            {
                nWord = true;
            }
            else
            {
                if(nWord && buffer.size() != 0)
                {
                    if(returnValue.size() == 0)
                        returnValue = buffer;
                    else
                        returnValue = buffer + " " + returnValue;
                    
                    buffer.clear();
                    buffer.push_back(ch);
                    nWord = false;
                }
                else
                {
                    buffer.push_back(ch);
                    nWord = false;
                }
            }
        }

        if(buffer.size() != 0)
        {
            if(returnValue.size() == 0)
                returnValue = buffer;
            else
                returnValue = buffer + " " + returnValue;
        }

        return returnValue;
    }
};

int main()
{
    return 0;
}