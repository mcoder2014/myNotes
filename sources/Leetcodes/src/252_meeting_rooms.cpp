#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// input [[0,30],[5,10],[15,20]]
// output false

class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {

        // 按照自然序排序
        sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b){
            return a[0] < b[0];
        });

        for(int i = 1; i < intervals.size(); i++) {
            if(intervals[i][0] < intervals[i-1][1]) {
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