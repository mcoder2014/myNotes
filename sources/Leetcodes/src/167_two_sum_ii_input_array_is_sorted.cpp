#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0;
        int right = numbers.size() - 1;
        vector<int> result;
        if(numbers.size() <= 1)
            return result;
        while(left +1 < right) {
            if(numbers[left] + numbers[right] > target) {
                right--;
            } else if(numbers[left] + numbers[right] < target) {
                left++;
            } else {
                break;
            }
        }
        if(numbers[left] + numbers[right] == target) {
            result.push_back(left + 1);
            result.push_back(right + 1);
        }
        return result;
    }
};


int main()
{
    return 0;
}