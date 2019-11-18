#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s)
    {
        string::iterator iter = s.end()-1;
        int length = 0;
        bool first_ch = false;
        while (iter >= s.begin())
        {
            if(!first_ch)
            {
                if(*iter != ' ')
                {
                    first_ch = true;
                    length++;
                }
            }
            else
            {
                if(*iter != ' ')
                    length++;
                else
                    break;
            }

            iter--;
        }
        return length;
    }
};

int main()
{

    return 0;
}
