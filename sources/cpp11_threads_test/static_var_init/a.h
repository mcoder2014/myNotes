#ifndef A_H
#define A_H

#include <string>
class A
{
public:
    A();
    A(std::string str);
    static A* localStaticVar();
};

#endif // A_H
