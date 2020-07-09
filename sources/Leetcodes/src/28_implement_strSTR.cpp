#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        if(needle.size() > haystack.size())
            return -1;
        else if(needle.size() == 0 && haystack.size() == 0)
            return 0;

        int haystack_size = haystack.size() - needle.size();
        int needle_size = needle.size();
        for (int i = 0; i <= haystack_size; i++)
        {
            bool isBreak = false;
            for(int j = 0; j < needle_size; j++)
            {
                if(haystack[i+j] != needle[j])
                {
                    isBreak = true;
                    break;
                }
            }
            if(!isBreak)
                return i;
        }

        return -1;
    }
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
