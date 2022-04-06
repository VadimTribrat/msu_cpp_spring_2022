#include <gtest/gtest.h>
#include "allocator.hpp"

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

TEST_F(TestFoo, testMakeAllocator1)
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

TEST_F(TestFoo, testMakeAllocator2)
{
	allocator->makeAllocator(1);
	ASSERT_NE(allocator->alloc(1), nullptr);
	ASSERT_EQ(allocator->alloc(1), nullptr);
	allocator->makeAllocator(50);
	ASSERT_NE(allocator->alloc(20), nullptr);
	ASSERT_NE(allocator->alloc(30), nullptr);
	ASSERT_EQ(allocator->alloc(1), nullptr);
	allocator->reset();
	ASSERT_NE(allocator->alloc(50), nullptr);	
}

TEST_F(TestFoo, testPointers)
{
	allocator->makeAllocator(20);
	char* p1 = allocator->alloc(5);
	char* p2 = allocator->alloc(10);
	ptrdiff_t diff = p2 - p1;
	ASSERT_EQ(diff, 5);
	p2 = allocator->alloc(5);
	diff = p2 - p1;
	ASSERT_EQ(diff, 15);
	allocator->reset();
	p2 = allocator->alloc(10);
	diff = p2 - p1;
	ASSERT_EQ(diff, 0);
}

int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
