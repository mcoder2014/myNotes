#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> genNext(string& dst)
{
    int j = 0;
    int k = -1;
    int len = dst.size();
    vector<int> next(len, 0);
    next[0] = -1;

    while(j < len) {
        if(k == -1 || dst[j] == dst[k]){
            k++;
            j++;
            next[j] = k;
        } else {
            k = next[k];
        }
    }

    return next;
}

int kmp(string& src, string& dst)
{
    vector<int> next = genNext(dst);
    
    int k = 0;

    int i = 0;
    while(i < src.size()){
        if(k==-1 || src[i] == dst[k]) {
            k++;
            i++;
            if(k == dst.size()) {
                return i-k;
            }
        } else {
            k = next[k];
        }
    }
    return -1;
}


int main()
{
    string src;
    string dst;

    while(true) {
        cin >> src >> dst;

        cout << "find dst at " << kmp(src, dst) << endl;
    }

}