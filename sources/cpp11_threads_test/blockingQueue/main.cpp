#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <sys/poll.h>

// #include <windows.h>

#include <blockingqueue.h>
using namespace std;

int task=100;
BlockingQueue<int> blockingqueue;
std::mutex mutex_cout;

void worker()
{
    int value;
    thread::id this_id = this_thread::get_id();
    while(true)
    {
        value = blockingqueue.take();
        uint64_t sum = 0;
        for(int i = 0; i < value; i++)
        {
            sum += i;
        }

        // 模拟耗时操作
        poll(nullptr, 0, 100);

        std::lock_guard<mutex> lock(mutex_cout);
        std::cout << "workder: " << this_id << " "
                  << __FUNCTION__
                  << " line: " << __LINE__
                  << " sum: " << sum
                  << std::endl;
    }
}

void master()
{
    srand(time(nullptr));
    for(int i = 0; i < task; i++)
    {
        blockingqueue.push(rand()%10000);
        printf("%s %d %i\n",__FUNCTION__, __LINE__, i);
        poll(nullptr, 0, 20);
    }
}

int main()
{
    thread th_master(master);
    std::vector<thread> th_workers;
    for(int i =0; i < 5; i++)
    {
        th_workers.emplace_back(thread(worker));
    }

    th_master.join();
    return 0;
}
