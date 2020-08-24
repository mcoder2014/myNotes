#pragma once

#include <thread>

class EventLoop
{
public:
    EventLoop();
    ~EventLoop();

    void loop();
    void assertInLoopThread()
    {
        if(!isInLoopThread())
        {
            abortNotInLoopThread();
        }
    }

    bool isInLoopThread() const 
    {
        return threadId == std::this_thread::get_id();
    }

    static EventLoop* getEventLoopOfCurrentThread();

private:
    void abortNotInLoopThread();

    bool looping;
    const std::thread::id threadId;
};