
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <iostream>
#include <string>
#include <sstream>
#include <type_traits>
#include "vector.hpp"

class TestFoo : public ::testing::Test
{
};

TEST_F(TestFoo, test1)
{
	vector<int, allocator<int>> vec(3);
	for (size_t i = 0; i < 50; ++i)
	{
		vec.push_back(i);
	}
	int i = 0;
	for (auto val: vec)
	{
		ASSERT_TRUE(val == i++);
	}
	i = 49;
	for(auto it = vec.rbegin(); it != vec.rend(); ++it)
	{
		ASSERT_TRUE(*it == i--);
	}
	ASSERT_TRUE(i == -1);
	ASSERT_TRUE(vec.size() == 50);
	ASSERT_TRUE(vec.capacity() == 50);
	ASSERT_TRUE(vec.pop_back() == 49);
	ASSERT_TRUE(vec.size() == 49);
	ASSERT_TRUE(vec.capacity() == 50);
	for (size_t i = 0; i < 49; ++i)
		vec.pop_back();
	ASSERT_TRUE(vec.size() == 0);
	ASSERT_TRUE(vec.capacity() == 50);
	for (size_t i = 0; i < 50; ++i)
	{
		vec.emplace_back(i + 100);
	}
	i = 100;
	for (auto val: vec)
	{
		ASSERT_TRUE(val == i++);
	}
	ASSERT_TRUE(vec.size() == 50);
	ASSERT_TRUE(vec.capacity() == 50);
	vec.resize(100);
	i = 100;
	for (auto val: vec)
	{
		ASSERT_TRUE(val == i++);
	}
	ASSERT_TRUE(vec.size() == 50);
	ASSERT_TRUE(vec.capacity() == 100);
}

int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
