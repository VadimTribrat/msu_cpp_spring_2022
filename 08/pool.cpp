#include "pool.hpp"

ThreadPool::ThreadPool(size_t poolSize): size{poolSize}, done{false}
{
    for (size_t i = 0; i < size; ++i)
    {
        threads.push_back(std::thread([this](){ this->work(); }));
    }
}

void ThreadPool::work()
{
    while (!done)
    {
        std::unique_lock<std::mutex> guard(lock);
        if (queue.empty())
            cv.wait(guard);
        else
        {
            auto fun = std::move(queue.front());
            queue.pop();
            guard.unlock();
            fun();   
        }        
    }
}

ThreadPool::~ThreadPool()
{
    done = true;
    cv.notify_all();
    for (auto& val: threads)
        val.join();
}