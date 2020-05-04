#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites)  {

        vector<int> de(numCourses,0);
        vector<unordered_set<int> > gra(numCourses);
        //make graph
        for(vector<int> &a:prerequisites)
        {
            gra[a[1]].insert(a[0]);
            de[a[1]]++;
        }
        
        for(int i=0;i<numCourses;++i)
        {
            int j=0;
            for(;j<numCourses;++j)
            {
                if(de[j]==0)    break;
            }
            if(j==numCourses)    return false;   
            de[j]=-1;   
            for(auto a:gra[j])
                de[a]--;    
        }
        return true;
    }
};

int main()
{
    return 0;
}