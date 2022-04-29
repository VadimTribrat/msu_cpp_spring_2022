#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <sstream>
#include "serializer.hpp"
#include "deserializer.hpp"

struct Data
{
	uint64_t a, b, c;
	bool b1, b2;
	Data(uint64_t a, uint64_t b, uint64_t c, bool b1, bool b2): a{a}, b{b}, c{c}, b1{b1}, b2{b2}
	{}

	template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c, b1, b2);
    }
	bool operator==(const Data& other)
	{
		return (a == other.a) && 
		(b == other.b) &&
		(c == other.c) &&
		(b1 == other.b1) &&
		(b2 == other.b2); 
	}
};

class TestFoo : public ::testing::Test
{
};

TEST_F(TestFoo, test1)
{
	Data data{1, 2, 3, true, false};
	std::stringstream ss;
	Serializer ser(ss);
	Deserializer deser(ss);
	if (ser.save(data) != Error::NoError)
		assert(false);
	data.a = 12;
	data.b = 22;
	data.c = 32;
	data.b1 = false;
	data.b2 = true;
	ASSERT_TRUE(data == Data(12, 22, 32, false, true));
	if (deser.load(data) != Error::NoError)
		assert(false);
	ASSERT_TRUE(data == Data(1, 2, 3, true, false));
}

TEST_F(TestFoo, test2)
{
	Data data{0, 0, 0, true, true};
	std::stringstream ss;
	Serializer ser(ss);
	Deserializer deser(ss);
 	if (ser.save(data) != Error::NoError)
	 	assert(false);
	data.a = 12;
	ASSERT_TRUE(data == Data(12, 0, 0, true, true));
	if (deser.load(data) != Error::NoError)
		assert(false);
	if (ser.save(data) != Error::NoError)
		assert(false);
	ASSERT_TRUE(data == Data(0, 0, 0, true, true));
	data.b = 100;
	ASSERT_TRUE(data == Data(0, 100, 0, true, true));
	data.b1 = false;
	ASSERT_TRUE(data == Data(0, 100, 0, false, true));
	if (deser.load(data) != Error::NoError)
		assert(false);
	ASSERT_TRUE(data == Data(0, 0, 0, true, true));
}

int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
