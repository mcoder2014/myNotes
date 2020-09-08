#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

class Comp1
{
    public:
    bool
    operator()(pair<int, string>& x, pair<int, string>& y)
    { 
        if(x.first < y.first) {
            return true;
        } else if (x.first > y.first) {
            return false;
        } else {
            return x.second > y.second;
        }
    }
};

class Comp2
{
    public:
    bool
    operator()(pair<int, string>& x, pair<int, string>& y)
    { 
        if(x.first < y.first) {
            return true;
        } else if (x.first > y.first) {
            return false;
        } else {
            return x.second < y.second;
        }
    }
};

void coutLine(pair<int, string> item) {
    cout << item.second << " " << item.first << endl;
}

void coutMaxK(int K, map<string, int> counts) {
    priority_queue<pair<int, string>, vector<pair<int, string>>, Comp1> strQueue;
    priority_queue<pair<int, string>, vector<pair<int, string>>, Comp2> strQueue2;

    for(pair<string, int> item:counts) {
        strQueue.push(pair<int, string>(item.second, item.first));
        strQueue2.push(pair<int, string>(item.second, item.first));
    }

    // 前k个是最小的
    for(int i = 0; i < K; i++) {
        coutLine(strQueue.top());
        strQueue.pop();
    }

    for(int i = 0; i < counts.size() - K; i++) {
        strQueue2.pop();
    }

    // 后k个是最大的
    vector<pair<int, string>> vec;
    for(int i = 0; i <K; i++) {
        vec.push_back(strQueue2.top());
        strQueue2.pop();
    }
    std::reverse(vec.begin(), vec.end());
    for(pair<int, string> &item:vec) {
        coutLine(item);
    }
}

int main()
{
    int N, K;
    scanf("%d %d", &N, &K);

    vector<string> strs(N);
    string str;
    map<string, int> counts;
    for(int i =0; i < N; i++)
    {
        cin >> str;
        strs[i] = str;
        if(counts.find(str) != counts.end()) {
            counts[str] = counts[str] + 1;
        } else {
            counts[str] = 1;
        }
    }

    coutMaxK(K, counts);

    return 0;
}