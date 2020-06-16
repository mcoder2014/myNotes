#include <iostream>
#include <functional>

void testFunction()
{
    printf("testFunction %d\n", __LINE__);
}

void testFunctionWithArgs(int a, int b, int c)
{
    printf("a: %d, b: %d, c: %d\n", a, b ,c);
}

class A
{
    public:
    void testObjectFunction(int a, int b, int c)
    {
        printf("data: %d, a: %d, b: %d, c: %d\n", data, a, b, c);
    }
    int data;
};

int main()
{

    // 无参回调
    std::function<void()> callback;
    callback = std::bind(&testFunction);

    callback();   
    
    // 使用占位符的回调
    std::function<void(int,int,int)> callbackWithArgs = std::bind(&testFunctionWithArgs, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    callbackWithArgs(1,2,3);

    // 指派参数的 回调
    std::function<void()> callbackSettingArgs = std::bind(&testFunctionWithArgs, 4,5,6);
    callbackSettingArgs();

    // 指定部分参数，仍留有部分参数
    std::function<void(int,int)> callbackWithPartiionalArgs = std::bind(&testFunctionWithArgs, std::placeholders::_2, 7, std::placeholders::_1);
    //                         _1 _2
    callbackWithPartiionalArgs(8, 9);

    // 回调对象的函数
    A a;
    a.data = 10;
    std::function<void(int)> callbackObjectFunction = std::bind(&A::testObjectFunction, &a, 11, std::placeholders::_1, 12);
    callbackObjectFunction(13);

    return 0;
}
