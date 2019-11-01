#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {

#ifdef On2
        int max_water = 0, size = height.size();
        for(int i =0; i < size; i++)
            for (int j = i+1; j < size; j++)
            {
                int lower = height[i] < height[j]? height[i]:height[j];
                int water = lower *(j-i);
                max_water = max_water > water ?max_water:water;
            }

        return max_water;
#endif

#define On
#ifdef On
        int max_water = 0, size = height.size();
        int i = 0, j = size -1;
        int tmp_lower, tmp_water;
        while (i <j)
        {
            tmp_lower = height[i]<height[j]?height[i]:height[j];
            tmp_water = tmp_lower * (j-i);
            max_water = max_water>tmp_water?max_water:tmp_water;

            if(tmp_lower == height[i])
                i++;
            else
                j--;
        }
        return max_water;
#endif

    }
};

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
