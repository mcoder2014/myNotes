#include <iostream>

using namespace std;

class A
{
public:
    ~A(){}
};

class Base: public A
{
public:
    virtual ~Base(){}
    virtual Base* f(Base* param)
    {
        cout << "Base" << endl;
        return nullptr;
    }
};

class Derived: public Base
{
public:
    virtual ~Derived(){}
    
    // override 返回值为 Base 的派生类不会失效
    // override 参数必须为 Base 才行
    virtual Derived* f(Base* param) override
    {
        cout << "Derived" << endl;
        return nullptr;
    }
};

int main()
{
    return 0;
}