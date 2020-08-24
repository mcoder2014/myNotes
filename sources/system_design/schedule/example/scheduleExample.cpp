#include <iostream>
#include <EventLoop.h>
#include <thread>

#include <unistd.h>

using namespace std;

void threadFunc()
{
    cout << "threadFunc(): pid = " <<  (getpid()) << 
    " tid = " << std::this_thread::get_id() << endl;
    
    EventLoop loop;
    loop.loop();
}

int main()
{
    cout << "main(): pid = " <<  (getpid()) << 
    " tid = " << std::this_thread::get_id() << endl;

    EventLoop loop;
    loop.loop();

    std::thread th(threadFunc);
    th.join();

    return 0;
}