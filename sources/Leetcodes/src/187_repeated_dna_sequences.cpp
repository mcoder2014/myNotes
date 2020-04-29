#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_map<string, int> counter;
        vector<string> result;
        int i = 0;
        for(; i+10 < s.size(); i++) {
            counter[s.substr(i, 10)] ++;
        }

        for(pair<string, int> item:counter) {
            if(item.second >= 2) {
                result.push_back(item.first);
            }
        }
        return result;
    }
};

int main()
{
    return 0;
}