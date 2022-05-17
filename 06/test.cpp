#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <type_traits>
#include "format.hpp"

class TestFoo : public ::testing::Test
{
};

TEST_F(TestFoo, test1)
{
	auto text = format("{1}+{1} = {0}", 2, "one");
	ASSERT_TRUE(text == "one+one = 2");
	EXPECT_THROW(
		try
		{
			format("{0}, {1}, {3}", 1, 2);
		}
		catch(const MyException& e)
		{
			EXPECT_STREQ(e.what(), "Not enough arguments\n");
			throw;
		},
		MyException
		
	);
	EXPECT_THROW(
		try
		{
			format("{0}, {1} {", 1, 2);
		}
		catch(const MyException& e)
		{
			EXPECT_STREQ(e.what(), "Unbalanced number of brackets\n");
			throw;
		},
		MyException
		
	);
	ASSERT_TRUE(format("{0}, {1}, {0}, {2}", false, 1, "abc") == "0, 1, 0, abc");
}

TEST_F(TestFoo, test2)
{
	auto text = format("");
	ASSERT_TRUE(text == "");
	text = format("qwerty 12");
	ASSERT_TRUE(text == "qwerty 12");
	text = format("{0}", 15);
	ASSERT_TRUE(text == "15");
	text = format("ABC{0}FG", "D");
	ASSERT_TRUE(text == "ABCDFG");
	text = format("{0}{1}{2}{0}", true, 4, "a");
	ASSERT_TRUE(text == "14a1");
	text = format("one {0} one {0} {1}", "two", "three");
	ASSERT_TRUE(text == "one two one two three");
}

TEST_F(TestFoo, test3)
{
	EXPECT_THROW(
		try
		{
			format("qwerty {0}{", 1);
		}
		catch(const MyException& e)
		{
			EXPECT_STREQ(e.what(), "Unbalanced number of brackets\n");
			throw;
		},
		MyException
		
	);
	EXPECT_THROW(
		try
		{
			format("qwe {0}{ ty", 1);
		}
		catch(const MyException& e)
		{
			EXPECT_STREQ(e.what(), "Not a number");
			throw;
		},
		MyException
		
	);
	EXPECT_THROW(
		try
		{
			format("qwe {0 ty", 1);
		}
		catch(const MyException& e)
		{
			EXPECT_STREQ(e.what(), "Not a number");
			throw;
		},
		MyException
		
	);
	EXPECT_THROW(
		try
		{
			format("qwerty {0}}", 1);
		}
		catch(const MyException& e)
		{
			EXPECT_STREQ(e.what(), "Unbalanced number of brackets\n");
			throw;
		},
		MyException
		
	);
	EXPECT_THROW(
		try
		{
			format(format("qwe {0}} ty", 1), 1);
		}
		catch(const MyException& e)
		{
			EXPECT_STREQ(e.what(), "Unbalanced number of brackets\n");
			throw;
		},
		MyException
		
	);
	EXPECT_THROW(
		try
		{
			format("qwe 0} ty", 1);
		}
		catch(const MyException& e)
		{
			EXPECT_STREQ(e.what(), "Unbalanced number of brackets\n");
			throw;
		},
		MyException
		
	);
	EXPECT_THROW(
		try
		{
			format("qwe {} ty", 1);
		}
		catch(const MyException& e)
		{
			EXPECT_STREQ(e.what(), "No index");
			throw;
		},
		MyException
		
	);
	EXPECT_THROW(
		try
		{
			format("qwe {1str} ty", 1);
		}
		catch(const MyException& e)
		{
			EXPECT_STREQ(e.what(), "Not a number");
			throw;
		},
		MyException
		
	);
	EXPECT_THROW(
		try
		{
			format("qwe {str} ty", 1);
		}
		catch(const MyException& e)
		{
			EXPECT_STREQ(e.what(), "Not a number");
			throw;
		},
		MyException
		
	);
	EXPECT_THROW(
		try
		{
			format("qwe {10000000000000000000000000000} ty", 1);
		}
		catch(const MyException& e)
		{
			EXPECT_STREQ(e.what(), "Too long number");
			throw;
		},
		MyException
		
	);
	EXPECT_THROW(
		try
		{
			format("one {0} one {0} {1}", "two");
		}
		catch(const MyException& e)
		{
			EXPECT_STREQ(e.what(), "Not enough arguments\n");
			throw;
		},
		MyException
		
	);
	EXPECT_THROW(
		try
		{
			format("one {0} one {0} {1} 3", "two", "two", "two");
		}
		catch(const MyException& e)
		{
			EXPECT_STREQ(e.what(), "Too much arguments");
			throw;
		},
		MyException
		
	);
}

int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
