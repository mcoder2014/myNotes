#ifndef SINGLEINSTANCEII_H
#define SINGLEINSTANCEII_H
#include <iostream>
#include <mutex>

/**
 * @brief The SingleInstanceII class
 * 加锁的懒汉式
 */
class SingleInstanceII
{
public:
    static SingleInstanceII* getInstance();
    static void deleteInstance();

    int getData() const;
    void setData(int value);
    void printAddress();

private:

    SingleInstanceII();
    ~SingleInstanceII();

    static std::mutex mutex_instance;
    static SingleInstanceII* m_instance;

    int data;
};

#endif // SINGLEINSTANCEII_H
