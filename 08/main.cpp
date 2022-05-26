#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include "pool.hpp"

void f(int i)
{
    std::cout << 10 << "\n";
    // return 100;
}

int main()
{
    ThreadPool pool(8);
    auto val = pool.exec(f, 10);
    val.wait();
    //std::cout << val.get() << "\n";
    return 0;
}