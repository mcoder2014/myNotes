#include <iostream>
#include <memory>

using namespace std;

class Base
{
public:
    virtual ~Base(){};
    virtual void test() = 0;
};

class Derived: public Base
{
public:
    virtual ~Derived(){}
    virtual void test()
    {
        printf("Derived test\n");
    }
};

int main()
{
    unique_ptr<Base> base = make_unique<Derived>();
    base->test();
    return 0;
}
