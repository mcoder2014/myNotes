#include <iostream>

using namespace std;

class Solution {
public:
    bool isPowerOfTwo(int n) {
        int64_t value = 2;
        if(n == 1) {
            return true;
        } else if(n <= 0) {
            return false;
        }

        while(value <= n) {
            if(value == n) {
                return true;
            }
            value = value << 1;
        }

        return false;
    }
};

int main()
{
    return 0;
}