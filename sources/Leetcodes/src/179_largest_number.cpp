#include <iostream>
#include <vector>

using namespace std;



/**
 * 9尽可能靠前
 * 可能会溢出
 */ 
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> strNum;
        for(int num:nums) {
            strNum.push_back(std::to_string(num));
        }
        sort(strNum.begin(), strNum.end(), &Solution::comp);
        string stringBuilder;

        bool fliterZero = true;
        for(string &item:strNum) {
            if(fliterZero) {
                if(item == "0") {
                    continue;
                }
            }
            fliterZero = false;
            stringBuilder = stringBuilder + item;
        }
        if(stringBuilder.size() == 0)
            stringBuilder = "0";
        return stringBuilder;
    }

    static bool comp(string& num1, string& num2) {
        string app1 = num1 + num2;
        string app2 = num2 + num1;
        return app1 > app2;
    }
};

int main()
{
    Solution slo;
    auto test = [&](vector<int> nums) {
        string result = slo.largestNumber(nums);
        cout << result << endl;
    };

    test({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0});

    return 0;
}