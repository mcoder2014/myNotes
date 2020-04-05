#include <iostream>
#include <a.h>
using namespace std;


static A staticGlobal("global static var");
A global("global");

/**
 * @brief main
 * 研究静态变量什么时机初始化
 * @return
 */
int main()
{
    cout << "Hello World!" << endl;
    A* lazyStaticVar = A::localStaticVar();

    return 0;
}
