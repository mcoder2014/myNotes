#include "singleinstance.h"
#include<iostream>
SingleInstance* SingleInstance::m_instance=nullptr;

SingleInstance *SingleInstance::getInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new SingleInstance();
    }
    return m_instance;
}

void SingleInstance::deleteInstance()
{
    if(m_instance != nullptr)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

SingleInstance::~SingleInstance()
{

}

SingleInstance::SingleInstance()
{
    printf("%s %d mem address: %ld\n",__FUNCTION__, __LINE__, (int64_t)this);
}

int SingleInstance::getData() const
{
    return data;
}

int SingleInstance::getAndIncrease()
{
    data++;
    return data;
}

void SingleInstance::setData(int value)
{
    data = value;
}

void SingleInstance::printAddress()
{
    printf("%s %d mem address: %ld\n",__FUNCTION__, __LINE__, (int64_t)this);
}
