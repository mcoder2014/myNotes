#include "EventLoop.h"

#include <assert.h>

// unix support
#include <poll.h>

thread_local EventLoop* tLoopInThisThread = 0;

EventLoop::EventLoop()
    :looping(false),
    threadId(std::this_thread::get_id())
{
    if(!tLoopInThisThread)
    {
        tLoopInThisThread = this;
    }
    
}

EventLoop::~EventLoop()
{
    assert(!looping);
    tLoopInThisThread = nullptr;
}

EventLoop* EventLoop::getEventLoopOfCurrentThread()
{
    return tLoopInThisThread;
}

void EventLoop::loop()
{
    assert(!looping);
    assertInLoopThread();
    looping = true;

    // 定时器使用
    ::poll(nullptr, 0, 5*1000);

    looping = false;
}