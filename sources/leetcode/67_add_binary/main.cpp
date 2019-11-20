#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    string addBinary(string a, string b)
    {
        string longer = a.size()>=b.size() ?a:b;
        string shorter = a.size()>=b.size() ?b:a;

        reverse(longer.begin(), longer.end());
        reverse(shorter.begin(), shorter.end());
        for (int i =0; i <shorter.length();i++)
        {
            longer[i] += shorter[i]-'0';
        }



        char plus = 0;
        int idx = 0;
        int length = longer.size();
        while(idx < length)
        {
            longer[idx] += plus;
            plus = (longer[idx]-'0')/2;
            longer[idx] = (longer[idx]-'0')%2 + '0';
            idx++;
        }
        while (plus > 0)
        {
            longer.push_back(plus%2+'0');
            plus = plus/2;
        }

        reverse(longer.begin(),longer.end());

        return longer;
    }
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
