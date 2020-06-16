#ifndef SINGLEINSTANCE_H
#define SINGLEINSTANCE_H

#include<stdio.h>

/**
 * @brief The SingleInstance class
 * 线程不安全的单例模式
 * 懒汉式
 * 懒汉模式：即第一次调用该类实例的时候才产生一个新的该类实例，
 * 并在以后仅返回此实例。
 */

class SingleInstance
{
    static SingleInstance* getInstance();
    static void deleteInstance();

public:
    int getData() const;
    int getAndIncrease();
    void setData(int value);

    void printAddress();

private:
    SingleInstance();
    ~SingleInstance();

    static SingleInstance* m_instance;
    int data;
};

#endif // SINGLEINSTANCE_H
