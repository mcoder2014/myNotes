#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int countPrimes(int n) {
        if(n <2)
            return 0;
        vector<int> prime(n + 1, 0);
        for(int i = 1; i <= n; i++) {
            prime[i] = i;
        }

        int counter = 0;

        prime[0] = 0;
        prime[1] = 1;
        for(int i =2; i <= n/2; i++) {
            if(prime[i] != 0) {
                counter++;
                int delta = prime[i];
                int index = i+delta;
                while(index <= n) {
                    prime[index] = 0;
                    index += delta;
                }
            }
        }
        return counter;
    }
};

int main()
{
    return 0;
}