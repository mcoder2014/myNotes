#include <iostream>
#include <vector>

using namespace std;

class ListNode
{
public:
    ListNode* next;
    int value;
};

vector<int> maxSub(vector<int> v1, vector<int> v2)
{
    vector<int>::iterator iter1 = v1.begin();
    vector<int>::iterator iter2 = v2.begin();

    vector<int> result;

    while(iter1 != v1.end() && iter2 != v2.end())
    {
        if(*iter1 > *iter2) {
            iter1++;
        } else if (*iter1 < *iter2) {
            iter2++;
        } else {
            result.push_back(*iter1);
            iter1++;iter2++;
        }
    }
    return result;
}

int main()
{

    int len1, len2;
    
    scanf("%d", &len1);
    vector<int> l1(len1);
    for(int i = 0; i < len1; i++) {
        scanf("%d", &(l1[i]));
    }

    scanf("%d", &len2);
    vector<int> l2(len2);
    for(int i = 0; i < len2; i++) {
        scanf("%d", &(l2[i]));
    }

    vector<int> result = maxSub(l1, l2);
    for(int i = 0; i < result.size() -1; i++) {
        printf("%d ", result[i]);
    }
    if(result.size() > 1) {
        printf("%d\n", result[result.size()-1]);
    } else {
        printf("\n");
    }

    return 0;
}