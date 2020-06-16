#include <iostream>
#include <vector>
#include <limits>
#include <time.h>
using namespace std;

// 直接递归的方法
int cut_rod(std::vector<int>& value, int length)
{
    if(length == 0)
        return 0;

    int q = numeric_limits<int>::min();
    for (int i = 1; i <= value.size() && i <= length; i++)
    {
        int val = value[i-1] +cut_rod(value, length-i);
        if(val > q)
            q = val;
    }
    return q;
}

// 带备忘的递归
int memoized_cut_rod(std::vector<int>& value, int length, std::vector<int>& note)
{
    if(note[length] >= 0)
        return note[length];

    int q = numeric_limits<int>::min();
    if(length == 0)
         q = 0;
    else
    {
        for (int i = 1; i <= value.size() && i <= length; i++)
        {
            int val = value[i-1] +memoized_cut_rod(value, length-i, note);
            if(val > q)
                q = val;
        }
    }
    note[length] = q;
    return q;
}

// 自底向上的方法
int bottom_up_cut_rod(std::vector<int> &value, int length, std::vector<int>& solution)
{
    std::vector<int> note(length+1, numeric_limits<int>::min());
//    std::vector<int> sloution(length+1, numeric_limits<int>::min());
    note[0] = 0;
    for (int j = 1; j <= length; j++)
    {
        int q = numeric_limits<int>::min();
        for (int i = 1; i <= j && i <= value.size(); i++)
        {
            if(q < value[i-1] + note[j-i])
            {
                q = value[i-1] + note [j-i];
                solution[j] = i;
            }
        }
        note[j] = q;
    }

    return note[length];
}

int main()
{

    std::vector<int> valve_meter({1,5,8,9,10,17,17,20,24,30});

    for (int i = 1; i <= valve_meter.size(); i++)
        cout << i << "\t";
    cout << endl;

    for(int item: valve_meter)
        cout << item << "\t";
    cout << endl;

    int CUT_LENGTH = 7;

    // 递归法
//    {
//        clock_t time_start = clock();
//        int result = cut_rod(valve_meter, CUT_LENGTH);
//        cout << "Top_down:\t" << result << endl;
//        clock_t time_end = clock();
//        cout << "Cost time:\t" << (time_end- time_start)/CLOCKS_PER_SEC << endl;
//    }

    // 带备忘录递归法
    {
        clock_t time_start = clock();
        std::vector<int> note(CUT_LENGTH+1, numeric_limits<int>::min());
        int result = memoized_cut_rod(valve_meter, CUT_LENGTH, note);
        cout << "Top_down:\t" << result << endl;
        clock_t time_end = clock();
        cout << "Cost time:\t" << (time_end- time_start)/CLOCKS_PER_SEC << endl;
    }

    // 自底向上的迭代方法
    {
        std::vector<int> solution(CUT_LENGTH+1, numeric_limits<int>::min());
        clock_t time_start = clock();

        int result = bottom_up_cut_rod(valve_meter, CUT_LENGTH, solution);
        cout << "Top_down:\t" << result << endl;
        clock_t time_end = clock();

        int n = CUT_LENGTH;
        while(n > 0)
        {
            cout << solution[n] << "\t";
            n -= solution[n];
        }
        cout << endl;
        cout << "Cost time:\t" << (time_end- time_start)/CLOCKS_PER_SEC << endl;
    }

    return 0;
}
