#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve(vector<int>& nums)
{
    vector<pair<int, int>> ordered(nums.size());
    for(int i=0; i < nums.size(); i++) {
        ordered[i] = pair<int,int>(nums[i], i);
    }
    sort(ordered.begin(), ordered.end());

    vector<int> mid(nums.size());

    int first = ordered[nums.size()/2 - 1].first;
    int second = ordered[nums.size()/2].first;
    for(int i = 0; i < nums.size()/2; i++) {
        pair<int, int>& item = ordered[i];
        mid[item.second] = second;
    }
    for(int i = nums.size()/2; i < nums.size(); i++) {
        pair<int, int>& item = ordered[i];
        mid[item.second] = first;
    }

    for(int& item:mid){
        printf("%d\n", item);
    }

}

int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for(int i =0; i < n; i++) {
        cin >> nums[i];
    }

    solve(nums);

    return 0;
}