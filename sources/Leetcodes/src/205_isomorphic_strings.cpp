#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, char> s2t;
        unordered_map<char, char> t2s;

        int length = s.size();

        for(int i = 0; i < length; i++){
            if((s2t.find(s[i]) != s2t.end() && s2t[s[i]] != t[i])
                || (t2s.find(t[i]) != t2s.end() && t2s[t[i]] != s[i])) {
                    return false;
            } else {
                // 添加
                s2t[s[i]] = t[i];
                t2s[t[i]] = s[i];
            }
        }

        return true;
    }
};

int main()
{
    return 0;
}