#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
    int n;
    string nodes;
    cin >> n;
    vector<int> idx(n);
    cin >> nodes;
    for(int i = 0; i < n; i ++) {
        cin >> idx[i];
    }

    return 0;
}