#include "singleinstanceiii.h"
#include <iostream>

SingleInstanceIII::SingleInstanceIII()
{
    printf("%s %d mem address: %ld\n",__FUNCTION__, __LINE__, (int64_t)this);
}

SingleInstanceIII::~SingleInstanceIII()
{

}

SingleInstanceIII *SingleInstanceIII::getInstance()
{
    // 静态变量，始终在内存中
    static SingleInstanceIII instance;
    return &instance;
}

int SingleInstanceIII::getData() const
{
    return data;
}

void SingleInstanceIII::setData(int value)
{
    data = value;
}
