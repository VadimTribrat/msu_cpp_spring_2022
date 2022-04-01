#include <gtest/gtest.h>
#include "allocator.h"

class TestFoo : public ::testing::Test
{
protected:
	void SetUp()
	{
		allocator = new Allocator();
	}
	void TearDowm()
	{
		delete allocator;
	}
	Allocator * allocator;
};

TEST_F(TestFoo, testAlloc1)
{
	allocator->makeAllocator(15);
	ASSERT_NE(allocator->alloc(5), nullptr);
	ASSERT_NE(allocator->alloc(10), nullptr);
	ASSERT_EQ(allocator->alloc(1), nullptr);
	allocator->reset();
	ASSERT_NE(allocator->alloc(15), nullptr);
	ASSERT_EQ(allocator->alloc(1), nullptr);
}

TEST_F(TestFoo, testAlloc2)
{
	ASSERT_EQ(allocator->alloc(5), nullptr);
	allocator->makeAllocator(2);
	ASSERT_EQ(allocator->alloc(5), nullptr);
	ASSERT_NE(allocator->alloc(1), nullptr);
	ASSERT_NE(allocator->alloc(1), nullptr);
	ASSERT_EQ(allocator->alloc(1), nullptr);
}

TEST_F(TestFoo, testMakeAllocator)
{
	ASSERT_EQ(allocator->alloc(5), nullptr);
	allocator->makeAllocator(5);
	ASSERT_NE(allocator->alloc(5), nullptr);
	ASSERT_EQ(allocator->alloc(1), nullptr);
	allocator->makeAllocator(6);
	ASSERT_NE(allocator->alloc(5), nullptr);
	ASSERT_NE(allocator->alloc(1), nullptr);
	ASSERT_EQ(allocator->alloc(1), nullptr);
}

int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
