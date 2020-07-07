#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        multiset<pair<int, int>> boundary;

        // 按大楼两侧的边界排序，通过负号区分左边界 右边界
        for(vector<int>& building: buildings) {
            boundary.insert(pair<int, int>(building[0], -building[2]));
            boundary.insert(pair<int, int>(building[1], building[2]));
        }

        vector<vector<int>> returnValue;
        // 维护一个高度二叉树，保持最高边界
        multiset<int> height{0};
        int m = 0;
        for(const pair<int, int>& wall:boundary) {
            if(wall.second < 0) {
                // 碰到大楼左边界，插入高度集合
                height.insert(-wall.second);
            } else {
                // 碰到大楼右边界，从高度集合中取出
                height.erase(height.find(wall.second));
            }

            // 如果高度发生变换，加入返回值
            if(m != *height.rbegin()) {
                returnValue.push_back({wall.first, *height.rbegin()});
                m = *height.rbegin();
            }
        }

        return returnValue;
    }
};

int main()
{
    return 0;
}