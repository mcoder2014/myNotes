#include <iostream>
#include <algorithm>

using namespace std;


class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {

        int areaA = (C-A) * (D-B);
        int areaB = (G-E) * (H-F);

        // 排除没有相交的情况
        if(E > C || A > G || B > H || F > D) {
            return areaA + areaB;
        }

        int minX, minY;
        int maxX, maxY;

        minX = max(A, E);
        minY = max(B, F);
        maxX = min(C, G);
        maxY = min(D, H);

        int dupArea = (maxX - minX) * (maxY - minY);
        return areaA - dupArea + areaB;
    }
};

int main()
{
    return 0;
}