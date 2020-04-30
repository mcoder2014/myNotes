#include <iostream>

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t result = 0;
        uint32_t one = 1;
        for(int i = 0; i <32; i++) {
            uint32_t bit = n & (one << i);
            bit = bit >> i;
            result = result | bit << (31-i);
        }
        return result;
    }
};

int main()
{
    return 0;
}