#include <functional>
#include <iostream>

using namespace std;

class Functor 
{
public:
    double operator() (double x, double y, double z) {
        return factor * (x + y + z);
    }
double factor;
};

std::function<double(double,double,double)> getAFunction(double factor) 
{
    Functor func;
    func.factor = factor;
    std::function<double(double,double,double)> stdFunction = func;
    return stdFunction;
}

int main()
{
    std::function<double(double,double,double)> func5 = getAFunction(5.0);
    std::function<double(double,double,double)> func2 = getAFunction(2);
    std::function<double(double,double,double)> func1 = getAFunction(1.0);

    std::cout << func1(1,2,3) << endl;
    std::cout << func2(1,2,3) << endl;
    std::cout << func5(1,2,3) << endl;

    return 0;
}