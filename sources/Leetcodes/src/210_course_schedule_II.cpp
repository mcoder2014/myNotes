#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> degree(numCourses, 0);
        vector<unordered_set<int>> graph(numCourses);
        for(vector<int> & preOrder: prerequisites) {
            degree[preOrder[0]] ++;
            graph[preOrder[1]].insert(preOrder[0]);
        }

        vector<int> order;
        for(int i = 0; i < numCourses; i++) {
            int j = 0;
            for(;j < numCourses; j++) {
                if(degree[j] == 0) {
                    // 入度为0
                    order.push_back(j);

                    degree[j] = -1;
                    for(int course:graph[j]) {
                        degree[course]--;
                    }
                }
            }
        }
        if(order.size() == numCourses) {
            return order;
        } else {
            return vector<int>();
        }
    }
};

int main()
{
    return 0;
}