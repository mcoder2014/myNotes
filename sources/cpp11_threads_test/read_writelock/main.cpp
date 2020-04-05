#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <vector>
using namespace std;

int task = 100;

int account = 0;
std::shared_mutex rwlock;

void writer()
{
    std::thread::id this_id = std::this_thread::get_id();
    for(int i = 0; i < task; i++)
    {
        std::unique_lock<std::shared_mutex> lock(rwlock);
        account++;
        std::cout << "writer thread: " << this_id
                  << __FUNCTION__ << " " << __LINE__
                  << " value: " << account << std::endl;
    }
}

void reader()
{
    std::thread::id this_id = std::this_thread::get_id();
    for(int i =0; i <task; i++)
    {
        rwlock.lock_shared();
        std::cout << "reader thread: " << this_id
                  << __FUNCTION__ << " " << __LINE__
                  << " value: " << account << std::endl;
        rwlock.unlock_shared();
    }
}


int main()
{
    std::vector<thread> thread_writers;
    std::vector<thread> thread_readers;
    for(int i = 0; i <5; i++)
    {
        thread_writers.emplace_back(thread(writer));
        thread_readers.emplace_back(std::thread(reader));
    }

    for(thread& th: thread_writers)
    {
        th.join();
    }
    for(thread& th:thread_readers)
    {
        th.join();
    }


    return 0;
}
