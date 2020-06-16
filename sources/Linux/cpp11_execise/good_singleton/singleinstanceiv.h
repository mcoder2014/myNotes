#ifndef SINGLEINSTANCEIV_H
#define SINGLEINSTANCEIV_H


/**
 * @brief The SingleInstanceIV class
 * 饿汉式，线程安全
 * 饿汉模式：即无论是否调用该类的实例，
 * 在程序开始时就会产生一个该类的实例，并在以后仅返回此实例
 */
class SingleInstanceIV
{
public:
    static SingleInstanceIV *getInstance();
    static void deleteInstance();

    int getData() const;
    void setData(int value);

private:
    SingleInstanceIV();
    ~SingleInstanceIV();

    int data;
    static SingleInstanceIV* m_instance;
};

#endif // SINGLEINSTANCEIV_H
