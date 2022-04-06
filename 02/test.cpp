
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "parser.hpp"

class TestFoo : public ::testing::Test
{
};

void numFu(int i)
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
	callbackOnNum(numFu);
    callbackOnStr(strFu);
    callbackOnStart(before);
    callbackOnEnd(after);
    std::string str = "akd_ad   u89 1982 900 sfgk";
    parser(str);
}

int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
