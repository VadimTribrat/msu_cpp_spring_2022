#include <gtest/gtest.h>
#include <chrono>
#include "pool.hpp"

class TestFoo : public ::testing::Test
{
};

void f1(size_t iterations)
{
    volatile int sum_ = 0;
    for (size_t i = 0; i < iterations; ++i)
        sum_++;
}

TEST_F(TestFoo, test1)
{
    std::vector<std::future<void>> futures;
    ThreadPool pool(4);
    auto startTime = std::chrono::system_clock::now();
    for (size_t i = 0; i < 10; ++i)
        f1(100'000'000);
    auto endTime = std::chrono::system_clock::now();
    std::cout << "Without pool: " << 
    std::chrono::duration_cast<std::chrono::milliseconds> (endTime - startTime).count() << "\n";

    startTime = std::chrono::system_clock::now();
    for (size_t i = 0; i < 10; ++i)
        futures.push_back(pool.exec(f1, 100'000'000));
    for (auto& val: futures)
        val.wait();
    endTime = std::chrono::system_clock::now();
    std::cout << "With pool: " << 
    std::chrono::duration_cast<std::chrono::milliseconds> (endTime - startTime).count() << "\n";
}

TEST_F(TestFoo, test2)
{
    std::vector<std::future<size_t>> futures;
    ThreadPool pool(4);
    for (size_t i = 0; i < 20; ++i)
    {
        futures.push_back(
            pool.exec(
                [](size_t k){
                    std::cout << k << "\n";
                    return k + 100;
                }, i
            )
        );
    }
    std::cout << "\n\n";
    for (auto& val: futures)
        std::cout << val.get() << "\n";
}

int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}