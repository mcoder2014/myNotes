#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int quickSort(vector<int> &numList, int left, int right)
    {
        //对left到right的这个区间进行排序
        int i = left;
        int j = right;
        int tmp = numList[left];
        while (i < j) //当i>=j时，排序完成
        {
            while (i < j && tmp >= numList[j]) //注意与前面不一样
            {
                j--;
            }
            if (i < j)
            {
                numList[i++] = numList[j];
            }
            while (i < j && tmp < numList[i]) //注意与前面不同
            {
                i++;
            }
            if (i < j)
            {
                numList[j--] = numList[i];
            }
        }
        numList[i] = tmp;
        return i; //返回基准数下标
    }

    int findKthLargest(vector<int>& nums, int k)
    {
        // write your code here
        if (nums.size() == 0)
            return 0;
        int left = 0;
        int right = nums.size() - 1;
        while (1)
        {
            int pos = quickSort(nums, left, right);
            if (pos == k - 1) //若找到的基准数下标为k-1，即为结果
            {
                return nums[k - 1];
            }
            if (pos > k - 1) //若找到的基准数下标比k-1大，则从其左区间中继续寻找，丢弃其右区间
            {
                right = pos - 1;
            }
            if (pos < k - 1) //若找到的基准数下标比k-1小，则从其右区间中继续寻找，丢弃其左区间
            {
                left = pos + 1;
            }
        }
    }
};

int main()
{
    int k, tmp;
    vector<int> nums;

    Solution solu;

    while (cin >> k)
    {
        nums.clear();
        while (cin >> tmp)
        {
            nums.push_back(tmp);

            if (cin.get() == '\n')
            {
                break;
            }
        }

        int value = solu.findKthLargest(nums, k);
        cout << "value " << value << endl;
    }

    return 0;
}