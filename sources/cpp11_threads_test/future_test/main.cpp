#include <iostream>
#include <future>
#include <thread>
#include <sys/poll.h>

int main()
{
    // 来自 packaged_task 的 future
    std::packaged_task<int()> task([]() {
        poll(nullptr, 0, 3000);
        return 7;
    }); // 包装函数

    std::future<int> f1 = task.get_future(); // 获取 future
    std::thread(std::move(task)).detach();   // 在线程上运行

    // 来自 async() 的 future
    std::future<int> f2 = std::async(std::launch::async, []() {
        poll(nullptr, 0, 3000);
        return 8;
    });

    // 来自 promise 的 future
    std::promise<int> p;
    std::future<int> f3 = p.get_future();
    std::thread([&p] {
        poll(nullptr, 0, 3000);
        p.set_value_at_thread_exit(9);
    }).detach();

    std::cout << "Waiting..." << std::flush;
    f1.wait();
    f2.wait();
    f3.wait();
    std::cout << "Done!\nResults are: "
              << f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';

    return 0;
}