#include "singleinstanceii.h"

SingleInstanceII* SingleInstanceII::m_instance = nullptr;
std::mutex SingleInstanceII::mutex_instance;

SingleInstanceII::SingleInstanceII()
{
    printf("%s %d mem address: %ld\n",__FUNCTION__, __LINE__, (int64_t)this);
}

SingleInstanceII::~SingleInstanceII()
{

}

SingleInstanceII *SingleInstanceII::getInstance()
{
    if(m_instance == nullptr)
    {
        mutex_instance.lock();
        if(m_instance == nullptr)
        {
            m_instance = new SingleInstanceII();
        }
        mutex_instance.unlock();
    }
    return m_instance;
}

void SingleInstanceII::deleteInstance()
{
    mutex_instance.lock();
    if(m_instance != nullptr)
    {
        delete m_instance;
        m_instance = nullptr;
    }
    mutex_instance.unlock();
}

int SingleInstanceII::getData() const
{
    return data;
}

void SingleInstanceII::setData(int value)
{
    data = value;
}

void SingleInstanceII::printAddress()
{
    printf("%s %d mem address: %ld\n",__FUNCTION__, __LINE__, (int64_t)this);
}
