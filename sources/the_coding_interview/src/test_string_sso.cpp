#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

class C
{
public:
    C(string &s) : _s(s), _value(s.c_str()) // s引用计数+1
    {
        printf("s : %s\n", s.c_str());
        printf("_s:%s\n", _s.c_str());
        printf("s : %p---->%p\n", &s, s.c_str());
        printf("_s: %p---->%p\n", &_s, _s.c_str());
        printf("_value: %s\n", _value);
    }
    string _s;
    const char *_value;
};

C *func()
{
    string a = "aaa"; //rc = 1
    return new C(a);
}
int main(int argc, char *argv[])
{
    C *c = func();
    cout << "c->_value: " << c->_value << endl;
    cout << "c->_s:" << c->_s << endl;
    return 0;
}