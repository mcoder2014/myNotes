#include <iostream>
#include <vector>

using namespace std;

/*
熟悉的A+B
时间限制： 1000MS
内存限制： 65536KB
题目描述：
A+B问题又来了。

设a，b，c是0到9之间的整数（其中a，b，c互不相同），其中abc和acc是两个不同的三位数，现给定一正整数n，问有多少对abc和acc能满足abc+acc=n（a≠0）？



输入描述
一个正整数n（100<n<2000）。

输出描述
第一行输出有多少对满足要求的数字。

接下来每一行输出一对abc和acc，以空格分隔。如果没有一对abc和acc的话，则直接输出0即可。如果有多对，请按照abc升序的次序输出。


样例输入
1068
样例输出
1
524 544
*/
vector<pair<int,int>> store;

bool fit(int a, int b, int c, int n)
{
    if(a == b || a == c || b == c)
    {
        return false;
    }

    int abc = 100 * a + 10 * b + c;
    int acc = 100 * a + 10 * c + c;
    if(abc + acc == n) {
        store.push_back(pair<int, int>(abc, acc));
        return true;
    }

    return false;
}

int main()
{
    int n = 0;
    cin >> n;

    int count = 0;
    for(int a = 1; a < 10; a++)
    {
        for(int b = 0; b < 10; b++)
        {
            for(int c = 0; c < 10; c++)
            {
                if(fit(a,b,c,n))
                {
                    count++;
                }
            }
        }
    }

    cout << count << endl;
    for(pair<int, int>&p:store) {
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}