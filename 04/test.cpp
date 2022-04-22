
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "bigint.hpp"

class TestFoo : public ::testing::Test
{
};

TEST_F(TestFoo, sumTest)
{
    ASSERT_TRUE(bigInt("12") + bigInt("101234654761620") == bigInt("101234654761632"));
    ASSERT_TRUE(bigInt("3787465125780") + bigInt("-1") == bigInt("3787465125779"));
    ASSERT_TRUE(bigInt("-356") + bigInt("-644") == bigInt("-1000"));
    ASSERT_TRUE(bigInt("1723541827354") + bigInt("1239847162394") == bigInt("2963388989748"));
    ASSERT_TRUE(bigInt("1000000000000000000000") + bigInt("100") == bigInt("1000000000000000000100"));
    ASSERT_TRUE(bigInt("-5") + bigInt("1000000000000000000000") == bigInt("999999999999999999995"));
    ASSERT_TRUE(bigInt("3787465125780") + -1 == bigInt("3787465125779"));
    ASSERT_TRUE(bigInt("1723541827354") + 1239847 == bigInt("1723543067201"));
    ASSERT_TRUE(bigInt("1723541827354") + 0 == bigInt("1723541827354"));
    std::cout << bigInt("12") + bigInt("101234654761620") << "\n";
}

TEST_F(TestFoo, subTest)
{
    ASSERT_TRUE(bigInt("12") - bigInt("101234654761620") == bigInt("-101234654761608"));
    ASSERT_TRUE(bigInt("3787465125780") - bigInt("-1") == bigInt("3787465125781"));
    ASSERT_TRUE(bigInt("-356") - bigInt("-644") == bigInt("288"));
    ASSERT_TRUE(bigInt("1723541827354") - bigInt("1239847162394") == bigInt("483694664960"));
    ASSERT_TRUE(bigInt("1000000000000000000000") - bigInt("100") == bigInt("999999999999999999900"));
    ASSERT_TRUE(bigInt("-5") - bigInt("1000000000000000000000") == bigInt("-1000000000000000000005"));
    ASSERT_TRUE(bigInt("3787465125780") - -1 == bigInt("3787465125781"));
    ASSERT_TRUE(bigInt("1723541827354") - 1239847 == bigInt("1723540587507"));
    ASSERT_TRUE(bigInt("1723541827354") - 0 == bigInt("1723541827354"));
}

TEST_F(TestFoo, mulTest)
{
    ASSERT_TRUE(bigInt("12") * bigInt("101234654761620") == bigInt("1214815857139440"));
    ASSERT_TRUE(bigInt("3787465125780") * bigInt("-1") == bigInt("-3787465125780"));
    ASSERT_TRUE(bigInt("3787465125780") * bigInt("0") == bigInt("0"));
    ASSERT_TRUE(bigInt("3787465125780") * bigInt("1") == bigInt("3787465125780"));
    ASSERT_TRUE(bigInt("-356") * bigInt("-644") == bigInt("229264"));
    ASSERT_TRUE(bigInt("172354182") * bigInt("12398471") == bigInt("2136928327255722"));
    ASSERT_TRUE(bigInt("1000000000000000000000") * bigInt("100") == bigInt("100000000000000000000000"));
    ASSERT_TRUE(bigInt("-12") * bigInt("12000000000000000000000") == bigInt("-144000000000000000000000"));
}

TEST_F(TestFoo, compTest)
{
    ASSERT_TRUE(bigInt("12") == bigInt("12"));
    ASSERT_TRUE(bigInt("3787465125780") > bigInt("-3787465125780"));
    ASSERT_TRUE(bigInt("3787465125780") >= bigInt("-3787465125780"));
    ASSERT_TRUE(bigInt("3787465125780") <= bigInt("3787465125780"));
    ASSERT_TRUE(bigInt("-2") < bigInt("-1"));
    ASSERT_TRUE(bigInt("-200") > bigInt("-201"));
    ASSERT_TRUE(bigInt("3787465125780") != bigInt("3787"));
}

int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
