#ifndef SINGLEINSTANCEIII_H
#define SINGLEINSTANCEIII_H

/**
 * @brief The SingleInstanceIII class
 * 内部静态变量的懒汉式单例模式
 */
class SingleInstanceIII
{
public:
    static SingleInstanceIII* getInstance();

    int getData() const;
    void setData(int value);

private:
    SingleInstanceIII();
    ~SingleInstanceIII();

    int data;

};

#endif // SINGLEINSTANCEIII_H
