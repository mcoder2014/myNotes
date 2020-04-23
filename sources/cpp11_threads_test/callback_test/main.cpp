#include <iostream>
#include <functional>

void testFunction()
{
    printf("testFunction %d\n", __LINE__);
}

int main()
{

    std::function<void()> callback;
    callback = std::bind(&testFunction);

    callback();   
    
    return 0;
}
