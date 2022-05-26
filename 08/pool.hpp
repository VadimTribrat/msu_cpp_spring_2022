#pragma once
#include <thread>
#include <queue>
#include <mutex>
#include <vector>
#include <condition_variable>
#include <future>
#include <functional>

class ThreadPool
{
    size_t size;
    std::condition_variable cv;
    std::mutex lock;
    std::vector<std::thread> threads;
    std::atomic<bool> done;
    std::queue<std::packaged_task<void()>> queue;
    void work();
public:
    explicit ThreadPool(size_t poolSize);
    ~ThreadPool();
    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
};

template <class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))>
{
    auto f = std::packaged_task<decltype(func(args...))()> ([func, args...]() { return func(args...); });
    auto fut = f.get_future();
    queue.emplace([f{std::move(f)}]() mutable { f(); } );
    cv.notify_one();
    return fut;
}