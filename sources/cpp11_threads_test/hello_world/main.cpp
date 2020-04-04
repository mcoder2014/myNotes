#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>
#include <string>
#include <mutex>


std::mutex m;

int count = 0;

void get_and_plus()
{

//    int round = 1000000;
//    for(int i = 0; i < round; i++)
//    {
//        999999*5555555;
//    }

    std::lock_guard<std::mutex> guard(m);
    count ++;
    printf("%s:<%s>:%d count value %d\n ", __FILE__, __FUNCTION__, __LINE__ , count);
}

int main()
{
    std::vector<std::thread> threads;
    for(int i = 0; i < 10; i++)
    {
        threads.emplace_back(get_and_plus);
    }
    for(std::thread & thread: threads)
    {
        thread.join();
    }

    printf("End: %d\n", count);
    return 0;
}
