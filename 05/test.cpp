#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
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

struct DataBool
{
	bool b1;
	DataBool(bool b1):b1{b1}
	{}

	template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(b1);
    }
	bool operator==(const DataBool& other)
	{
		return b1 == other.b1;
	}
};

struct DataUInt
{
	uint64_t a;
	DataUInt(uint64_t a): a{a}
	{}

	template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a);
    }
	bool operator==(const DataUInt& other)
	{
		return a == other.a;
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
	ASSERT_EQ(ser.save(data), Error::NoError);
	data.a = 12;
	data.b = 22;
	data.c = 32;
	data.b1 = false;
	data.b2 = true;
	ASSERT_TRUE(data == Data(12, 22, 32, false, true));
	ASSERT_EQ(deser.load(data), Error::NoError);
	ASSERT_TRUE(data == Data(1, 2, 3, true, false));
}

TEST_F(TestFoo, test2)
{
	Data data{0, 0, 0, true, true};
	std::stringstream ss;
	Serializer ser(ss);
	Deserializer deser(ss);
	ASSERT_EQ(ser.save(data), Error::NoError);
	data.a = 12;
	ASSERT_TRUE(data == Data(12, 0, 0, true, true));
	ASSERT_EQ(deser.load(data), Error::NoError);
	ASSERT_EQ(ser.save(data), Error::NoError);
	ASSERT_TRUE(data == Data(0, 0, 0, true, true));
	data.b = 100;
	ASSERT_TRUE(data == Data(0, 100, 0, true, true));
	data.b1 = false;
	ASSERT_TRUE(data == Data(0, 100, 0, false, true));
	ASSERT_EQ(deser.load(data), Error::NoError);
	ASSERT_TRUE(data == Data(0, 0, 0, true, true));
}

TEST_F(TestFoo, test3)
{
	DataBool dataB1{true};
	DataBool dataB2{false};
	std::stringstream ss1;
	std::stringstream ss2;
	Serializer ser1(ss1);
	Deserializer deser1(ss1);
	Serializer ser2(ss2);
	Deserializer deser2(ss2);
	ASSERT_EQ(ser1.save(dataB1), Error::NoError);
	ASSERT_EQ(ser2.save(dataB2), Error::NoError);
	dataB1.b1 = false;
	dataB2.b1 = true;
	ASSERT_TRUE(dataB1 == DataBool(false));
	ASSERT_TRUE(dataB2 == DataBool(true));
	ASSERT_EQ(deser1.load(dataB1), Error::NoError);
	ASSERT_EQ(deser2.load(dataB2), Error::NoError);
	ASSERT_TRUE(dataB1 == DataBool(true));
	ASSERT_TRUE(dataB2 == DataBool(false));
}

TEST_F(TestFoo, test4)
{
	DataUInt data(15);
	std::stringstream ss;
	Serializer ser(ss);
	Deserializer deser(ss);
	ASSERT_EQ(ser.save(data), Error::NoError);
	data.a = 100;
	ASSERT_TRUE(data == DataUInt(100));
	ASSERT_EQ(deser.load(data), Error::NoError);
	ASSERT_TRUE(data == DataUInt(15));
}

TEST_F(TestFoo, test5)
{
	Data data{0, 0, 0, true, true};
	std::stringstream ss;
	ss << "0 0 0 true ";
	Deserializer deser(ss);
	ASSERT_EQ(deser.load(data), Error::CorruptedArchive);
	ss.clear();
	ss << "0 AAA 0 true true ";
	ASSERT_EQ(deser.load(data), Error::CorruptedArchive);
	ss.clear();
	ss << "0 0 0 true true  true";
	ASSERT_EQ(deser.load(data), Error::CorruptedArchive);
}

TEST_F(TestFoo, testMaxValue)
{
	uint64_t val = std::numeric_limits<uint64_t>::max();
	DataUInt data(val);
	std::stringstream ss;
	Serializer ser(ss);
	Deserializer deser(ss);
	ASSERT_EQ(ser.save(data), Error::NoError);
	data.a = 100;
	ASSERT_TRUE(data == DataUInt(100));
	ASSERT_EQ(deser.load(data), Error::NoError);
	ASSERT_TRUE(data == DataUInt(val));
}

TEST_F(TestFoo, testOverFlow)
{
	DataUInt data(10);
	std::stringstream ss;
	ss << "18446744073709551616" << " ";
	Deserializer deser(ss);
	ASSERT_EQ(deser.load(data), Error::CorruptedArchive);
	ss.clear();
	ss << "123AAA456" << " ";
	ASSERT_EQ(deser.load(data), Error::CorruptedArchive);
	ss.clear();
	ss << "18446744073709551615" << " ";
	ASSERT_EQ(deser.load(data), Error::NoError);
}

int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
