#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {

        unordered_map<char, int> indices;

        int left = 0;
        int max_length = 0;
        int length = s.length();
        for (int i = 0; i < length; i++)
        {
            if(indices.find(s[i]) != indices.end())
            {
                // 表中已存在
                // 记录长度
                max_length = max_length > (i-left) ? max_length : (i-left);

                // 更新为 left 为 indices[s[i]] + 1
                int next_left = indices[s[i]] + 1;

                // 将 left 到 indices[s[i]] 的indices 删除
                for(int j = left; j < next_left; j++)
                    indices.erase(s[j]);

                left = next_left;
                indices[s[i]] = i;
            }
            else
            {
                // 未存在
                indices[s[i]] = i;
            }
        }

        max_length = max_length >= length-left ? max_length : length-left;
        return max_length;
    }
};

int main()
{
//    cout << "Hello World!" << endl;
    Solution solution;
    string tets = "abcabcbb";
    int result = solution.lengthOfLongestSubstring(tets);
    cout << result << "\n";


    tets = "bbbbb";
    result = solution.lengthOfLongestSubstring(tets);
    cout << result << "\n";

    tets = "pwwkew";
    result = solution.lengthOfLongestSubstring(tets);
    cout << result << "\n";

    return 0;
}
