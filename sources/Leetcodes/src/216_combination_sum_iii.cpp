#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<vector<int>>res;
    
    vector<int> path;

    vector<vector<int>> combinationSum3(int k, int n) {
        if(k==0||n==0) return res;
        vector<int> num;
        for(int i=1;i<10;i++){
            num.push_back(i);
        }
        DFS(num,n,k,0);
        return res;
    }

    void DFS(vector<int>& num,int n,int k,int start){
        if(path.size()==k && n==0){
            res.push_back(path);
            return;
        }

        if(n<0||path.size()>k) 
            return;

        for(int i=start;i<9&&n-num[i]>=0;i++){
            path.push_back(num[i]);
            DFS(num,n-num[i],k,i+1);
            path.pop_back();
        }
    }
};

int main()
{
    return 0;
}