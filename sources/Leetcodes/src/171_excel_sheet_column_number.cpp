#include <string>

using namespace std;

class Solution {
public:
    int titleToNumber(string s) {
        int ALPHBAT = 26;
        int number = 0;
        for(char ch:s) {
            number *= ALPHBAT;
            number += ch-'A'+1;
        }
        return number;
    }
};

int main()
{
    return 0;
}