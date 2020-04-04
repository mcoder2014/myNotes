#include "singleinstanceiv.h"
#include <iostream>

SingleInstanceIV* SingleInstanceIV::m_instance = new SingleInstanceIV();

SingleInstanceIV::SingleInstanceIV()
{
    printf("%s %d mem address: %ld\n",__FUNCTION__, __LINE__, (int64_t)this);
}

SingleInstanceIV::~SingleInstanceIV()
{

}

SingleInstanceIV *SingleInstanceIV::getInstance()
{
    return m_instance;
}

void SingleInstanceIV::deleteInstance()
{
    if(m_instance != nullptr)
    {
        delete  m_instance;
        m_instance = nullptr;
    }
}

int SingleInstanceIV::getData() const
{
    return data;
}

void SingleInstanceIV::setData(int value)
{
    data = value;
}
