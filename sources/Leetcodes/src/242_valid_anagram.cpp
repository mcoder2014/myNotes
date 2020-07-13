#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.length() != t.length()) {
            return false;
        }

        vector<int> counts(26, 0);
        for(char ch:s) {
            counts[ch-'a']++;
        }
        for(char ch:t) {
            counts[ch-'a']--;
        }
        for(int item:counts) {
            if(item != 0) {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    return 0;
}