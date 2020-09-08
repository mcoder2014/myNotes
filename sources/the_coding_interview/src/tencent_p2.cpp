#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool check_intersect(set<int> s_union, set<int> xx)
{
    for (int item : xx)
    {
        if (s_union.find(item) != s_union.end())
        {
            return true;
        }
    }
    return false;
}

int main()
{
    int n; //人数
    int m; //团队个数

    cin >> n >> m;
    vector<set<int>> team(m);
    int zero_num = -1;
    for (int i = 0; i < m; i++)
    {
        int a;
        cin >> a;
        while (cin >> a)
        {
            if (a == 0)
            {
                zero_num = i;
            }
            team[i].insert(a);
            if (cin.get() == '\n')
            {
                break;
            }
        }
    }

    //构造关系
    if (zero_num != -1)
    {
        set<int> v_union = team[zero_num];
        int count = v_union.size();
        int oldCount = 0;
        while (count != oldCount)
        {
            oldCount = count;
            for (int i = 0; i < team.size(); i++)
            {
                if (i != zero_num)
                {
                    if (check_intersect(v_union, team[i]))
                    {
                        for (int item : team[i])
                        {
                            v_union.insert(item);
                        }
                    }
                }
            }
            count = v_union.size();
        }

        std::cout << v_union.size() << std::endl;
    }
    else
    {
        std::cout << 1 << std::endl;
        return 0;
    }
    return 0;
}
