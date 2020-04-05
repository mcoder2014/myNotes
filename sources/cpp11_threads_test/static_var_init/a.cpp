#include "a.h"
#include <iostream>
A::A()
{
    printf("%s line: %d class Init;\n", __FUNCTION__, __LINE__);
}

A::A(std::string str)
{
    printf("%s line: %d class Init; %s\n", __FUNCTION__, __LINE__, str.data());
}

A *A::localStaticVar()
{
    static A a("static local");
    printf("%s line: %d class Init;\n", __FUNCTION__, __LINE__);
    return &a;
}
