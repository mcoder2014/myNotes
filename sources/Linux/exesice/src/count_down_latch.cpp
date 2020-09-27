#include <iostream>
#include <thread>
#include <vector>
#include <poll.h>

#include "CountDownLatch.h"

using namespace std;

CountDownLatch cdOrder(1);
CountDownLatch cdAnswer(3);

void run()
{
    cout << "Thread:" << this_thread::get_id() << " wait order" << endl;
    cdOrder.await();

    cout << "Thread:" << this_thread::get_id() << " get order" << endl;
    poll(nullptr, 0, 1000);
    cout << "Thread:" << this_thread::get_id() << " order process finished" << endl;
    cdAnswer.countDown();
}

int main()
{

    vector<thread> threads;
    threads.emplace_back(thread(run));
    threads.emplace_back(thread(run));
    threads.emplace_back(thread(run));

    poll(nullptr, 0, 3000);

    cout << "Thread:" << this_thread::get_id() << " dispatch order" << endl;
    cdOrder.countDown();

    cout << "Thread:" << this_thread::get_id() << " have send order" << endl;
    
    cdAnswer.await();
    cout << "Thread:" << this_thread::get_id() << " get all answer" << endl;

    return 0;
}