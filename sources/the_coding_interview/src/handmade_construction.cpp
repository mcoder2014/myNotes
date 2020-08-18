#include <iostream>
#include <memory>

using namespace std;

/**
 * 测试不使用构造函数，自己申请一大块空间,
 * 然后初始化类对象
 */

class A
{
public:
    int a;
    char b;
    double c;
    float d;

    void print()
    {
        cout << a << "\t" 
            << b << "\t" 
            << c << "\t" 
            << d << "\n";
    }
};

/**
 * 构造函数
 */ 
void construct(A* a)
{
    a->a = 1;
    a->b = '2';
    a->c = 3;
    a->d = 4;
}

int main()
{
    void *mem = malloc(sizeof(A) * 10);

    for(int i = 0; i < 10; i++) {
        int offset = i * sizeof(A);
        A* a = (A*)((int64_t)mem + offset);
        construct(a);
        a->print();
    }

    free(mem);
    return 0;
}