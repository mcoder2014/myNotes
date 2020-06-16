#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex a_mutex;
mutex b_mutex;

int a = 0;
int b = 0;

const int task = 10000;

void function_a()
{
    for (int i = 0; i < task; i++)
    {
        a_mutex.lock();
        a = a + 1;
        b_mutex.lock();

        printf("%s %d a = %d , b = %d \n", __FUNCTION__, __LINE__, a, b);

        b_mutex.unlock();
        a_mutex.unlock();
    }
}

void function_b()
{
    for (int i = 0; i < task; i++)
    {
        b_mutex.lock();
        b = b + 1;
        a_mutex.lock();
        printf("%s :%d a = %d , b = %d\n", __FUNCTION__, __LINE__, a, b);
        a_mutex.unlock();
        b_mutex.unlock();
    }
}

int main()
{
    thread thread_a(function_a);
    thread thread_b(function_b);

    thread_a.join();
    thread_b.join();

    return 0;
}
