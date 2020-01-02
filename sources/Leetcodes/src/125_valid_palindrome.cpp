#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool isPalindrome(string s) 
    {
        if(s.size() == 0)
            return true;
        int left = 0, right = s.size() -1;
        // transform(s.begin(), s.end(),s.begin(), std::tolower);
        for(char &ch:s)
        {
            ch = (char)tolower(ch);
        }

        while(left < right)
        {
            while(left < right && !(s[left] >= 'a' && s[left] <= 'z'))
                left ++;
            while(left < right && !(s[right] >= 'a' && s[right] <= 'z'))
                right --;
            
            if(s[left] == s[right])
            {
                left++;
                right--;
            }
            else
                return false;
        }   

        return true;
    }
};

int main()
{
    return 0;
}