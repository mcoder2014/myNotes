#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template<typename T>
class plus11
{
public:
    void operator()(T& value) 
    {
        value = value +11;
    }
};

template<class T>
class cqPrint
{
public:
    void operator()(const T& value)
    {
        cout << "v: " << value << endl;
    }
};

int main ()
{
    std::vector<int> array(10, 0);
    for_each(array.begin(), array.end(), plus11<int>());
    for_each(array.begin(), array.end(), cqPrint<int>());
    return 0;
}
