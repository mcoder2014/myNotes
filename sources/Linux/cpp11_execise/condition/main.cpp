#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <stack>
#include <vector>
#include <atomic>
using namespace std;

static const int task = 100;

static std::mutex mutex_lock;
static std::condition_variable condition;

static std::stack<int> stk;
atomic_int counter(0);

void push()
{
    for(; counter.load() < task; counter.fetch_add(1))
    {
        std::unique_lock<mutex> lock(mutex_lock);
        stk.push(counter.load());
        condition.notify_all();
        printf("%s %d push data %d \n", __FUNCTION__, __LINE__, counter.load());
    }
}

void pop()
{
    thread::id this_id = this_thread::get_id();

    while(counter.load() < task)
    {
        std::unique_lock<mutex> lock(mutex_lock);
        condition.wait(lock);
        while(stk.size() > 0)
        {
            int data = stk.top();
            stk.pop();
            cout << "thread pop: " << this_id << " "
                 << __FUNCTION__ << " " << __LINE__
                 << " get value :" << data << std::endl;
        }

    }
}

int main()
{
    std::vector<thread> thread_pops;
    for(int i = 0; i < 5; i++)
    {
        thread_pops.emplace_back(thread(pop));
    }
    thread thread_push(push);

    thread_push.join();
    for(thread& th:thread_pops)
    {
        th.join();
    }

    return 0;
}
