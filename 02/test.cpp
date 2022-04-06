#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "parser.hpp"

class TestFoo : public ::testing::Test
{
};

void numFu(int i)
{
    static counter = 0;
    std::cout << "Digit: " << i << "\n";
    counter++;
    return counter;
}

void strFu(const std::string& str)
{
    static counter = 0;
    std::cout << "Digit: " << str << "\n";
    counter++;
    return counter;
}

TEST_F(TestFoo, test1)
{
	callbackOnNum(numFu);
    callbackOnStr(strFu);
    std::string str = "akd_ad   u89 1982 900 sfgk";

}

int main(int argc, char ** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}