
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "parser.hpp"

class TestFoo : public ::testing::Test
{
};

void numFu(unsigned long i)
{
    std::cout << "Digit: " << i << "\n";
}

void strFu(const std::string& str)
{
    std::cout << "String " << str << "\n";
}

void before()
{
	std::cout << "Start\n";
}

void after()
{
	std::cout << "End\n";
}

TEST_F(TestFoo, test1)
{
    TokenParser tp;
	tp.SetDigitTokenCallback(numFu);
    tp.SetStringCallback(strFu);
    tp.SetStartCallback(before);
    tp.SetEndCallback(after);
    std::string str = "akd_ad   u89 1982 900 sfgk";
    tp.Parse(str);
    std::vector<std::string> res{"Start", "Str:akd_ad", "Str:u89", "Dig:1982", "Dig:900", "Str:sfgk", "End"};
    ASSERT_EQ(tp.forTest, res);
}

TEST_F(TestFoo, nullPtrTest)
{
    TokenParser tp;
	tp.SetDigitTokenCallback(nullptr);
    tp.SetStringCallback(nullptr);
    tp.SetStartCallback(nullptr);
    tp.SetEndCallback(nullptr);
    std::string str = "akd_ad   u89 1982 900 sfgk";
    tp.Parse(str);
    std::vector<std::string> res;
    ASSERT_EQ(tp.forTest, res);
}

TEST_F(TestFoo, emptyString)
{
    TokenParser tp;
	tp.SetDigitTokenCallback(numFu);
    tp.SetStringCallback(strFu);
    tp.SetStartCallback(before);
    tp.SetEndCallback(after);
    std::string str = "";
    tp.Parse(str);
    std::vector<std::string> res{"Start", "End"};
    ASSERT_EQ(tp.forTest, res);
}

TEST_F(TestFoo, spaceString)
{
    TokenParser tp;
	tp.SetDigitTokenCallback(numFu);
    tp.SetStringCallback(strFu);
    tp.SetStartCallback(before);
    tp.SetEndCallback(after);
    std::string str = "           \n \n  \t";
    tp.Parse(str);
    std::vector<std::string> res{"Start", "End"};
    ASSERT_EQ(tp.forTest, res);
}

TEST_F(TestFoo, test2)
{
    TokenParser tp;
	tp.SetDigitTokenCallback(numFu);
    tp.SetStringCallback(strFu);
    tp.SetStartCallback(before);
    tp.SetEndCallback(after);
    std::string str = " a v 1   3 0 -1 d";
    tp.Parse(str);
    std::vector<std::string> res{"Start", "Str:a", "Str:v", "Dig:1", "Dig:3", "Str:0", "Str:-1", "Str:d", "End"};
    ASSERT_EQ(tp.forTest, res);
}

TEST_F(TestFoo, test3)
{
    TokenParser tp;
	tp.SetDigitTokenCallback(numFu);
    tp.SetStringCallback(strFu);
    tp.SetStartCallback(before);
    tp.SetEndCallback(after);
    std::string str = " ahj39__ 8723 12jjj9 jkf -190 sss 0001";
    tp.Parse(str);
    std::vector<std::string> res{ "Start", "Str:ahj39__", "Dig:8723", "Str:12jjj9", "Str:jkf", "Str:-190", "Str:sss", "Dig:0001", "End" };
    ASSERT_EQ(tp.forTest, res);
}

TEST_F(TestFoo, maxValues)
{
    TokenParser tp;
	tp.SetDigitTokenCallback(numFu);
    tp.SetStringCallback(strFu);
    tp.SetStartCallback(before);
    tp.SetEndCallback(after);
    std::string str = "18446744073709551615   \t 184467440737095516106 \n 18446744073709551617";
    tp.Parse(str);
    std::vector<std::string> res{ "Start", "Dig:18446744073709551615", "Str:184467440737095516106", "Str:18446744073709551617", "End" };
    ASSERT_EQ(tp.forTest, res);
}

int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
