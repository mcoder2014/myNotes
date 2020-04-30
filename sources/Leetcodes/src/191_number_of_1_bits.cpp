#include <iostream>

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int numOfOne = 0;
        uint32_t one = 1;
        for(int i = 0; i < 32; i++) {
            if(n &(one << i)) {
                numOfOne++;
            }
        }
        return numOfOne;
    }
};

int main()
{
    return 0;
}