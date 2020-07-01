#include <iostream>
#include <vector>

using namespace std;

int josephuse(int count, int interval) 
{   
    if(count <= 1 || interval <= 1) {
        return -1;
    }

    int last = 0;
    for(int i =2; i <= count; i++) {
        last = (last + interval) % i;
    }

    return last;

}


int main()
{
    int count;
    int interval;

    while(cin >> count >> interval) {
        cout << "last num " << josephuse(count, interval) << endl;
    }

    return 0;
}
