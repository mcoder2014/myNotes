#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {

        if(s.size() == 0)
            return vector<int>();

        // 生成所有可能情况，对每种情况测试
        vector<vector<bool>> test(words.size(), vector<bool>(s.length(), false));
        for(int idx = 0; idx < words.size(); idx++)
        {
            for (int i = 0; i <= s.size() - words[idx].size(); i++)
            {
                bool finished = true;
                // 判断每一位置的true or fasle
                for(int ch = 0; ch < words[idx].size(); ch++)
                {
                    if(s[i+ch] != words[idx][ch])
                    {
                        finished = false;
                        break;
                    }
                }
                if(finished)
                    test[idx][i] = true;
            }
        }

        // 生成组合方案

        // 根据组合方案查询表格


    }


    vector<int> findSubstring2(string s, vector<string>& words)
    {
        if(s.size() ==0 || words.size() == 0)
            return vector<int>();

        unordered_map<string, int> counts;
        for (string &word:words)
        {
            counts[word] ++;
        }

        int len_s = s.size();
        int num_words = words.size();
        int len_word = words[0].size();
        int range = len_s - num_words * len_word;
        vector<int> result;

        for (int i = 0; i <= range; i++)
        {
            int j=0;
            unordered_map<string, int> seen;
            for (;j<num_words; j++)
            {
                string word = s.substr(i + j * len_word, len_word);
                if(counts.find(word) == counts.end())
                    break;
                else
                {
                    seen[word]++;
                    if(seen[word] > counts[word])
                        break;
                }
            }
            if(j == num_words)
                result.push_back(i);
        }

        return result;
    }

};


int main()
{
    Solution solution;

    return 0;
}
